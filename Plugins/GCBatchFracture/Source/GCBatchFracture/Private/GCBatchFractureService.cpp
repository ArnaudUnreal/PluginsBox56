// Copyright Arnaud Szobad 2026 All Rights Reserved.

#include "GCBatchFractureService.h"
#include "GCBatchFractureLog.h"
#include "AssetToolsModule.h"
#include "SGCBatchFractureDialog.h"
#include "Framework/Application/SlateApplication.h"
#include "Framework/Docking/TabManager.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"
#include "Widgets/SWindow.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Dataflow/DataflowSelection.h"
#include "Engine/StaticMesh.h"
#include "Rendering/NaniteResources.h"
#include "StaticMeshResources.h"
#include "FractureEngineFracturing.h"
#include "FractureEngineUtility.h"
#include "GeometryCollection/GeometryCollection.h"
#include "GeometryCollection/GeometryCollectionAlgo.h"
#include "GeometryCollection/GeometryCollectionConvexUtility.h"
#include "GeometryCollection/GeometryCollectionEngineConversion.h"
#include "GeometryCollection/GeometryCollectionObject.h"
#include "GCBatchFractureSettings.h"
#include "HAL/FileManager.h"
#include "Materials/MaterialInterface.h"
#include "Misc/MessageDialog.h"
#include "Misc/PackageName.h"
#include "Misc/ScopedSlowTask.h"
#include "UObject/Package.h"
#include "UObject/SavePackage.h"
#include "UObject/StrongObjectPtr.h"
#include "Tasks/Task.h"

#include <atomic>

#define LOCTEXT_NAMESPACE "GCBatchFractureService"

static bool ValidateSourceStaticMeshComplexity(
	const UStaticMesh* StaticMesh,
	const UGCBatchFractureSettings& Settings,
	FString& OutError)
{
	if (!StaticMesh)
	{
		OutError = TEXT("Static Mesh is null.");
		return false;
	}

	if (!StaticMesh->GetRenderData() ||
		StaticMesh->GetRenderData()->LODResources.IsEmpty())
	{
		OutError = TEXT("Static Mesh has no render data or no LOD resources.");
		return false;
	}

	// AppendStaticMesh reads the max-resolution source geometry. For Nanite meshes,
	// render LOD0 is only the low-poly fallback, so count the Nanite input instead.
	int64 VertexCount = 0;
	int64 TriangleCount = 0;

	if (StaticMesh->HasValidNaniteData())
	{
		const Nanite::FResources& NaniteResources = *StaticMesh->GetRenderData()->NaniteResourcesPtr;
		VertexCount = NaniteResources.NumInputVertices;
		TriangleCount = NaniteResources.NumInputTriangles;
	}
	else
	{
		const FStaticMeshLODResources& LOD0 =
			StaticMesh->GetRenderData()->LODResources[0];

		VertexCount = LOD0.GetNumVertices();
		TriangleCount = LOD0.GetNumTriangles();
	}

	if (Settings.MaxSourceVertices > 0 && VertexCount > Settings.MaxSourceVertices)
	{
		OutError = FString::Printf(
			TEXT("Static Mesh has too many vertices: %lld > %d."),
			VertexCount,
			Settings.MaxSourceVertices);
		return false;
	}

	if (Settings.MaxSourceTriangles > 0 && TriangleCount > Settings.MaxSourceTriangles)
	{
		OutError = FString::Printf(
			TEXT("Static Mesh has too many triangles: %lld > %d."),
			TriangleCount,
			Settings.MaxSourceTriangles);
		return false;
	}

	return true;
}

/**
 * @brief Removes a generated Geometry Collection that could not be completed.
 *
 * The asset exists in memory and its package is dirty when fracture or save fails.
 * Leaving it there would show a broken asset in the Content Browser and make the next
 * batch skip or rename it as if it already existed.
 *
 * @param GeometryCollection Partially generated asset to discard.
 * @param bRegisteredInAssetRegistry True if AssetCreated() was already called for it.
 */
static void DiscardGeneratedAsset(UGeometryCollection* GeometryCollection, bool bRegisteredInAssetRegistry)
{
	if (!GeometryCollection)
	{
		return;
	}

	UPackage* Package = GeometryCollection->GetOutermost();

	if (bRegisteredInAssetRegistry)
	{
		FAssetRegistryModule::AssetDeleted(GeometryCollection);
	}

	GeometryCollection->ClearFlags(RF_Public | RF_Standalone);
	GeometryCollection->Rename(
		nullptr,
		GetTransientPackage(),
		REN_DontCreateRedirectors | REN_NonTransactional | REN_DoNotDirty);
	GeometryCollection->MarkAsGarbage();

	if (Package)
	{
		Package->SetDirtyFlag(false);
	}
}

/**
 * @brief Runs the complete batch process on the selected Content Browser objects.
 *
 * This is the main entry point called by the editor context-menu action. It filters
 * the received objects to keep only unique UStaticMesh assets, validates the batch
 * size, creates one Geometry Collection per mesh, applies the fracture pipeline, and
 * optionally saves each generated asset immediately.
 *
 * Output paths are deterministic:
 * - Source:      /Game/Folder/SM_Asset
 * - Destination: /Game/Folder/GC/GC_SM_Asset
 *
 * @param SelectedObjects Objects selected in the Content Browser.
 * @return A summary containing requested, valid, succeeded, failed and status messages.
 */
FGCBatchFractureResult FGCBatchFractureService::RunOnStaticMeshes(const TArray<UStaticMesh*>& SelectedObjects)
{
	UE_LOG(LogGCBatchFracture, Display,
		TEXT("Starting batch fracture: Requested=%d"),
		SelectedObjects.Num());
	
	FGCBatchFractureResult Result;
	Result.Requested = SelectedObjects.Num();

	// The editor keeps processing input while a batch runs: refuse to start a second one.
	static bool bIsBatchRunning = false;
	if (bIsBatchRunning)
	{
		Result.Messages.Add(TEXT("A batch fracture is already running."));
		UE_LOG(LogGCBatchFracture, Warning, TEXT("A batch fracture is already running. New request ignored."));
		return Result;
	}
	TGuardValue<bool> BatchRunningGuard(bIsBatchRunning, true);

	Result.ValidStaticMeshes = SelectedObjects.Num();

	if (SelectedObjects.IsEmpty())
	{
		Result.Messages.Add(TEXT("No valid UStaticMesh found in the current selection."));
		return Result;
	}

	const UGCBatchFractureSettings* DefaultSettings = GetDefault<UGCBatchFractureSettings>();
	if (!DefaultSettings)
	{
		Result.Messages.Add(TEXT("Could not read GCBatchFracture settings."));
		UE_LOG(LogGCBatchFracture, Error, TEXT("Could not read GCBatchFracture settings."));
		return Result;
	}

	// The fracture runs on a worker thread while the editor stays responsive, so it reads a
	// copy taken now: edits made in Project Settings during the batch must not reach it.
	// The strong pointer keeps the copy alive across the periodic garbage collections.
	const TStrongObjectPtr<UGCBatchFractureSettings> SettingsSnapshot(
		NewObject<UGCBatchFractureSettings>(GetTransientPackage(), NAME_None, RF_Transient));

	for (TFieldIterator<FProperty> PropertyIt(UGCBatchFractureSettings::StaticClass()); PropertyIt; ++PropertyIt)
	{
		PropertyIt->CopyCompleteValue_InContainer(SettingsSnapshot.Get(), DefaultSettings);
	}

	const UGCBatchFractureSettings* Settings = SettingsSnapshot.Get();

	if (!ValidateSelectionCount(SelectedObjects.Num(), *Settings))
	{
		Result.Messages.Add(TEXT("Batch cancelled because of selection safety limits."));
		return Result;
	}

	FScopedSlowTask SlowTask(static_cast<float>(SelectedObjects.Num()), LOCTEXT("BatchFractureProgress", "Generating Geometry Collections..."));
	SlowTask.MakeDialog(true);

	int32 GeneratedSinceLastGC = 0;

	UE_LOG(LogGCBatchFracture, Display,
				TEXT("Processing %d Static Mesh asset(s)."),
				SelectedObjects.Num());
	
	for (UStaticMesh* StaticMesh : SelectedObjects)
	{
		// Checked at the top of the loop so every path, including `continue` on failure, is covered.
		if (Settings->GarbageCollectEveryNAssets > 0 &&
			GeneratedSinceLastGC >= Settings->GarbageCollectEveryNAssets)
		{
			CollectGarbage(GARBAGE_COLLECTION_KEEPFLAGS);
			GeneratedSinceLastGC = 0;
		}

		if (SlowTask.ShouldCancel())
		{
			Result.bCancelled = true;
			Result.Messages.Add(TEXT("Batch cancelled by user."));
			UE_LOG(LogGCBatchFracture, Warning, TEXT("Batch cancelled by user."));
			break;
		}
		const FString DisplayName = StaticMesh ? StaticMesh->GetName() : TEXT("Invalid Static Mesh");
		
		SlowTask.EnterProgressFrame(
			1.0f,
			FText::FromString(FString::Printf(TEXT("Processing %s"), *DisplayName)));
		
		if (!StaticMesh)
		{
			UE_LOG(LogGCBatchFracture, Warning,
				TEXT("Skipped null Static Mesh entry."));

			++Result.Failed;

			continue;
		}

		const FString SourceAssetName = StaticMesh->GetName();
		FString Error;

		// Cheap checks first: a rejected mesh must not leave an empty output folder behind.
		if (!ValidateSourceStaticMeshComplexity(StaticMesh, *Settings, Error))
		{
			UE_LOG(LogGCBatchFracture, Warning,
				TEXT("Rejected source asset '%s': %s"),
				*SourceAssetName,
				*Error);

			++Result.Failed;
			Result.Messages.Add(FString::Printf(
				TEXT("[FAILED] %s : %s"), *SourceAssetName, *Error));
			continue;
		}

		const FString SourcePackagePath =
			FPackageName::GetLongPackagePath(StaticMesh->GetPackage()->GetName());
		const FString DestinationFolder =
			BuildDestinationFolder(SourcePackagePath, *Settings);
		FString DestinationObjectPath;

		const EGCBatchDestinationResult DestinationResult =
			BuildDestinationObjectPath(
				SourcePackagePath,
				SourceAssetName,
				*Settings,
				DestinationObjectPath);

		if (DestinationResult == EGCBatchDestinationResult::Skipped)
		{
			UE_LOG(LogGCBatchFracture, Warning,
				TEXT("Skipped existing Geometry Collection for source asset: %s"),
				*SourceAssetName);

			++Result.Skipped;
			continue;
		}

		if (DestinationResult == EGCBatchDestinationResult::Failed || DestinationObjectPath.IsEmpty())
		{
			UE_LOG(LogGCBatchFracture, Error,
				TEXT("Failed to Fracture for '%s'"),
				*SourceAssetName);

			++Result.Failed;
			continue;
		}
		
		UE_LOG(LogGCBatchFracture, Display,
			TEXT("Processing asset: %s"),
			*SourceAssetName);
		
		if (!EnsureFolderExists(DestinationFolder))
		{
			++Result.Failed;
			Result.Messages.Add(FString::Printf(
				TEXT("[FAILED] %s : could not create/find destination folder '%s'"), *SourceAssetName, *DestinationFolder));
			continue;
		}

		UGeometryCollection* GeometryCollection = CreateGeometryCollectionAssetFromStaticMesh(
			StaticMesh,
			DestinationObjectPath,
			Error);

		if (!GeometryCollection)
		{
			++Result.Failed;
			Result.Messages.Add(FString::Printf(TEXT("[FAILED] %s : %s"), *SourceAssetName, *Error));
			continue;
		}

		// Counted as soon as an asset exists: failed and discarded assets leave garbage
		// behind too, so they must count toward the periodic collection.
		++GeneratedSinceLastGC;
		
		TArray<FString> AssetSafetyMessages;
		bool bCancelledDuringAsset = false;
		if (!ApplyDefaultFractureSettings(GeometryCollection, *Settings, Error, &AssetSafetyMessages, bCancelledDuringAsset))
		{
			DiscardGeneratedAsset(GeometryCollection, false);

			// Cancelled while this asset was being fractured: not a failure of the asset.
			if (bCancelledDuringAsset)
			{
				Result.bCancelled = true;
				Result.Messages.Add(FString::Printf(
					TEXT("Batch cancelled by user while processing %s."), *SourceAssetName));
				UE_LOG(LogGCBatchFracture, Warning,
					TEXT("Batch cancelled by user while processing %s. This asset was discarded."),
					*SourceAssetName);
				break;
			}

			++Result.Failed;
			Result.Messages.Add(FString::Printf(TEXT("[FAILED] %s : %s"), *SourceAssetName, *Error));
			continue;
		}

		// Announced only now that it is complete: while the worker was fracturing it, the
		// Content Browser (thumbnails, etc.) must not read the collection.
		FAssetRegistryModule::AssetCreated(GeometryCollection);

		if (Settings->bSaveAfterEachAsset)
		{
			if (!SavePackageForObject(GeometryCollection, Error))
			{
				DiscardGeneratedAsset(GeometryCollection, true);
				++Result.Failed;
				Result.Messages.Add(FString::Printf(TEXT("[FAILED] %s : %s"), *SourceAssetName, *Error));
				continue;
			}
		}
		
		if (!AssetSafetyMessages.IsEmpty())
		{
			++Result.SafetyLimited;

			for (const FString& SafetyMessage : AssetSafetyMessages)
			{
				const FString FullMessage = FString::Printf(
					TEXT("[LIMITED] %s : %s"),
					*SourceAssetName,
					*SafetyMessage);

				Result.SafetyMessages.Add(FullMessage);
				Result.Messages.Add(FullMessage);
			}
		}

		UE_LOG(LogGCBatchFracture, Display,
			TEXT("Generated Geometry Collection: %s -> %s"),
			*SourceAssetName,
			*DestinationObjectPath);
				
		++Result.Succeeded;
		Result.Messages.Add(FString::Printf(TEXT("[OK] %s -> %s"), *SourceAssetName, *DestinationObjectPath));
	}

	UE_LOG(LogGCBatchFracture, Display,
		TEXT("Batch fracture completed. Requested=%d Succeeded=%d Skipped=%d Failed=%d SafetyLimited=%d"),
		Result.Requested,
		Result.Succeeded,
		Result.Skipped,
		Result.Failed,
		Result.SafetyLimited);
	
	// Failure reasons are otherwise only in Result.Messages, which nothing displays.
	for (const FString& Message : Result.Messages)
	{
		if (Message.StartsWith(TEXT("[FAILED]")))
		{
			UE_LOG(LogGCBatchFracture, Error, TEXT("%s"), *Message);
		}
	}

	if (!Result.SafetyMessages.IsEmpty())
	{
		UE_LOG(LogGCBatchFracture, Warning,
			TEXT("Some assets were generated with safety limitations:"));

		for (const FString& SafetyMessage : Result.SafetyMessages)
		{
			UE_LOG(LogGCBatchFracture, Warning,
				TEXT("  %s"),
				*SafetyMessage);
		}
	}
	
	return Result;
}

/**
 * @brief Marks an asset package as dirty without triggering unused-result warnings.
 *
 * UObject::MarkPackageDirty() returns a boolean, but this tool does not need to
 * branch on that result for normal asset generation. This helper centralizes the
 * call and logs the result only at Verbose level.
 *
 * @param Object Asset or object whose outer package should be marked dirty.
 */
static void MarkAssetDirty(UObject* Object)
{
	if (!Object)
	{
		return;
	}

	(void)Object->MarkPackageDirty();
}

/**
 * @brief Validates the number of Static Mesh assets selected for batch processing.
 *
 * Uses the plugin safety settings to block very large selections and warn the user
 * before processing moderately large selections. This prevents accidental long jobs
 * or memory-heavy batches.
 *
 * @param Count Number of valid Static Mesh assets selected.
 * @return True if the batch may continue; false if it should be cancelled.
 */
bool FGCBatchFractureService::ValidateSelectionCount(int32 Count, const UGCBatchFractureSettings& Settings)
{
	if (Count > Settings.HardSelectionBlockCount)
	{
		FMessageDialog::Open(
			EAppMsgType::Ok,
			FText::FromString(FString::Printf(
				TEXT("%d Static Mesh assets selected. Safety block is set to %d. Reduce the selection or raise the limit in Project Settings > Plugins > GC Batch Fracture."),
				Count,
				Settings.HardSelectionBlockCount)));
		UE_LOG(LogGCBatchFracture, Warning, TEXT("Selection count exceeded hard limit: %d > %d"), Count, Settings.HardSelectionBlockCount);
		return false;
	}

	if (Count > Settings.SoftSelectionWarningCount)
	{
		const EAppReturnType::Type Choice = FMessageDialog::Open(
			EAppMsgType::YesNo,
			FText::FromString(FString::Printf(
				TEXT("%d Static Mesh assets selected. This may take time and memory. Continue?"),
				Count)));
		UE_LOG(LogGCBatchFracture, Display, TEXT("Selection count exceeded soft limit: %d > %d"), Count, Settings.SoftSelectionWarningCount);
		return Choice == EAppReturnType::Yes;
	}
	return true;
}

/**
 * @brief Builds the destination folder for generated Geometry Collection assets.
 *
 * The folder is created next to the source mesh folder, using the configurable
 * OutputSubfolder setting. For example: /Game/Boats -> /Game/Boats/GC.
 *
 * @param SourcePackagePath Long package path of the source mesh folder.
 * @return Long package path of the destination folder.
 */
FString FGCBatchFractureService::BuildDestinationFolder(
	const FString& SourcePackagePath,
	const UGCBatchFractureSettings& Settings)
{
	return SourcePackagePath / Settings.OutputSubfolder;
}

/**
 * @brief Builds the full destination object path for a generated Geometry Collection.
 *
 * The generated asset is placed in the configured output subfolder and receives the
 * configured name prefix.
 *
 * Example:
 * - Source folder: /Game/Boats
 * - Source asset:  SM_Boat_01
 * - Output asset:  /Game/Boats/GC/GC_SM_Boat_01.GC_SM_Boat_01
 *
 * @param SourcePackagePath Long package path of the source mesh folder.
 * @param SourceAssetName Name of the source Static Mesh asset.
 * @param OutDestinationObjectPath
 * @return Full object path of the generated Geometry Collection asset.
 */
EGCBatchDestinationResult FGCBatchFractureService::BuildDestinationObjectPath(
	const FString& SourcePackagePath,
	const FString& SourceAssetName,
	const UGCBatchFractureSettings& Settings,
	FString& OutDestinationObjectPath)
{
	OutDestinationObjectPath.Reset();

	const FString DestinationFolder = BuildDestinationFolder(SourcePackagePath, Settings);
	const FString DesiredAssetName = Settings.NamePrefix + SourceAssetName;
	const FString DesiredPackageName = DestinationFolder / DesiredAssetName;
	const FString DesiredObjectPath = DesiredPackageName + TEXT(".") + DesiredAssetName;

	if (!DoesAssetAlreadyExist(DesiredPackageName, DesiredAssetName))
	{
		OutDestinationObjectPath = DesiredObjectPath;
		return EGCBatchDestinationResult::Valid;
	}

	if (Settings.bSkipExistingAssets)
	{
		return EGCBatchDestinationResult::Skipped;
	}

	FAssetToolsModule& AssetToolsModule =
		FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools");

	FString UniquePackageName;
	FString UniqueAssetName;

	AssetToolsModule.Get().CreateUniqueAssetName(
		DesiredPackageName,
		TEXT(""),
		UniquePackageName,
		UniqueAssetName
	);

	if (UniquePackageName.IsEmpty() || UniqueAssetName.IsEmpty())
	{
		return EGCBatchDestinationResult::Failed;
	}

	OutDestinationObjectPath = UniquePackageName + TEXT(".") + UniqueAssetName;

	return EGCBatchDestinationResult::Valid;
}

bool FGCBatchFractureService::DoesAssetAlreadyExist(
	const FString& PackageName,
	const FString& AssetName)
{
	const FString ObjectPath = PackageName + TEXT(".") + AssetName;

	if (StaticFindObject(nullptr, nullptr, *ObjectPath))
	{
		return true;
	}

	return FPackageName::DoesPackageExist(PackageName);
}

/**
 * @brief Ensures that a long package folder exists on disk.
 *
 * Converts an Unreal long package path, such as /Game/Boats/GC, to a filesystem
 * path and creates the directory if needed.
 *
 * @param LongPackagePath Destination folder as an Unreal long package path.
 * @return True if the folder exists or was created successfully.
 */
bool FGCBatchFractureService::EnsureFolderExists(const FString& LongPackagePath)
{
	FString Filename;
	if (!FPackageName::TryConvertLongPackageNameToFilename(LongPackagePath, Filename))
	{
		return false;
	}

	return IFileManager::Get().MakeDirectory(*Filename, true);
}

/**
 * @brief Saves a generated asset package to disk.
 *
 * The batch process saves each generated Geometry Collection as soon as it is ready,
 * which makes long batch operations safer. If Unreal crashes or the user cancels
 * later, already processed assets are preserved.
 *
 * @param ObjectToSave Asset object to save.
 * @param OutError Filled with a human-readable error if saving fails.
 * @return True if the package was saved successfully.
 */
bool FGCBatchFractureService::SavePackageForObject(UObject* ObjectToSave, FString& OutError)
{
	if (!ObjectToSave)
	{
		OutError = TEXT("SavePackageForObject received a null object.");
		return false;
	}

	UPackage* Package = ObjectToSave->GetOutermost();
	if (!Package)
	{
		OutError = TEXT("Object has no package.");
		return false;
	}

	const FString PackageName = Package->GetName();
	FString Filename;
	if (!FPackageName::TryConvertLongPackageNameToFilename(PackageName, Filename, FPackageName::GetAssetPackageExtension()))
	{
		OutError = FString::Printf(TEXT("Could not convert package path '%s' to filename."), *PackageName);
		return false;
	}

	FSavePackageArgs SaveArgs;
	SaveArgs.TopLevelFlags = EObjectFlags::RF_Public | EObjectFlags::RF_Standalone;
	SaveArgs.SaveFlags = SAVE_NoError;

	const bool bSaved = UPackage::SavePackage(Package, ObjectToSave, *Filename, SaveArgs);
	if (!bSaved)
	{
		OutError = FString::Printf(TEXT("Failed to save package '%s'"), *Filename);
		return false;
	}

	return true;
}

/**
 * @brief Generates deterministic Voronoi sites inside each of the given bounding boxes.
 *
 * NumSitesPerBounds sites are generated inside every box, so each selected piece
 * receives its own sites and is actually cut, whatever its size relative to the
 * whole collection. The seed makes the result reproducible: the same mesh,
 * settings and seed produce the same site distribution.
 *
 * @param BoundsList Collection-space bounds, one per piece to fracture.
 * @param NumSitesPerBounds Number of Voronoi sites to generate inside each box.
 * @param RandomSeed Seed used by the deterministic random stream.
 * @param OutSites Filled with generated site positions.
 */
static void GenerateVoronoiSitesInBounds(
	const TArray<FBox>& BoundsList,
	int32 NumSitesPerBounds,
	int32 RandomSeed,
	TArray<FVector>& OutSites)
{
	OutSites.Reset();

	if (NumSitesPerBounds <= 0)
	{
		return;
	}

	OutSites.Reserve(BoundsList.Num() * NumSitesPerBounds);

	FRandomStream RandomStream(RandomSeed);

	for (const FBox& Bounds : BoundsList)
	{
		if (!Bounds.IsValid)
		{
			continue;
		}

		for (int32 Index = 0; Index < NumSitesPerBounds; ++Index)
		{
			const FVector Alpha(
				RandomStream.FRand(),
				RandomStream.FRand(),
				RandomStream.FRand());

			const FVector Site(
				FMath::Lerp(Bounds.Min.X, Bounds.Max.X, Alpha.X),
				FMath::Lerp(Bounds.Min.Y, Bounds.Max.Y, Alpha.Y),
				FMath::Lerp(Bounds.Min.Z, Bounds.Max.Z, Alpha.Z));

			OutSites.Add(Site);
		}
	}
}

/**
 * @brief Builds a valid Dataflow transform selection from transform indices.
 *
 * FractureEngine functions expect an FDataflowTransformSelection. In UE 5.6, that
 * selection must be explicitly initialized with the current transform count before
 * calling SetSelected(). Otherwise its internal bit array remains empty and the
 * fracture call can fail with mismatched selection sizes.
 *
 * @param Collection Geometry Collection that owns the selected transforms.
 * @param TransformIndices Transform indices to select.
 * @param OutSelection Filled with a valid selection if possible.
 * @return True if the selection is valid for the collection and contains at least one selected transform.
 */
static bool BuildTransformSelection(
	const FGeometryCollection& Collection,
	const TArray<int32>& TransformIndices,
	FDataflowTransformSelection& OutSelection)
{
	const int32 NumTransforms = Collection.NumElements(FGeometryCollection::TransformGroup);

	OutSelection.Initialize(NumTransforms, false);

	for (const int32 TransformIndex : TransformIndices)
	{
		if (TransformIndex >= 0 && TransformIndex < NumTransforms)
		{
			OutSelection.SetSelected(TransformIndex);
		}
	}

	return OutSelection.IsValidForCollection(Collection) && OutSelection.NumSelected() > 0;
}

/**
 * @brief Computes the collection-space bounding box of each given transform.
 *
 * Geometry bounds are stored relative to their own transform, so they are moved to
 * collection space with the global matrices, the same space VoronoiFracture expects
 * its sites in. These per-piece bounds are later used to generate Voronoi sites.
 *
 * @param Collection Geometry Collection to inspect. Its geometry bounds are refreshed.
 * @param TransformIndices Geometry-owning transforms whose bounds are requested.
 * @param OutBoundsList Filled with one valid box per transform that has geometry.
 * @return True if at least one valid bounding box was computed.
 */
static bool BuildBoundsForTransforms(
	FGeometryCollection& Collection,
	const TArray<int32>& TransformIndices,
	TArray<FBox>& OutBoundsList)
{
	OutBoundsList.Reset();

	Collection.UpdateBoundingBox();

	TArray<FMatrix> GlobalMatrices;
	GeometryCollectionAlgo::GlobalMatrices(Collection.Transform, Collection.Parent, GlobalMatrices);

	for (const int32 TransformIndex : TransformIndices)
	{
		if (!GlobalMatrices.IsValidIndex(TransformIndex))
		{
			continue;
		}

		const int32 GeometryIndex = Collection.TransformToGeometryIndex[TransformIndex];
		if (!Collection.BoundingBox.IsValidIndex(GeometryIndex))
		{
			continue;
		}

		const FBox Bounds = Collection.BoundingBox[GeometryIndex].TransformBy(GlobalMatrices[TransformIndex]);
		if (Bounds.IsValid)
		{
			OutBoundsList.Add(Bounds);
		}
	}

	return !OutBoundsList.IsEmpty();
}

/**
 * @brief Collects transforms that are linked to actual geometry.
 *
 * Geometry Collections can contain transforms for roots, clusters, parents and
 * renderable pieces. Only transforms with a valid TransformToGeometryIndex can be
 * directly fractured as geometry-owning pieces.
 *
 * @param Collection Geometry Collection to inspect.
 * @param OutTransformIndices Filled with geometry-owning transform indices.
 */
static void GetGeometryTransformIndices(
	const FGeometryCollection& Collection,
	TArray<int32>& OutTransformIndices)
{
	OutTransformIndices.Reset();

	for (int32 TransformIndex = 0; TransformIndex < Collection.TransformToGeometryIndex.Num(); ++TransformIndex)
	{
		if (Collection.TransformToGeometryIndex[TransformIndex] != INDEX_NONE)
		{
			OutTransformIndices.Add(TransformIndex);
		}
	}
}

/**
 * @brief Generates convex collision hulls required by Chaos runtime simulation.
 *
 * Voronoi fracture creates visible pieces, but runtime physics needs implicit
 * collision shapes. This function initializes convex-hull attributes, generates
 * hulls for leaf pieces, and generates cluster hulls from their children so the
 * collection can collide properly in-game.
 *
 * @param Collection Fractured collection to prepare for runtime collision.
 */
static void GenerateCollisionHullsForGeometryCollection(FGeometryCollection& Collection, const UGCBatchFractureSettings& Settings)
{
	FGeometryCollectionConvexPropertiesInterface ConvexPropertiesInterface(&Collection);
	ConvexPropertiesInterface.InitializeInterface();
	if (Settings.bGenerateLeafConvexHulls)
	{
		const bool bRestrictToSelection = false;
		const TArray<int32> SelectedBones;
		const float SimplificationDistanceThreshold = 10.0f;

		FGeometryCollectionConvexUtility::FLeafConvexHullSettings LeafSettings(
			SimplificationDistanceThreshold,
			EGenerateConvexMethod::ComputedFromGeometry);

		TArray<FGeometryCollectionConvexUtility::FSphereCoveringInfo> SphereCoverings;
	
		FGeometryCollectionConvexUtility::GenerateLeafConvexHulls(
			Collection,
			bRestrictToSelection,
			SelectedBones,
			LeafSettings,
			&SphereCoverings);
	}
	if (Settings.bGenerateClusterConvexHulls)
	{
		const int32 ConvexCount = 1;
		const double ErrorToleranceInCm = 10.0;
		const bool bPreferExternalCollisionShapes = false;

		FGeometryCollectionConvexUtility::FClusterConvexHullSettings ClusterSettings(
			ConvexCount,
			ErrorToleranceInCm,
			bPreferExternalCollisionShapes);

		ClusterSettings.bAllowMergingLeafHulls = true;
		
		FGeometryCollectionConvexUtility::GenerateClusterConvexHullsFromChildrenHulls(
			Collection,
			ClusterSettings);
	}
	
	if (Settings.bCreateNonOverlappingConvexHulls)
	{
		UE_LOG(LogGCBatchFracture, Warning,
			TEXT("Non-overlapping convex hull generation is enabled. This can be slow and should be considered experimental for large batches."));

		const double NonOverlapStartTime = FPlatformTime::Seconds();

		const float CanRemoveFraction = 0.3f;
		const float SimplificationDistanceThreshold = 10.0f;
		const float CanExceedFraction = 0.5f;
		const float OverlapRemovalShrinkPercent = 0.0f;

		FGeometryCollectionConvexUtility::CreateNonOverlappingConvexHullData(
			&Collection,
			CanRemoveFraction,
			SimplificationDistanceThreshold,
			CanExceedFraction,
			EConvexOverlapRemoval::All,
			OverlapRemovalShrinkPercent
		);

		UE_LOG(LogGCBatchFracture, Verbose,
			TEXT("CreateNonOverlappingConvexHullData took %.3f seconds"),
			FPlatformTime::Seconds() - NonOverlapStartTime);
	}
}

/**
 * @brief Builds a selection containing every transform that owns geometry.
 *
 * Used by cleanup/finalization steps, especially FixTinyGeo, where the operation
 * should inspect all physical pieces rather than only the last fracture selection.
 *
 * @param Collection Geometry Collection to inspect.
 * @param OutSelection Filled with all geometry-owning transforms.
 * @return True if the selection is valid and non-empty.
 */
static bool BuildSelectionForAllGeometryTransforms(
	const FGeometryCollection& Collection,
	FDataflowTransformSelection& OutSelection)
{
	const int32 NumTransforms = Collection.NumElements(FGeometryCollection::TransformGroup);

	OutSelection.Initialize(NumTransforms, false);

	for (int32 TransformIndex = 0; TransformIndex < Collection.TransformToGeometryIndex.Num(); ++TransformIndex)
	{
		if (Collection.TransformToGeometryIndex[TransformIndex] != INDEX_NONE)
		{
			OutSelection.SetSelected(TransformIndex);
		}
	}

	return OutSelection.IsValidForCollection(Collection) && OutSelection.NumSelected() > 0;
}

/**
 * @brief Removes invalid or useless generated collection data after fracture.
 *
 * Fracture operations can leave unreferenced geometry, clusters of one, or dangling
 * clusters. Cleaning those up reduces unstable simulation data and unnecessary
 * runtime work before collision hulls are generated.
 *
 * @param Collection Geometry Collection to validate and clean.
 */
static void ValidateFracturedGeometryCollection(FGeometryCollection& Collection)
{
	FFractureEngineUtility::ValidateGeometryCollection(
		Collection,
		true,
		true,
		true);
}

/**
 * @brief Merges or fixes fragments that are too small for reliable Chaos simulation.
 *
 * Very small fracture pieces can generate missing or invalid implicit collision
 * geometry. This can cause Chaos warnings such as "Some geometry is too small to
 * be simulated" or, in worse cases, a null physics geometry ensure at runtime.
 *
 * @param Collection Fractured collection to clean.
 * @param TinyGeometryMinSizeCm Minimum fragment size, expressed as the cube root of volume in centimeters.
 */
static void FixTinyGeometryForSimulation(FGeometryCollection& Collection, float TinyGeometryMinSizeCm)
{
	FDataflowTransformSelection TransformSelection;

	if (!BuildSelectionForAllGeometryTransforms(Collection, TransformSelection))
	{
		UE_LOG(LogGCBatchFracture, Warning, TEXT("FixTinyGeo skipped: no valid transform selection."));
		return;
	}

	FFractureEngineUtility::FixTinyGeo(
		Collection,
		TransformSelection,
		EFixTinyGeoMergeType::MergeGeometry,
		true,
		EFixTinyGeoGeometrySelectionMethod::VolumeCubeRoot,
		TinyGeometryMinSizeCm,
		0.01f,
		EFixTinyGeoUseBoneSelection::NoEffect,
		false,
		EFixTinyGeoNeighborSelectionMethod::LargestNeighbor,
		true,
		true,
		false);
}

/**
 * @brief Creates a new Geometry Collection asset from a source Static Mesh.
 *
 * This is the first asset-generation step. It creates the destination package and
 * UGeometryCollection object, copies source materials, stores GeometrySource
 * metadata, and appends the Static Mesh geometry into the collection.
 *
 * This function deliberately does not build final render data, convex hulls or
 * simulation data. Those are generated later, after the fracture passes, because
 * the collection structure changes during fracture.
 *
 * @param SourceMesh Static Mesh to convert.
 * @param DestinationObjectPath Full object path of the generated Geometry Collection.
 * @param OutError Filled with a human-readable error if creation fails.
 * @return Newly created Geometry Collection asset, or nullptr on failure.
 */
UGeometryCollection* FGCBatchFractureService::CreateGeometryCollectionAssetFromStaticMesh(
	UStaticMesh* SourceMesh,
	const FString& DestinationObjectPath,
	FString& OutError)
{
	if (!SourceMesh)
	{
		OutError = TEXT("Source mesh is null.");
		return nullptr;
	}
		
	if (StaticFindObject(nullptr, nullptr, *DestinationObjectPath))
	{
		OutError = FString::Printf(
			TEXT("Destination asset is already loaded. Refusing to overwrite: %s"),
			*DestinationObjectPath);

		return nullptr;
	}
	
	const int32 DotIndex = DestinationObjectPath.Find(TEXT("."), ESearchCase::IgnoreCase, ESearchDir::FromEnd);
	const FString LongPackageName = (DotIndex != INDEX_NONE)
		? DestinationObjectPath.Left(DotIndex)
		: DestinationObjectPath;
	const FString AssetName = FPackageName::GetLongPackageAssetName(LongPackageName);

	UPackage* Package = CreatePackage(*LongPackageName);
	if (!Package)
	{
		OutError = FString::Printf(TEXT("Could not create package '%s'"), *LongPackageName);
		return nullptr;
	}

	UGeometryCollection* GeometryCollection = NewObject<UGeometryCollection>(
		Package,
		UGeometryCollection::StaticClass(),
		*AssetName,
		RF_Public | RF_Standalone | RF_Transactional);

	if (!GeometryCollection)
	{
		OutError = TEXT("Could not allocate UGeometryCollection.");
		return nullptr;
	}

	GeometryCollection->Modify();
	GeometryCollection->SetFlags(RF_Public | RF_Standalone | RF_Transactional);

	if (GeometryCollection->SizeSpecificData.IsEmpty())
	{
		GeometryCollection->SizeSpecificData.Add(FGeometryCollectionSizeSpecificData());
	}

	TArray<TObjectPtr<UMaterialInterface>> Materials;
	Materials.Reserve(SourceMesh->GetStaticMaterials().Num());

	for (int32 MaterialIndex = 0; MaterialIndex < SourceMesh->GetStaticMaterials().Num(); ++MaterialIndex)
	{
		Materials.Add(SourceMesh->GetMaterial(MaterialIndex));
	}

	const FSoftObjectPath SourcePath(SourceMesh);

	GeometryCollection->GeometrySource.Empty();
	GeometryCollection->GeometrySource.Add({
		SourcePath,
		FTransform::Identity,
		Materials,
		true,
		true
	});

	FGeometryCollectionEngineConversion::AppendStaticMesh(
		SourceMesh,
		Materials,
		FTransform::Identity,
		GeometryCollection,
		false,
		true,
		false);

	GeometryCollection->InitializeMaterials(false);
	MarkAssetDirty(GeometryCollection);

	// Not registered in the Asset Registry here: RunOnStaticMeshes() announces the asset
	// once the fracture pipeline has completed.

	OutError.Reset();
	return GeometryCollection;
}

/**
 * @brief Applies one Voronoi fracture pass to the current Geometry Collection.
 *
 * A fracture level is one pass over the currently geometry-owning pieces. Level 0
 * usually fractures the original mesh/root. Higher levels refracture the pieces
 * produced by earlier passes, which can become expensive very quickly.
 *
 * @param AssetName Name of the asset being generated. Used for logs/errors only, so the
 *        function never touches the UObject and can run on a worker thread.
 * @param Collection Internal collection data to modify.
 * @param Settings Plugin settings controlling fracture parameters.
 * @param LevelIndex Current fracture level index.
 * @param OutError Filled with a human-readable error if fracture fails.
 * @return True if the pass produced additional transforms.
 */
static bool FractureOneLevel(
	const FString& AssetName,
	FGeometryCollection& Collection,
	const UGCBatchFractureSettings& Settings,
	int32 LevelIndex,
	FString& OutError,
	TArray<FString>* OutSafetyMessages)
{
	const int32 LevelSeed = Settings.RandomSeed + LevelIndex * Settings.RandomSeedOffsetPerLevel;
	const int32 NumTransformsBefore = Collection.NumElements(FGeometryCollection::TransformGroup);
	const int32 NumVerticesBefore = Collection.NumElements(FGeometryCollection::VerticesGroup);
	const int32 NumFacesBefore = Collection.NumElements(FGeometryCollection::FacesGroup);

	if (NumVerticesBefore <= 0 || NumFacesBefore <= 0)
	{
		OutError = TEXT("GeometryCollection has no vertices/faces to fracture.");
		return false;
	}
	
	TArray<int32> TransformIndicesToFracture;
	GetGeometryTransformIndices(Collection, TransformIndicesToFracture);

	if (TransformIndicesToFracture.IsEmpty())
	{
		OutError = TEXT("No geometry transform found to fracture.");
		return false;
	}

	FDataflowTransformSelection TransformSelection;

	
	
	if (LevelIndex > 0 && Settings.PerLevelChanceToFracture < 1.0f)
	{
		TArray<int32> FilteredTransforms;

		const int32 SelectionSeed =
			Settings.RandomSeed
			+ LevelIndex * Settings.RandomSeedOffsetPerLevel
			+ 9999;

		FRandomStream SelectionRandomStream(SelectionSeed);

		for (const int32 TransformIndex : TransformIndicesToFracture)
		{
			if (SelectionRandomStream.FRand() <= Settings.PerLevelChanceToFracture)
			{
				FilteredTransforms.Add(TransformIndex);
			}
		}

		TransformIndicesToFracture = MoveTemp(FilteredTransforms);
	}
	
	// Filtrage par chance et set des MaxTransforms
	if (Settings.MaxTransformsToFracturePerLevel > 0 &&
	TransformIndicesToFracture.Num() > Settings.MaxTransformsToFracturePerLevel)
	{
		const int32 SelectionSeed =
			Settings.RandomSeed
			+ LevelIndex * Settings.RandomSeedOffsetPerLevel
			+ 12345;

		FRandomStream SelectionRandomStream(SelectionSeed);

		for (int32 Index = TransformIndicesToFracture.Num() - 1; Index > 0; --Index)
		{
			const int32 SwapIndex = SelectionRandomStream.RandRange(0, Index);
			TransformIndicesToFracture.Swap(Index, SwapIndex);
		}

		TransformIndicesToFracture.SetNum(Settings.MaxTransformsToFracturePerLevel);
	}

	const int32 EstimatedFractureOperations = TransformIndicesToFracture.Num() * Settings.VoronoiSites;
	
	
	if (Settings.MaxEstimatedFractureOperationsPerLevel > 0 &&
		EstimatedFractureOperations > Settings.MaxEstimatedFractureOperationsPerLevel)
	{
		const FString SafetyMessage = FString::Printf(
		TEXT("Skipping fracture level %d for '%s': estimated work is too high (%d > %d). SelectedTransforms=%d Sites=%d"),
			LevelIndex,
			*AssetName,
			EstimatedFractureOperations,
			Settings.MaxEstimatedFractureOperationsPerLevel,
			TransformIndicesToFracture.Num(),
			Settings.VoronoiSites);

		UE_LOG(LogGCBatchFracture, Warning, TEXT("%s"), *SafetyMessage);

		if (OutSafetyMessages)
		{
			OutSafetyMessages->Add(SafetyMessage);
		}

		if (LevelIndex == 0)
		{
			OutError = SafetyMessage;
			return false;
		}

		return true;
	}
	
	if (!BuildTransformSelection(Collection, TransformIndicesToFracture, TransformSelection))
	{
		OutError = FString::Printf(
			TEXT("Could not build valid transform selection for level %d."),
			LevelIndex);
		return false;
	}
	
	TArray<FBox> BoundsList;
	if (!BuildBoundsForTransforms(Collection, TransformIndicesToFracture, BoundsList))
	{
		OutError = FString::Printf(
			TEXT("Could not compute bounds for fracture level %d."),
			LevelIndex);
		return false;
	}

	TArray<FVector> VoronoiSites;
	GenerateVoronoiSitesInBounds(
		BoundsList,
		Settings.VoronoiSites,
		LevelSeed,
		VoronoiSites);

	if (VoronoiSites.IsEmpty())
	{
		OutError = FString::Printf(
			TEXT("No Voronoi sites generated for fracture level %d."),
			LevelIndex);
		return false;
	}

	const int32 FractureResult = FFractureEngineFracturing::VoronoiFracture(
		Collection,
		TransformSelection,
		MoveTemp(VoronoiSites), // Taken by value by the engine: move instead of copying.
		FTransform::Identity,
		LevelSeed,
		Settings.ChanceToFracture,
		Settings.bSplitIslands,
		Settings.Grout,
		Settings.Amplitude,
		Settings.Frequency,
		Settings.Persistence,
		Settings.Lacunarity,
		Settings.OctaveNumber,
		Settings.PointSpacing,
		Settings.bAddSamplesForCollision,
		// UE 5.6/5.7 ignore bAddSamplesForCollision and add samples whenever the spacing is
		// > 0, so the spacing must be 0 to really disable them (a tiny spacing never ends).
		Settings.bAddSamplesForCollision ? Settings.CollisionSampleSpacing : 0.0f);

	const int32 NumTransformsAfter = Collection.NumElements(FGeometryCollection::TransformGroup);

	if (FractureResult <= 0 || NumTransformsAfter <= NumTransformsBefore)
	{
		// Level 0 must produce pieces, otherwise there is nothing to simulate.
		if (LevelIndex == 0)
		{
			OutError = TEXT("Voronoi fracture level 0 failed or did not create new transforms.");
			return false;
		}

		// A secondary level with no effect (e.g. ChanceToFracture rejected every piece)
		// keeps the pieces from the previous levels instead of failing the whole asset.
		const FString SafetyMessage = FString::Printf(
			TEXT("Fracture level %d for '%s' did not create new transforms and was ignored."),
			LevelIndex,
			*AssetName);

		UE_LOG(LogGCBatchFracture, Warning, TEXT("%s"), *SafetyMessage);

		if (OutSafetyMessages)
		{
			OutSafetyMessages->Add(SafetyMessage);
		}
	}
	return true;
}

/**
 * @brief State shared between the game thread and the worker running the fracture pipeline.
 *
 * Atomics are polled while the worker runs. The other fields are written by the worker
 * only, and read by the game thread once the task has completed.
 */
struct FGCBatchFractureJob
{
	/** Number of pipeline steps completed by the worker (levels, cleanup, hulls). */
	std::atomic<int32> CompletedSteps{0};

	/** Set by the game thread when the user cancels; checked by the worker between steps. */
	std::atomic<bool> bCancelRequested{false};

	bool bSucceeded = false;
	FString Error;
	TArray<FString> SafetyMessages;
};

/**
 * @brief Runs the pure-data part of the pipeline: fracture levels, cleanup and collision hulls.
 *
 * Only FGeometryCollection data is touched here, never a UObject, so this runs on a worker
 * thread while the game thread keeps the editor and the progress dialog responsive.
 * An engine call that has started cannot be interrupted: cancellation is checked between steps.
 *
 * Steps reported through Job.CompletedSteps: one per fracture level, then cleanup, then hulls.
 *
 * @param Collection Collection to fracture. Kept alive by the caller for the whole task.
 * @param Settings Settings snapshot, kept alive by the caller for the whole task.
 * @param AssetName Name of the asset being generated, for logs only.
 * @param Job Shared progress, cancellation and result state.
 */
static void RunFracturePipelineOnWorker(
	FGeometryCollection& Collection,
	const UGCBatchFractureSettings& Settings,
	const FString& AssetName,
	FGCBatchFractureJob& Job)
{
	for (int32 LevelIndex = 0; LevelIndex < Settings.FractureLevelCount; ++LevelIndex)
	{
		if (Job.bCancelRequested)
		{
			return;
		}

		if (!FractureOneLevel(
			AssetName,
			Collection,
			Settings,
			LevelIndex,
			Job.Error,
			&Job.SafetyMessages))
		{
			return;
		}

		++Job.CompletedSteps;

		const int32 CurrentTransformCount =
			Collection.NumElements(FGeometryCollection::TransformGroup);

		if (Settings.MaxTransformsAfterFracture > 0 &&
			CurrentTransformCount > Settings.MaxTransformsAfterFracture)
		{
			const FString SafetyMessage = FString::Printf(
				TEXT("Stopping further fracture levels for '%s': CurrentTransforms=%d MaxTransforms=%d"),
				*AssetName,
				CurrentTransformCount,
				Settings.MaxTransformsAfterFracture);

			UE_LOG(LogGCBatchFracture, Warning, TEXT("%s"), *SafetyMessage);
			Job.SafetyMessages.Add(SafetyMessage);
			break;
		}
	}

	// Skipped levels still count, so progress continues from the cleanup step.
	Job.CompletedSteps = Settings.FractureLevelCount;

	if (Job.bCancelRequested)
	{
		return;
	}

	Collection.UpdateBoundingBox();
	FGeometryCollectionConvexUtility::SetVolumeAttributes(&Collection);

	if (Settings.bFixTinyGeometry)
	{
		FixTinyGeometryForSimulation(
			Collection,
			Settings.TinyGeometryMinSizeCm);
	}

	if (Settings.bValidateGeometryCollectionAfterFracture)
	{
		ValidateFracturedGeometryCollection(Collection);
	}

	++Job.CompletedSteps;

	if (Job.bCancelRequested)
	{
		return;
	}

	GenerateCollisionHullsForGeometryCollection(Collection, Settings);
	GeometryCollectionAlgo::PrepareForSimulation(&Collection);

	++Job.CompletedSteps;
	Job.bSucceeded = true;
}

/**
 * @brief Finalizes a fractured Geometry Collection for runtime use. Game thread only.
 *
 * Called once the worker has fractured the collection and generated its collision hulls.
 * These calls touch the UObject and render resources, so they cannot run on the worker.
 *
 * @param GeometryCollection Asset being generated.
 */
static void FinalizeFracturedGeometryCollection(UGeometryCollection* GeometryCollection)
{
	if (!GeometryCollection)
	{
		return;
	}

	GeometryCollection->InvalidateCollection();
	GeometryCollection->CreateSimulationData();

	GeometryCollection->InitializeMaterials();
	GeometryCollection->RebuildRenderData();

	MarkAssetDirty(GeometryCollection);
}

/**
 * @brief Progress text of a pipeline step, as shown in the progress dialog.
 */
static FText GetPipelineStepText(int32 StepIndex, int32 FractureLevelCount)
{
	if (StepIndex < FractureLevelCount)
	{
		return FText::Format(
			LOCTEXT("FractureLevelProgress", "Fracture level {0} / {1}"),
			FText::AsNumber(StepIndex + 1),
			FText::AsNumber(FractureLevelCount));
	}

	switch (StepIndex - FractureLevelCount)
	{
	case 0:
		return LOCTEXT("FinalizeCleanup", "Cleaning up fragments...");
	case 1:
		return LOCTEXT("FinalizeHulls", "Generating collision hulls...");
	default:
		return LOCTEXT("FinalizeSimulation", "Building simulation and render data...");
	}
}

/**
 * @brief Applies the complete configured fracture pipeline to one Geometry Collection.
 *
 * The fracture levels, cleanup and collision hulls run on a worker thread
 * (RunFracturePipelineOnWorker). Meanwhile the game thread keeps the progress dialog
 * responsive and reads the cancel button. Simulation and render data are then built
 * on the game thread (FinalizeFracturedGeometryCollection).
 *
 * On cancellation, the worker stops at the next step boundary: an engine call already
 * running cannot be interrupted, so the dialog shows that it is waiting for it.
 *
 * @param GeometryCollection Geometry Collection asset to fracture and finalize.
 * @param Settings Settings snapshot, kept alive by the caller during the call.
 * @param OutError Filled with a human-readable error if the operation fails or is cancelled.
 * @param OutSafetyMessages Filled with the safety limitations applied to this asset.
 * @param bOutCancelled Set to true if the user cancelled while this asset was processed.
 * @return True if the asset was fractured and finalized successfully.
 */
bool FGCBatchFractureService::ApplyDefaultFractureSettings(
		UGeometryCollection* GeometryCollection,
		const UGCBatchFractureSettings& Settings,
		FString& OutError,
		TArray<FString>* OutSafetyMessages,
		bool& bOutCancelled)
{
	bOutCancelled = false;

	if (!GeometryCollection)
	{
		OutError = TEXT("GeometryCollection is null.");
		return false;
	}

	TSharedPtr<FGeometryCollection, ESPMode::ThreadSafe> Collection = GeometryCollection->GetGeometryCollection();

	if (!Collection.IsValid())
	{
		OutError = TEXT("Internal FGeometryCollection is invalid.");
		return false;
	}

	const int32 FinalizeStepCount = 3;
	const int32 TotalStepCount = Settings.FractureLevelCount + FinalizeStepCount;

	FScopedSlowTask AssetTask(static_cast<float>(TotalStepCount));

	int32 EnteredSteps = 0;
	auto EnterNextStep = [&]()
	{
		AssetTask.EnterProgressFrame(1.0f, GetPipelineStepText(EnteredSteps, Settings.FractureLevelCount));
		++EnteredSteps;
	};

	EnterNextStep();

	TSharedRef<FGCBatchFractureJob, ESPMode::ThreadSafe> Job = MakeShared<FGCBatchFractureJob, ESPMode::ThreadSafe>();
	const FString AssetName = GeometryCollection->GetName();
	const UGCBatchFractureSettings* SettingsPtr = &Settings;

	// The task holds its own references to the collection and the job: both stay valid
	// even if this function returns while the worker is still running.
	UE::Tasks::TTask<void> Task = UE::Tasks::Launch(
		UE_SOURCE_LOCATION,
		[Collection, Job, SettingsPtr, AssetName]()
		{
			RunFracturePipelineOnWorker(*Collection, *SettingsPtr, AssetName, *Job);
		});

	while (!Task.IsCompleted())
	{
		// Steps 0..CompletedSteps-1 are done, so step CompletedSteps is the one in progress.
		const int32 StepInProgress = FMath::Min(Job->CompletedSteps.load(), TotalStepCount - 1);
		while (EnteredSteps <= StepInProgress)
		{
			EnterNextStep();
		}

		if (!Job->bCancelRequested && AssetTask.ShouldCancel())
		{
			Job->bCancelRequested = true;
			AssetTask.FrameMessage = LOCTEXT(
				"CancellingProgress",
				"Cancelling: waiting for the current engine operation to finish...");

			UE_LOG(LogGCBatchFracture, Warning,
				TEXT("Cancel requested while processing %s. Waiting for the current engine operation to finish."),
				*AssetName);
		}

		AssetTask.TickProgress();
		FPlatformProcess::Sleep(0.02f);
	}

	// Completion has been observed: the worker no longer touches the job or the collection.
	Task.Wait();

	if (OutSafetyMessages)
	{
		OutSafetyMessages->Append(Job->SafetyMessages);
	}

	if (Job->bCancelRequested)
	{
		bOutCancelled = true;
		OutError = TEXT("Cancelled by user.");
		return false;
	}

	if (!Job->bSucceeded)
	{
		OutError = Job->Error;
		return false;
	}

	while (EnteredSteps < TotalStepCount)
	{
		EnterNextStep();
	}

	FinalizeFracturedGeometryCollection(GeometryCollection);
	return true;
}

/**
 * @brief Displays the batch summary as an editor toast notification.
 *
 * Detailed per-asset messages stay in the Output Log; the notification gives the
 * counts and a link to open it.
 *
 * @param Result Summary returned by RunOnStaticMeshes().
 */
static void ShowBatchResultNotification(const FGCBatchFractureResult& Result)
{
	// A batch cancelled during its first asset has every count at 0 but still needs feedback.
	if (Result.Succeeded + Result.Skipped + Result.Failed == 0 && !Result.bCancelled)
	{
		return;
	}

	const FText Counts = FText::Format(
		LOCTEXT("BatchResultCounts", "{0} created, {1} skipped, {2} failed, {3} limited."),
		FText::AsNumber(Result.Succeeded),
		FText::AsNumber(Result.Skipped),
		FText::AsNumber(Result.Failed),
		FText::AsNumber(Result.SafetyLimited));

	FNotificationInfo Info(Result.bCancelled
		? FText::Format(LOCTEXT("BatchResultCancelled", "Batch Chaos Fracture cancelled: {0} The asset in progress was discarded."), Counts)
		: FText::Format(LOCTEXT("BatchResultNotification", "Batch Chaos Fracture: {0}"), Counts));

	Info.ExpireDuration = 8.0f;
	Info.bFireAndForget = true;
	Info.Hyperlink = FSimpleDelegate::CreateLambda([]()
	{
		FGlobalTabmanager::Get()->TryInvokeTab(FName(TEXT("OutputLog")));
	});
	Info.HyperlinkText = LOCTEXT("BatchResultShowLog", "Show Output Log");

	const TSharedPtr<SNotificationItem> Notification = FSlateNotificationManager::Get().AddNotification(Info);
	if (Notification.IsValid())
	{
		const bool bHasProblems = Result.bCancelled || Result.Failed > 0 || Result.SafetyLimited > 0;
		Notification->SetCompletionState(bHasProblems ? SNotificationItem::CS_Fail : SNotificationItem::CS_Success);
	}
}

void FGCBatchFractureService::OpenOptionsDialogAndRun(
	const TArray<UStaticMesh*>& StaticMeshes)
{
	if (StaticMeshes.IsEmpty())
	{
		return;
	}
	
	TArray<TWeakObjectPtr<UStaticMesh>> WeakMeshes;
	WeakMeshes.Reserve(StaticMeshes.Num());

	for (UStaticMesh* StaticMesh : StaticMeshes)
	{
		if (StaticMesh)
		{
			WeakMeshes.Add(StaticMesh);
		}
	}

	TSharedRef<SWindow> DialogWindow = SNew(SWindow)
		.Title(FText::FromString(TEXT("GC Batch Fracture")))
		.ClientSize(FVector2D(520.0f, 400.0f))
		.SupportsMaximize(false)
		.SupportsMinimize(false)
		.SizingRule(ESizingRule::FixedSize);

	DialogWindow->SetContent(
		SNew(SGCBatchFractureDialog)
		.SelectedAssetCount(WeakMeshes.Num())
		.ParentWindow(DialogWindow)
		.OnConfirmed(FSimpleDelegate::CreateLambda([WeakMeshes]()
		{
			TArray<UStaticMesh*> ValidMeshes;
			ValidMeshes.Reserve(WeakMeshes.Num());

			for (const TWeakObjectPtr<UStaticMesh>& WeakMesh : WeakMeshes)
			{
				if (WeakMesh.IsValid())
				{
					ValidMeshes.Add(WeakMesh.Get());
				}
			}

			if (!ValidMeshes.IsEmpty())
			{
				ShowBatchResultNotification(FGCBatchFractureService::RunOnStaticMeshes(ValidMeshes));
			}
		}))
	);

	FSlateApplication::Get().AddWindow(DialogWindow);
}
#undef LOCTEXT_NAMESPACE

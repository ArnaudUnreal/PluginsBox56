// Copyright Arnaud Szobad 2026 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

/*
 * Full pipeline:
 *
 * Content Browser selection
 * → filter Static Meshes
 * → create /GC/GC_* Geometry Collection asset
 * → append source Static Mesh geometry
 * → run one or more Voronoi fracture levels
 * → fix tiny fragments
 * → validate collection hierarchy
 * → generate convex collision hulls
 * → prepare Chaos simulation
 * → create simulation data
 * → rebuild render data
 * → save asset
 *
 * The important distinction is:
 * VoronoiFracture creates visible fractured pieces.
 * GenerateCollisionHulls & CreateSimulationData make those pieces usable by Chaos at runtime.
 */

class UGCBatchFractureSettings;
class UGeometryCollection;
class UStaticMesh;

struct FGCBatchFractureResult
{
    int32 Requested = 0;
    int32 ValidStaticMeshes = 0;
    int32 Succeeded = 0;
    int32 Skipped = 0;
    int32 Failed = 0;
    
    /** Number of assets whose fracture process was limited by a safety rule. */
    int32 SafetyLimited = 0;

    /** True if the user cancelled the batch. The asset in progress is discarded. */
    bool bCancelled = false;

    TArray<FString> Messages;

    /** Human-readable safety limitation messages collected during the batch. */
    TArray<FString> SafetyMessages;
};

enum class EGCBatchDestinationResult : uint8
{
    Valid,
    Skipped,
    Failed
};

/**
 * @brief Main service for Batch Fracture Tool
 */

class GCBATCHFRACTURE_API FGCBatchFractureService
{
public:
    static FGCBatchFractureResult RunOnStaticMeshes(const TArray<UStaticMesh*>& SelectedObjects);
    static void OpenOptionsDialogAndRun(const TArray<UStaticMesh*>& StaticMeshes);

private:
    static bool ValidateSelectionCount(int32 Count, const UGCBatchFractureSettings& Settings);
    static FString BuildDestinationFolder(const FString& SourcePackagePath, const UGCBatchFractureSettings& Settings);
    static EGCBatchDestinationResult BuildDestinationObjectPath(
        const FString& SourcePackagePath,
        const FString& SourceAssetName,
        const UGCBatchFractureSettings& Settings,
        FString& OutDestinationObjectPath);
    static bool DoesAssetAlreadyExist(const FString& PackageName, const FString& AssetName);
    static bool EnsureFolderExists(const FString& LongPackagePath);
    static bool SavePackageForObject(UObject* ObjectToSave, FString& OutError);

    static UGeometryCollection* CreateGeometryCollectionAssetFromStaticMesh(
        UStaticMesh* SourceMesh,
        const FString& DestinationObjectPath,
        FString& OutError);

    static bool ApplyDefaultFractureSettings(
        UGeometryCollection* GeometryCollection,
        const UGCBatchFractureSettings& Settings,
        FString& OutError,
        TArray<FString>* OutSafetyMessages,
        bool& bOutCancelled);
   
};

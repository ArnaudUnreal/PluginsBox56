// Copyright Arnaud Szobad 2026 All Rights Reserved.

#include "GCBatchFractureSettings.h"

static bool IsPresetControlledProperty(const FName PropertyName)
{
	return
		PropertyName == GET_MEMBER_NAME_CHECKED(UGCBatchFractureSettings, FractureLevelCount) ||
		PropertyName == GET_MEMBER_NAME_CHECKED(UGCBatchFractureSettings, VoronoiSites) ||
		PropertyName == GET_MEMBER_NAME_CHECKED(UGCBatchFractureSettings, RandomSeed) ||
		PropertyName == GET_MEMBER_NAME_CHECKED(UGCBatchFractureSettings, RandomSeedOffsetPerLevel) ||

		PropertyName == GET_MEMBER_NAME_CHECKED(UGCBatchFractureSettings, ChanceToFracture) ||
		PropertyName == GET_MEMBER_NAME_CHECKED(UGCBatchFractureSettings, PerLevelChanceToFracture) ||
		PropertyName == GET_MEMBER_NAME_CHECKED(UGCBatchFractureSettings, MaxTransformsToFracturePerLevel) ||
		PropertyName == GET_MEMBER_NAME_CHECKED(UGCBatchFractureSettings, MaxTransformsAfterFracture) ||

		PropertyName == GET_MEMBER_NAME_CHECKED(UGCBatchFractureSettings, bSplitIslands) ||
		PropertyName == GET_MEMBER_NAME_CHECKED(UGCBatchFractureSettings, Grout) ||

		PropertyName == GET_MEMBER_NAME_CHECKED(UGCBatchFractureSettings, Amplitude) ||
		PropertyName == GET_MEMBER_NAME_CHECKED(UGCBatchFractureSettings, Frequency) ||
		PropertyName == GET_MEMBER_NAME_CHECKED(UGCBatchFractureSettings, Persistence) ||
		PropertyName == GET_MEMBER_NAME_CHECKED(UGCBatchFractureSettings, Lacunarity) ||
		PropertyName == GET_MEMBER_NAME_CHECKED(UGCBatchFractureSettings, OctaveNumber) ||

		PropertyName == GET_MEMBER_NAME_CHECKED(UGCBatchFractureSettings, PointSpacing) ||
		PropertyName == GET_MEMBER_NAME_CHECKED(UGCBatchFractureSettings, bAddSamplesForCollision) ||
		PropertyName == GET_MEMBER_NAME_CHECKED(UGCBatchFractureSettings, CollisionSampleSpacing) ||

		PropertyName == GET_MEMBER_NAME_CHECKED(UGCBatchFractureSettings, bFixTinyGeometry) ||
		PropertyName == GET_MEMBER_NAME_CHECKED(UGCBatchFractureSettings, TinyGeometryMinSizeCm) ||
		PropertyName == GET_MEMBER_NAME_CHECKED(UGCBatchFractureSettings, bValidateGeometryCollectionAfterFracture) ||

		PropertyName == GET_MEMBER_NAME_CHECKED(UGCBatchFractureSettings, bGenerateLeafConvexHulls) ||
		PropertyName == GET_MEMBER_NAME_CHECKED(UGCBatchFractureSettings, bGenerateClusterConvexHulls) ||
		PropertyName == GET_MEMBER_NAME_CHECKED(UGCBatchFractureSettings, bCreateNonOverlappingConvexHulls);
}

/**
 * @brief Defines the default settings used by the batch fracture tool.
 *
 * These defaults control:
 * - output folder and asset prefix;
 * - batch safety limits;
 * - number of fracture levels;
 * - Voronoi site count and random seed;
 * - tiny geometry cleanup;
 * - collision hull generation;
 * - runtime simulation data generation.
 *
 * The goal is to provide safe defaults that work for most props without forcing
 * the user to understand every low-level Chaos setting.
 */
UGCBatchFractureSettings::UGCBatchFractureSettings()
{
    OutputSubfolder = TEXT("GC");
    NamePrefix = TEXT("GC_");

    bSkipExistingAssets = true;

    RandomSeed = 1337;
    RandomSeedOffsetPerLevel = 100;
    ChanceToFracture = 1.0f;
	MaxEstimatedFractureOperationsPerLevel = 512;
	MaxSourceTriangles = 200000;

	// Preset-controlled values come from the default preset, so the defaults shown
	// in Project Settings always match what the selected preset applies.
	Preset = EGCBatchFracturePreset::Balanced;
	ApplyPresetToSettings();
}

FName UGCBatchFractureSettings::GetContainerName() const
{
	// Config=EditorPerProjectUserSettings would place the section in Editor Preferences by
	// default. Keep it in Project Settings, while values are still saved per user.
	return TEXT("Project");
}

FName UGCBatchFractureSettings::GetCategoryName() const
{
    return TEXT("Plugins");
}

void UGCBatchFractureSettings::ApplyPresetToSettings()
{
	switch (Preset)
	{
	case EGCBatchFracturePreset::FastPreview:
		FractureLevelCount = 1;
		VoronoiSites = 8;
		PerLevelChanceToFracture = 1.0f;
		MaxTransformsToFracturePerLevel = 0;
		MaxTransformsAfterFracture = 150;

		bFixTinyGeometry = true;
		TinyGeometryMinSizeCm = 2.0f;
		bValidateGeometryCollectionAfterFracture = true;

		bGenerateLeafConvexHulls = true;
		bGenerateClusterConvexHulls = false;
		bCreateNonOverlappingConvexHulls = false;

		bSplitIslands = false;
		Grout = 0.0f;

		Amplitude = 0.0f;
		Frequency = 0.0f;
		Persistence = 0.5f;
		Lacunarity = 2.0f;
		OctaveNumber = 0;

		PointSpacing = 10.0f;
		bAddSamplesForCollision = false;
		CollisionSampleSpacing = 50.0f;
		
		break;

	case EGCBatchFracturePreset::Balanced:
		FractureLevelCount = 2;
		VoronoiSites = 4;
		PerLevelChanceToFracture = 0.35f;
		MaxTransformsToFracturePerLevel = 64;
		MaxTransformsAfterFracture = 300;

		bFixTinyGeometry = true;
		TinyGeometryMinSizeCm = 1.5f;
		bValidateGeometryCollectionAfterFracture = true;

		bGenerateLeafConvexHulls = true;
		bGenerateClusterConvexHulls = true;
		bCreateNonOverlappingConvexHulls = false;

		bSplitIslands = false;
		Grout = 0.0f;

		Amplitude = 0.0f;
		Frequency = 0.0f;
		Persistence = 0.5f;
		Lacunarity = 2.0f;
		OctaveNumber = 0;

		PointSpacing = 10.0f;
		bAddSamplesForCollision = false;
		CollisionSampleSpacing = 50.0f;
		break;

	case EGCBatchFracturePreset::RuntimeSafe:
		FractureLevelCount = 2;
		VoronoiSites = 6;
		PerLevelChanceToFracture = 0.5f;
		MaxTransformsToFracturePerLevel = 100;
		MaxTransformsAfterFracture = 500;

		bFixTinyGeometry = true;
		TinyGeometryMinSizeCm = 2.0f;
		bValidateGeometryCollectionAfterFracture = true;

		bGenerateLeafConvexHulls = true;
		bGenerateClusterConvexHulls = true;
		bCreateNonOverlappingConvexHulls = false;

		bSplitIslands = false;
		Grout = 0.0f;

		Amplitude = 0.0f;
		Frequency = 0.0f;
		Persistence = 0.5f;
		Lacunarity = 2.0f;
		OctaveNumber = 0;

		PointSpacing = 10.0f;
		bAddSamplesForCollision = false;
		CollisionSampleSpacing = 50.0f;
		break;

	case EGCBatchFracturePreset::Custom:
	default:
		// Custom preserves whatever values are already displayed in the settings.
		break;
	}
}

#if WITH_EDITOR
void UGCBatchFractureSettings::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	const FName PropertyName = PropertyChangedEvent.Property
		? PropertyChangedEvent.Property->GetFName()
		: NAME_None;

	const FName MemberPropertyName = PropertyChangedEvent.MemberProperty
		? PropertyChangedEvent.MemberProperty->GetFName()
		: PropertyName;

	Super::PostEditChangeProperty(PropertyChangedEvent);

	const bool bPresetChanged =
		PropertyName == GET_MEMBER_NAME_CHECKED(UGCBatchFractureSettings, Preset) ||
		MemberPropertyName == GET_MEMBER_NAME_CHECKED(UGCBatchFractureSettings, Preset);

	if (bPresetChanged)
	{
		if (!bIsApplyingPreset && Preset != EGCBatchFracturePreset::Custom)
		{
			TGuardValue<bool> ApplyingPresetGuard(bIsApplyingPreset, true);

			ApplyPresetToSettings();
		}

		SaveConfig();
		return;
	}

	const bool bChangedPropertyIsPresetControlled =
		IsPresetControlledProperty(PropertyName) ||
		IsPresetControlledProperty(MemberPropertyName);

	if (!bIsApplyingPreset &&
		Preset != EGCBatchFracturePreset::Custom &&
		bChangedPropertyIsPresetControlled)
	{
		TGuardValue<bool> ApplyingPresetGuard(bIsApplyingPreset, true);

		Preset = EGCBatchFracturePreset::Custom;
	}

	SaveConfig();
}
#endif
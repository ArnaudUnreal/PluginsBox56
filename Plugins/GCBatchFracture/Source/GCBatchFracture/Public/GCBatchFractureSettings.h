// Copyright Arnaud Szobad (Mecanode). All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "GCBatchFractureSettings.generated.h"

UENUM()
enum class EGCBatchFracturePreset : uint8
{
	FastPreview UMETA(DisplayName="Fast Preview"),
	Balanced	UMETA(DisplayName="Balanced"),
	RuntimeSafe UMETA(DisplayName="Runtime Safe"),
	Custom		UMETA(DisplayName="Custom")
};

UCLASS(Config=EditorPerProjectUserSettings, DisplayName="GC Batch Fracture")
class GCBATCHFRACTURE_API UGCBatchFractureSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UGCBatchFractureSettings();
	virtual FName GetContainerName() const override;
	virtual FName GetCategoryName() const override;
	void ApplyPresetToSettings();
	
	#if WITH_EDITOR
		virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	#endif
	
	// ----------------------------
	// Output
	// ----------------------------

	UPROPERTY(Config, EditAnywhere, Category="Output")
	FString OutputSubfolder = TEXT("GC");

	UPROPERTY(Config, EditAnywhere, Category="Output")
	FString NamePrefix = TEXT("GC_");

	UPROPERTY(Config, EditAnywhere, Category="Output")
	bool bSkipExistingAssets = true;

	// ----------------------------
	// Batch Safety
	// ----------------------------

	UPROPERTY(Config, EditAnywhere, Category="Batch Safety", meta=(ClampMin="1"))
	int32 SoftSelectionWarningCount = 50;

	UPROPERTY(Config, EditAnywhere, Category="Batch Safety", meta=(ClampMin="1"))
	int32 HardSelectionBlockCount = 100;

	UPROPERTY(Config, EditAnywhere, Category="Batch Safety")
	bool bSaveAfterEachAsset = true;

	UPROPERTY(Config, EditAnywhere, Category="Batch Safety", meta=(ClampMin="0"))
	int32 GarbageCollectEveryNAssets = 10;

	/**
	 * Maximum number of transforms allowed after the fracture process.
	 *
	 * Set to 0 to disable the limit.
	 * If the collection exceeds this value, the tool can stop before generating
	 * excessively heavy collision and simulation data.
	 */
	UPROPERTY(Config, EditAnywhere, Category="Batch Safety", meta=(ClampMin="0"))
	int32 MaxTransformsAfterFracture = 300;
	UPROPERTY(Config, EditAnywhere, Category="Preset", meta=(ToolTip="Changing this preset applies its values to the advanced settings below. Editing any advanced setting switches the preset to Custom."))
	EGCBatchFracturePreset Preset = EGCBatchFracturePreset::Balanced;

	// ----------------------------
	// Fracture
	// ----------------------------

	UPROPERTY(Config, EditAnywhere, Category="Fracture", meta=(ClampMin="1", ClampMax="10"))
	int32 FractureLevelCount = 2;

	UPROPERTY(Config, EditAnywhere, Category="Fracture", meta=(ClampMin="1", ClampMax="500"))
	int32 VoronoiSites = 4;

	UPROPERTY(Config, EditAnywhere, Category="Fracture")
	int32 RandomSeed = 1337;

	UPROPERTY(Config, EditAnywhere, Category="Fracture")
	int32 RandomSeedOffsetPerLevel = 100;

	UPROPERTY(Config, EditAnywhere, Category="Fracture", meta=(ClampMin="0.0", ClampMax="1.0"))
	float ChanceToFracture = 1.0f;

	/**
	 * If enabled, disconnected geometry islands may be separated during fracture.
	 * This can be useful for some meshes, but may also increase fragment count.
	 */
	UPROPERTY(Config, EditAnywhere, Category="Fracture|Advanced", 
		meta=(ToolTip="If enabled, disconnected geometry islands may be separated during fracture.Can increase fragment count on some meshes."))
	bool bSplitIslands = false;

	/**
	 * Gap amount inserted between fractured pieces.
	 *
	 * Keep this at 0 for most production assets.
	 * Higher values can create visible spacing between fragments.
	 */
	UPROPERTY(Config, EditAnywhere, Category="Fracture", 
		meta=(ClampMin="0.0",
		ToolTip="Gap amount inserted between fractured pieces. Keep this at 0 for most production assets. Higher values can create visible spacing between fragments."))
	float Grout = 0.0f;

	/**
	 * Chance for each transform to be selected for fracture on levels above 0.
	 *
	 * Level 0 usually fractures the original mesh/root.
	 * Higher levels can quickly become expensive if all pieces are refractured.
	 * A value below 1.0 limits the amount of pieces selected for secondary fracture passes.
	 */
	UPROPERTY(Config, EditAnywhere, Category="Fracture", meta=(ClampMin="0.0", ClampMax="1.0"))
	float PerLevelChanceToFracture = 0.35f;

	/**
	 * Maximum number of transforms that can be selected for fracture on a single level.
	 *
	 * Set to 0 to disable the limit.
	 * This is a safety setting to avoid extremely slow multi-level fracture passes.
	 */
	UPROPERTY(Config, EditAnywhere, Category="Fracture", meta=(ClampMin="0"))
	int32 MaxTransformsToFracturePerLevel = 64;
	
	UPROPERTY(Config, EditAnywhere, Category="Fracture|Safety", meta=(ClampMin="0"))
	int32 MaxEstimatedFractureOperationsPerLevel = 512;
	
	// ----------------------------
	// Batch
	// ----------------------------
	
	/**
	 * Maximum number of vertices of a source Static Mesh. Heavier meshes are rejected.
	 * Uses the Nanite input geometry for Nanite meshes. Set to 0 to disable the limit.
	 */
	UPROPERTY(Config, EditAnywhere, Category="Batch Safety", meta=(ClampMin="0"))
	int32 MaxSourceVertices = 0;

	/**
	 * Maximum number of triangles of a source Static Mesh. Heavier meshes are rejected.
	 * Uses the Nanite input geometry for Nanite meshes. Set to 0 to disable the limit.
	 */
	UPROPERTY(Config, EditAnywhere, Category="Batch Safety", meta=(ClampMin="0"))
	int32 MaxSourceTriangles = 200000;
	
	// ----------------------------
	// Noise
	// ----------------------------

	UPROPERTY(Config, EditAnywhere, Category="Noise")
	float Amplitude = 0.0f;

	UPROPERTY(Config, EditAnywhere, Category="Noise")
	float Frequency = 0.0f;

	UPROPERTY(Config, EditAnywhere, Category="Noise")
	float Persistence = 0.5f;

	UPROPERTY(Config, EditAnywhere, Category="Noise")
	float Lacunarity = 2.0f;

	UPROPERTY(Config, EditAnywhere, Category="Noise", meta=(ClampMin="0"))
	int32 OctaveNumber = 0;

	// ----------------------------
	// Collision
	// ----------------------------

	UPROPERTY(Config, EditAnywhere, Category="Collision")
	float PointSpacing = 10.0f;

	UPROPERTY(Config, EditAnywhere, Category="Collision")
	bool bAddSamplesForCollision = false;

	/**
	 * Spacing, in cm, of the extra collision sample points added on fractured surfaces.
	 * Only used when bAddSamplesForCollision is enabled. Small values add a huge number of
	 * points and can make the fracture run for a very long time.
	 */
	UPROPERTY(Config, EditAnywhere, Category="Collision", meta=(ClampMin="1.0", UIMin="10.0", EditCondition="bAddSamplesForCollision"))
	float CollisionSampleSpacing = 50.0f;
	
	UPROPERTY(Config, EditAnywhere, Category="Collision|Tiny Geometry")
	bool bFixTinyGeometry = true;

	UPROPERTY(Config, EditAnywhere, Category="Collision|Tiny Geometry", meta=(ClampMin="0.01", UIMin="0.1", UIMax="10.0"))
	float TinyGeometryMinSizeCm = 1.5f;

	UPROPERTY(Config, EditAnywhere, Category="Collision|Tiny Geometry")
	bool bValidateGeometryCollectionAfterFracture = true;
	
	/**
	 * Whether to generate convex hulls for leaf pieces.
	 * This is required for reliable runtime collision on fractured pieces.
	 */
	UPROPERTY(Config, EditAnywhere, Category="Collision")
	bool bGenerateLeafConvexHulls = true;

	/**
	 * Whether to generate convex hulls for cluster nodes.
	 * Useful when the collection starts as a clustered object before breaking.
	 */
	UPROPERTY(Config, EditAnywhere, Category="Collision")
	bool bGenerateClusterConvexHulls = true;

	/**
 * Whether to generate non-overlapping convex hull data.
 *
 * This can improve collision quality, but it is slower and more experimental.
 * Keep disabled unless you specifically need it.
 */
	UPROPERTY(
		Config,
		EditAnywhere,
		Category="Collision|Advanced",
		meta=(ToolTip="Experimental and potentially slow. Can improve collision quality, but may significantly increase generation time on complex Geometry Collections."))
	bool bCreateNonOverlappingConvexHulls = false;
	
	
private:

	/**
	 * Internal guard used to prevent preset application from being interpreted as
	 * manual user edits.
	 */
	bool bIsApplyingPreset = false;
	
};
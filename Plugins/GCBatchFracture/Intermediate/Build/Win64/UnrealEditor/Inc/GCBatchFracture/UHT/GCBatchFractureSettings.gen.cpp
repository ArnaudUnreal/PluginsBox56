// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GCBatchFractureSettings.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeGCBatchFractureSettings() {}

// ********** Begin Cross Module References ********************************************************
DEVELOPERSETTINGS_API UClass* Z_Construct_UClass_UDeveloperSettings();
GCBATCHFRACTURE_API UClass* Z_Construct_UClass_UGCBatchFractureSettings();
GCBATCHFRACTURE_API UClass* Z_Construct_UClass_UGCBatchFractureSettings_NoRegister();
GCBATCHFRACTURE_API UEnum* Z_Construct_UEnum_GCBatchFracture_EGCBatchFracturePreset();
UPackage* Z_Construct_UPackage__Script_GCBatchFracture();
// ********** End Cross Module References **********************************************************

// ********** Begin Enum EGCBatchFracturePreset ****************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EGCBatchFracturePreset;
static UEnum* EGCBatchFracturePreset_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EGCBatchFracturePreset.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EGCBatchFracturePreset.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_GCBatchFracture_EGCBatchFracturePreset, (UObject*)Z_Construct_UPackage__Script_GCBatchFracture(), TEXT("EGCBatchFracturePreset"));
	}
	return Z_Registration_Info_UEnum_EGCBatchFracturePreset.OuterSingleton;
}
template<> GCBATCHFRACTURE_API UEnum* StaticEnum<EGCBatchFracturePreset>()
{
	return EGCBatchFracturePreset_StaticEnum();
}
struct Z_Construct_UEnum_GCBatchFracture_EGCBatchFracturePreset_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "Balanced.DisplayName", "Balanced" },
		{ "Balanced.Name", "EGCBatchFracturePreset::Balanced" },
		{ "Custom.DisplayName", "Custom" },
		{ "Custom.Name", "EGCBatchFracturePreset::Custom" },
		{ "FastPreview.DisplayName", "Fast Preview" },
		{ "FastPreview.Name", "EGCBatchFracturePreset::FastPreview" },
		{ "ModuleRelativePath", "Public/GCBatchFractureSettings.h" },
		{ "RuntimeSafe.DisplayName", "Runtime Safe" },
		{ "RuntimeSafe.Name", "EGCBatchFracturePreset::RuntimeSafe" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EGCBatchFracturePreset::FastPreview", (int64)EGCBatchFracturePreset::FastPreview },
		{ "EGCBatchFracturePreset::Balanced", (int64)EGCBatchFracturePreset::Balanced },
		{ "EGCBatchFracturePreset::RuntimeSafe", (int64)EGCBatchFracturePreset::RuntimeSafe },
		{ "EGCBatchFracturePreset::Custom", (int64)EGCBatchFracturePreset::Custom },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_GCBatchFracture_EGCBatchFracturePreset_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_GCBatchFracture,
	nullptr,
	"EGCBatchFracturePreset",
	"EGCBatchFracturePreset",
	Z_Construct_UEnum_GCBatchFracture_EGCBatchFracturePreset_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_GCBatchFracture_EGCBatchFracturePreset_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_GCBatchFracture_EGCBatchFracturePreset_Statics::Enum_MetaDataParams), Z_Construct_UEnum_GCBatchFracture_EGCBatchFracturePreset_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_GCBatchFracture_EGCBatchFracturePreset()
{
	if (!Z_Registration_Info_UEnum_EGCBatchFracturePreset.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EGCBatchFracturePreset.InnerSingleton, Z_Construct_UEnum_GCBatchFracture_EGCBatchFracturePreset_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EGCBatchFracturePreset.InnerSingleton;
}
// ********** End Enum EGCBatchFracturePreset ******************************************************

// ********** Begin Class UGCBatchFractureSettings *************************************************
void UGCBatchFractureSettings::StaticRegisterNativesUGCBatchFractureSettings()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_UGCBatchFractureSettings;
UClass* UGCBatchFractureSettings::GetPrivateStaticClass()
{
	using TClass = UGCBatchFractureSettings;
	if (!Z_Registration_Info_UClass_UGCBatchFractureSettings.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("GCBatchFractureSettings"),
			Z_Registration_Info_UClass_UGCBatchFractureSettings.InnerSingleton,
			StaticRegisterNativesUGCBatchFractureSettings,
			sizeof(TClass),
			alignof(TClass),
			TClass::StaticClassFlags,
			TClass::StaticClassCastFlags(),
			TClass::StaticConfigName(),
			(UClass::ClassConstructorType)InternalConstructor<TClass>,
			(UClass::ClassVTableHelperCtorCallerType)InternalVTableHelperCtorCaller<TClass>,
			UOBJECT_CPPCLASS_STATICFUNCTIONS_FORCLASS(TClass),
			&TClass::Super::StaticClass,
			&TClass::WithinClass::StaticClass
		);
	}
	return Z_Registration_Info_UClass_UGCBatchFractureSettings.InnerSingleton;
}
UClass* Z_Construct_UClass_UGCBatchFractureSettings_NoRegister()
{
	return UGCBatchFractureSettings::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UGCBatchFractureSettings_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "DisplayName", "GC Batch Fracture" },
		{ "IncludePath", "GCBatchFractureSettings.h" },
		{ "ModuleRelativePath", "Public/GCBatchFractureSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OutputSubfolder_MetaData[] = {
		{ "Category", "Output" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// ----------------------------\n// Output\n// ----------------------------\n" },
#endif
		{ "ModuleRelativePath", "Public/GCBatchFractureSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Output" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NamePrefix_MetaData[] = {
		{ "Category", "Output" },
		{ "ModuleRelativePath", "Public/GCBatchFractureSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bSkipExistingAssets_MetaData[] = {
		{ "Category", "Output" },
		{ "ModuleRelativePath", "Public/GCBatchFractureSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SoftSelectionWarningCount_MetaData[] = {
		{ "Category", "Batch Safety" },
		{ "ClampMin", "1" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// ----------------------------\n// Batch Safety\n// ----------------------------\n" },
#endif
		{ "ModuleRelativePath", "Public/GCBatchFractureSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Batch Safety" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HardSelectionBlockCount_MetaData[] = {
		{ "Category", "Batch Safety" },
		{ "ClampMin", "1" },
		{ "ModuleRelativePath", "Public/GCBatchFractureSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bSaveAfterEachAsset_MetaData[] = {
		{ "Category", "Batch Safety" },
		{ "ModuleRelativePath", "Public/GCBatchFractureSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_GarbageCollectEveryNAssets_MetaData[] = {
		{ "Category", "Batch Safety" },
		{ "ClampMin", "0" },
		{ "ModuleRelativePath", "Public/GCBatchFractureSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxTransformsAfterFracture_MetaData[] = {
		{ "Category", "Batch Safety" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Maximum number of transforms allowed after the fracture process.\n\x09 *\n\x09 * Set to 0 to disable the limit.\n\x09 * If the collection exceeds this value, the tool can stop before generating\n\x09 * excessively heavy collision and simulation data.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/GCBatchFractureSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Maximum number of transforms allowed after the fracture process.\n\nSet to 0 to disable the limit.\nIf the collection exceeds this value, the tool can stop before generating\nexcessively heavy collision and simulation data." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Preset_MetaData[] = {
		{ "Category", "Preset" },
		{ "ModuleRelativePath", "Public/GCBatchFractureSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Changing this preset applies its values to the advanced settings below. Editing any advanced setting switches the preset to Custom." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FractureLevelCount_MetaData[] = {
		{ "Category", "Fracture" },
		{ "ClampMax", "10" },
		{ "ClampMin", "1" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// ----------------------------\n// Fracture\n// ----------------------------\n" },
#endif
		{ "ModuleRelativePath", "Public/GCBatchFractureSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Fracture" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_VoronoiSites_MetaData[] = {
		{ "Category", "Fracture" },
		{ "ClampMax", "500" },
		{ "ClampMin", "1" },
		{ "ModuleRelativePath", "Public/GCBatchFractureSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RandomSeed_MetaData[] = {
		{ "Category", "Fracture" },
		{ "ModuleRelativePath", "Public/GCBatchFractureSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RandomSeedOffsetPerLevel_MetaData[] = {
		{ "Category", "Fracture" },
		{ "ModuleRelativePath", "Public/GCBatchFractureSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ChanceToFracture_MetaData[] = {
		{ "Category", "Fracture" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
		{ "ModuleRelativePath", "Public/GCBatchFractureSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bSplitIslands_MetaData[] = {
		{ "Category", "Fracture|Advanced" },
		{ "ModuleRelativePath", "Public/GCBatchFractureSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "If enabled, disconnected geometry islands may be separated during fracture.Can increase fragment count on some meshes." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Grout_MetaData[] = {
		{ "Category", "Fracture" },
		{ "ClampMin", "0.0" },
		{ "ModuleRelativePath", "Public/GCBatchFractureSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Gap amount inserted between fractured pieces. Keep this at 0 for most production assets. Higher values can create visible spacing between fragments." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PerLevelChanceToFracture_MetaData[] = {
		{ "Category", "Fracture" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Chance for each transform to be selected for fracture on levels above 0.\n\x09 *\n\x09 * Level 0 usually fractures the original mesh/root.\n\x09 * Higher levels can quickly become expensive if all pieces are refractured.\n\x09 * A value below 1.0 limits the amount of pieces selected for secondary fracture passes.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/GCBatchFractureSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Chance for each transform to be selected for fracture on levels above 0.\n\nLevel 0 usually fractures the original mesh/root.\nHigher levels can quickly become expensive if all pieces are refractured.\nA value below 1.0 limits the amount of pieces selected for secondary fracture passes." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxTransformsToFracturePerLevel_MetaData[] = {
		{ "Category", "Fracture" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Maximum number of transforms that can be selected for fracture on a single level.\n\x09 *\n\x09 * Set to 0 to disable the limit.\n\x09 * This is a safety setting to avoid extremely slow multi-level fracture passes.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/GCBatchFractureSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Maximum number of transforms that can be selected for fracture on a single level.\n\nSet to 0 to disable the limit.\nThis is a safety setting to avoid extremely slow multi-level fracture passes." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxEstimatedFractureOperationsPerLevel_MetaData[] = {
		{ "Category", "Fracture|Safety" },
		{ "ClampMin", "0" },
		{ "ModuleRelativePath", "Public/GCBatchFractureSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxSourceVertices_MetaData[] = {
		{ "Category", "Batch Safety" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Maximum number of vertices of a source Static Mesh. Heavier meshes are rejected.\n\x09 * Uses the Nanite input geometry for Nanite meshes. Set to 0 to disable the limit.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/GCBatchFractureSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Maximum number of vertices of a source Static Mesh. Heavier meshes are rejected.\nUses the Nanite input geometry for Nanite meshes. Set to 0 to disable the limit." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxSourceTriangles_MetaData[] = {
		{ "Category", "Batch Safety" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Maximum number of triangles of a source Static Mesh. Heavier meshes are rejected.\n\x09 * Uses the Nanite input geometry for Nanite meshes. Set to 0 to disable the limit.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/GCBatchFractureSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Maximum number of triangles of a source Static Mesh. Heavier meshes are rejected.\nUses the Nanite input geometry for Nanite meshes. Set to 0 to disable the limit." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Amplitude_MetaData[] = {
		{ "Category", "Noise" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// ----------------------------\n// Noise\n// ----------------------------\n" },
#endif
		{ "ModuleRelativePath", "Public/GCBatchFractureSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Noise" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Frequency_MetaData[] = {
		{ "Category", "Noise" },
		{ "ModuleRelativePath", "Public/GCBatchFractureSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Persistence_MetaData[] = {
		{ "Category", "Noise" },
		{ "ModuleRelativePath", "Public/GCBatchFractureSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Lacunarity_MetaData[] = {
		{ "Category", "Noise" },
		{ "ModuleRelativePath", "Public/GCBatchFractureSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OctaveNumber_MetaData[] = {
		{ "Category", "Noise" },
		{ "ClampMin", "0" },
		{ "ModuleRelativePath", "Public/GCBatchFractureSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PointSpacing_MetaData[] = {
		{ "Category", "Collision" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// ----------------------------\n// Collision\n// ----------------------------\n" },
#endif
		{ "ModuleRelativePath", "Public/GCBatchFractureSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Collision" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bAddSamplesForCollision_MetaData[] = {
		{ "Category", "Collision" },
		{ "ModuleRelativePath", "Public/GCBatchFractureSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CollisionSampleSpacing_MetaData[] = {
		{ "Category", "Collision" },
		{ "ClampMin", "1.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Spacing, in cm, of the extra collision sample points added on fractured surfaces.\n\x09 * Only used when bAddSamplesForCollision is enabled. Small values add a huge number of\n\x09 * points and can make the fracture run for a very long time.\n\x09 */" },
#endif
		{ "EditCondition", "bAddSamplesForCollision" },
		{ "ModuleRelativePath", "Public/GCBatchFractureSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Spacing, in cm, of the extra collision sample points added on fractured surfaces.\nOnly used when bAddSamplesForCollision is enabled. Small values add a huge number of\npoints and can make the fracture run for a very long time." },
#endif
		{ "UIMin", "10.0" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bFixTinyGeometry_MetaData[] = {
		{ "Category", "Collision|Tiny Geometry" },
		{ "ModuleRelativePath", "Public/GCBatchFractureSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TinyGeometryMinSizeCm_MetaData[] = {
		{ "Category", "Collision|Tiny Geometry" },
		{ "ClampMin", "0.01" },
		{ "ModuleRelativePath", "Public/GCBatchFractureSettings.h" },
		{ "UIMax", "10.0" },
		{ "UIMin", "0.1" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bValidateGeometryCollectionAfterFracture_MetaData[] = {
		{ "Category", "Collision|Tiny Geometry" },
		{ "ModuleRelativePath", "Public/GCBatchFractureSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bGenerateLeafConvexHulls_MetaData[] = {
		{ "Category", "Collision" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Whether to generate convex hulls for leaf pieces.\n\x09 * This is required for reliable runtime collision on fractured pieces.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/GCBatchFractureSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Whether to generate convex hulls for leaf pieces.\nThis is required for reliable runtime collision on fractured pieces." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bGenerateClusterConvexHulls_MetaData[] = {
		{ "Category", "Collision" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Whether to generate convex hulls for cluster nodes.\n\x09 * Useful when the collection starts as a clustered object before breaking.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/GCBatchFractureSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Whether to generate convex hulls for cluster nodes.\nUseful when the collection starts as a clustered object before breaking." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bCreateNonOverlappingConvexHulls_MetaData[] = {
		{ "Category", "Collision|Advanced" },
		{ "ModuleRelativePath", "Public/GCBatchFractureSettings.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Experimental and potentially slow. Can improve collision quality, but may significantly increase generation time on complex Geometry Collections." },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_OutputSubfolder;
	static const UECodeGen_Private::FStrPropertyParams NewProp_NamePrefix;
	static void NewProp_bSkipExistingAssets_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bSkipExistingAssets;
	static const UECodeGen_Private::FIntPropertyParams NewProp_SoftSelectionWarningCount;
	static const UECodeGen_Private::FIntPropertyParams NewProp_HardSelectionBlockCount;
	static void NewProp_bSaveAfterEachAsset_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bSaveAfterEachAsset;
	static const UECodeGen_Private::FIntPropertyParams NewProp_GarbageCollectEveryNAssets;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaxTransformsAfterFracture;
	static const UECodeGen_Private::FBytePropertyParams NewProp_Preset_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Preset;
	static const UECodeGen_Private::FIntPropertyParams NewProp_FractureLevelCount;
	static const UECodeGen_Private::FIntPropertyParams NewProp_VoronoiSites;
	static const UECodeGen_Private::FIntPropertyParams NewProp_RandomSeed;
	static const UECodeGen_Private::FIntPropertyParams NewProp_RandomSeedOffsetPerLevel;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ChanceToFracture;
	static void NewProp_bSplitIslands_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bSplitIslands;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Grout;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_PerLevelChanceToFracture;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaxTransformsToFracturePerLevel;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaxEstimatedFractureOperationsPerLevel;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaxSourceVertices;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaxSourceTriangles;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Amplitude;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Frequency;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Persistence;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Lacunarity;
	static const UECodeGen_Private::FIntPropertyParams NewProp_OctaveNumber;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_PointSpacing;
	static void NewProp_bAddSamplesForCollision_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bAddSamplesForCollision;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CollisionSampleSpacing;
	static void NewProp_bFixTinyGeometry_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bFixTinyGeometry;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_TinyGeometryMinSizeCm;
	static void NewProp_bValidateGeometryCollectionAfterFracture_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bValidateGeometryCollectionAfterFracture;
	static void NewProp_bGenerateLeafConvexHulls_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bGenerateLeafConvexHulls;
	static void NewProp_bGenerateClusterConvexHulls_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bGenerateClusterConvexHulls;
	static void NewProp_bCreateNonOverlappingConvexHulls_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bCreateNonOverlappingConvexHulls;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGCBatchFractureSettings>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_OutputSubfolder = { "OutputSubfolder", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGCBatchFractureSettings, OutputSubfolder), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OutputSubfolder_MetaData), NewProp_OutputSubfolder_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_NamePrefix = { "NamePrefix", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGCBatchFractureSettings, NamePrefix), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NamePrefix_MetaData), NewProp_NamePrefix_MetaData) };
void Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_bSkipExistingAssets_SetBit(void* Obj)
{
	((UGCBatchFractureSettings*)Obj)->bSkipExistingAssets = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_bSkipExistingAssets = { "bSkipExistingAssets", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UGCBatchFractureSettings), &Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_bSkipExistingAssets_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bSkipExistingAssets_MetaData), NewProp_bSkipExistingAssets_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_SoftSelectionWarningCount = { "SoftSelectionWarningCount", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGCBatchFractureSettings, SoftSelectionWarningCount), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SoftSelectionWarningCount_MetaData), NewProp_SoftSelectionWarningCount_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_HardSelectionBlockCount = { "HardSelectionBlockCount", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGCBatchFractureSettings, HardSelectionBlockCount), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HardSelectionBlockCount_MetaData), NewProp_HardSelectionBlockCount_MetaData) };
void Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_bSaveAfterEachAsset_SetBit(void* Obj)
{
	((UGCBatchFractureSettings*)Obj)->bSaveAfterEachAsset = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_bSaveAfterEachAsset = { "bSaveAfterEachAsset", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UGCBatchFractureSettings), &Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_bSaveAfterEachAsset_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bSaveAfterEachAsset_MetaData), NewProp_bSaveAfterEachAsset_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_GarbageCollectEveryNAssets = { "GarbageCollectEveryNAssets", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGCBatchFractureSettings, GarbageCollectEveryNAssets), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_GarbageCollectEveryNAssets_MetaData), NewProp_GarbageCollectEveryNAssets_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_MaxTransformsAfterFracture = { "MaxTransformsAfterFracture", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGCBatchFractureSettings, MaxTransformsAfterFracture), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxTransformsAfterFracture_MetaData), NewProp_MaxTransformsAfterFracture_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_Preset_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_Preset = { "Preset", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGCBatchFractureSettings, Preset), Z_Construct_UEnum_GCBatchFracture_EGCBatchFracturePreset, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Preset_MetaData), NewProp_Preset_MetaData) }; // 3906274730
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_FractureLevelCount = { "FractureLevelCount", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGCBatchFractureSettings, FractureLevelCount), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FractureLevelCount_MetaData), NewProp_FractureLevelCount_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_VoronoiSites = { "VoronoiSites", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGCBatchFractureSettings, VoronoiSites), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_VoronoiSites_MetaData), NewProp_VoronoiSites_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_RandomSeed = { "RandomSeed", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGCBatchFractureSettings, RandomSeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RandomSeed_MetaData), NewProp_RandomSeed_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_RandomSeedOffsetPerLevel = { "RandomSeedOffsetPerLevel", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGCBatchFractureSettings, RandomSeedOffsetPerLevel), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RandomSeedOffsetPerLevel_MetaData), NewProp_RandomSeedOffsetPerLevel_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_ChanceToFracture = { "ChanceToFracture", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGCBatchFractureSettings, ChanceToFracture), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ChanceToFracture_MetaData), NewProp_ChanceToFracture_MetaData) };
void Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_bSplitIslands_SetBit(void* Obj)
{
	((UGCBatchFractureSettings*)Obj)->bSplitIslands = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_bSplitIslands = { "bSplitIslands", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UGCBatchFractureSettings), &Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_bSplitIslands_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bSplitIslands_MetaData), NewProp_bSplitIslands_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_Grout = { "Grout", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGCBatchFractureSettings, Grout), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Grout_MetaData), NewProp_Grout_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_PerLevelChanceToFracture = { "PerLevelChanceToFracture", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGCBatchFractureSettings, PerLevelChanceToFracture), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PerLevelChanceToFracture_MetaData), NewProp_PerLevelChanceToFracture_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_MaxTransformsToFracturePerLevel = { "MaxTransformsToFracturePerLevel", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGCBatchFractureSettings, MaxTransformsToFracturePerLevel), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxTransformsToFracturePerLevel_MetaData), NewProp_MaxTransformsToFracturePerLevel_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_MaxEstimatedFractureOperationsPerLevel = { "MaxEstimatedFractureOperationsPerLevel", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGCBatchFractureSettings, MaxEstimatedFractureOperationsPerLevel), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxEstimatedFractureOperationsPerLevel_MetaData), NewProp_MaxEstimatedFractureOperationsPerLevel_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_MaxSourceVertices = { "MaxSourceVertices", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGCBatchFractureSettings, MaxSourceVertices), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxSourceVertices_MetaData), NewProp_MaxSourceVertices_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_MaxSourceTriangles = { "MaxSourceTriangles", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGCBatchFractureSettings, MaxSourceTriangles), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxSourceTriangles_MetaData), NewProp_MaxSourceTriangles_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_Amplitude = { "Amplitude", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGCBatchFractureSettings, Amplitude), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Amplitude_MetaData), NewProp_Amplitude_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_Frequency = { "Frequency", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGCBatchFractureSettings, Frequency), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Frequency_MetaData), NewProp_Frequency_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_Persistence = { "Persistence", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGCBatchFractureSettings, Persistence), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Persistence_MetaData), NewProp_Persistence_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_Lacunarity = { "Lacunarity", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGCBatchFractureSettings, Lacunarity), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Lacunarity_MetaData), NewProp_Lacunarity_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_OctaveNumber = { "OctaveNumber", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGCBatchFractureSettings, OctaveNumber), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OctaveNumber_MetaData), NewProp_OctaveNumber_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_PointSpacing = { "PointSpacing", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGCBatchFractureSettings, PointSpacing), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PointSpacing_MetaData), NewProp_PointSpacing_MetaData) };
void Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_bAddSamplesForCollision_SetBit(void* Obj)
{
	((UGCBatchFractureSettings*)Obj)->bAddSamplesForCollision = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_bAddSamplesForCollision = { "bAddSamplesForCollision", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UGCBatchFractureSettings), &Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_bAddSamplesForCollision_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bAddSamplesForCollision_MetaData), NewProp_bAddSamplesForCollision_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_CollisionSampleSpacing = { "CollisionSampleSpacing", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGCBatchFractureSettings, CollisionSampleSpacing), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CollisionSampleSpacing_MetaData), NewProp_CollisionSampleSpacing_MetaData) };
void Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_bFixTinyGeometry_SetBit(void* Obj)
{
	((UGCBatchFractureSettings*)Obj)->bFixTinyGeometry = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_bFixTinyGeometry = { "bFixTinyGeometry", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UGCBatchFractureSettings), &Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_bFixTinyGeometry_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bFixTinyGeometry_MetaData), NewProp_bFixTinyGeometry_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_TinyGeometryMinSizeCm = { "TinyGeometryMinSizeCm", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGCBatchFractureSettings, TinyGeometryMinSizeCm), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TinyGeometryMinSizeCm_MetaData), NewProp_TinyGeometryMinSizeCm_MetaData) };
void Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_bValidateGeometryCollectionAfterFracture_SetBit(void* Obj)
{
	((UGCBatchFractureSettings*)Obj)->bValidateGeometryCollectionAfterFracture = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_bValidateGeometryCollectionAfterFracture = { "bValidateGeometryCollectionAfterFracture", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UGCBatchFractureSettings), &Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_bValidateGeometryCollectionAfterFracture_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bValidateGeometryCollectionAfterFracture_MetaData), NewProp_bValidateGeometryCollectionAfterFracture_MetaData) };
void Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_bGenerateLeafConvexHulls_SetBit(void* Obj)
{
	((UGCBatchFractureSettings*)Obj)->bGenerateLeafConvexHulls = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_bGenerateLeafConvexHulls = { "bGenerateLeafConvexHulls", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UGCBatchFractureSettings), &Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_bGenerateLeafConvexHulls_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bGenerateLeafConvexHulls_MetaData), NewProp_bGenerateLeafConvexHulls_MetaData) };
void Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_bGenerateClusterConvexHulls_SetBit(void* Obj)
{
	((UGCBatchFractureSettings*)Obj)->bGenerateClusterConvexHulls = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_bGenerateClusterConvexHulls = { "bGenerateClusterConvexHulls", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UGCBatchFractureSettings), &Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_bGenerateClusterConvexHulls_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bGenerateClusterConvexHulls_MetaData), NewProp_bGenerateClusterConvexHulls_MetaData) };
void Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_bCreateNonOverlappingConvexHulls_SetBit(void* Obj)
{
	((UGCBatchFractureSettings*)Obj)->bCreateNonOverlappingConvexHulls = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_bCreateNonOverlappingConvexHulls = { "bCreateNonOverlappingConvexHulls", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UGCBatchFractureSettings), &Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_bCreateNonOverlappingConvexHulls_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bCreateNonOverlappingConvexHulls_MetaData), NewProp_bCreateNonOverlappingConvexHulls_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UGCBatchFractureSettings_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_OutputSubfolder,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_NamePrefix,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_bSkipExistingAssets,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_SoftSelectionWarningCount,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_HardSelectionBlockCount,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_bSaveAfterEachAsset,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_GarbageCollectEveryNAssets,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_MaxTransformsAfterFracture,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_Preset_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_Preset,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_FractureLevelCount,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_VoronoiSites,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_RandomSeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_RandomSeedOffsetPerLevel,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_ChanceToFracture,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_bSplitIslands,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_Grout,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_PerLevelChanceToFracture,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_MaxTransformsToFracturePerLevel,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_MaxEstimatedFractureOperationsPerLevel,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_MaxSourceVertices,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_MaxSourceTriangles,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_Amplitude,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_Frequency,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_Persistence,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_Lacunarity,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_OctaveNumber,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_PointSpacing,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_bAddSamplesForCollision,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_CollisionSampleSpacing,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_bFixTinyGeometry,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_TinyGeometryMinSizeCm,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_bValidateGeometryCollectionAfterFracture,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_bGenerateLeafConvexHulls,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_bGenerateClusterConvexHulls,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGCBatchFractureSettings_Statics::NewProp_bCreateNonOverlappingConvexHulls,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UGCBatchFractureSettings_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UGCBatchFractureSettings_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UDeveloperSettings,
	(UObject* (*)())Z_Construct_UPackage__Script_GCBatchFracture,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UGCBatchFractureSettings_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UGCBatchFractureSettings_Statics::ClassParams = {
	&UGCBatchFractureSettings::StaticClass,
	"EditorPerProjectUserSettings",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UGCBatchFractureSettings_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UGCBatchFractureSettings_Statics::PropPointers),
	0,
	0x001000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UGCBatchFractureSettings_Statics::Class_MetaDataParams), Z_Construct_UClass_UGCBatchFractureSettings_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UGCBatchFractureSettings()
{
	if (!Z_Registration_Info_UClass_UGCBatchFractureSettings.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UGCBatchFractureSettings.OuterSingleton, Z_Construct_UClass_UGCBatchFractureSettings_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UGCBatchFractureSettings.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UGCBatchFractureSettings);
UGCBatchFractureSettings::~UGCBatchFractureSettings() {}
// ********** End Class UGCBatchFractureSettings ***************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Gregr_Plugins_GCBatchFracture_Source_GCBatchFracture_Public_GCBatchFractureSettings_h__Script_GCBatchFracture_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ EGCBatchFracturePreset_StaticEnum, TEXT("EGCBatchFracturePreset"), &Z_Registration_Info_UEnum_EGCBatchFracturePreset, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 3906274730U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UGCBatchFractureSettings, UGCBatchFractureSettings::StaticClass, TEXT("UGCBatchFractureSettings"), &Z_Registration_Info_UClass_UGCBatchFractureSettings, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UGCBatchFractureSettings), 2355110851U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Gregr_Plugins_GCBatchFracture_Source_GCBatchFracture_Public_GCBatchFractureSettings_h__Script_GCBatchFracture_946237124(TEXT("/Script/GCBatchFracture"),
	Z_CompiledInDeferFile_FID_Gregr_Plugins_GCBatchFracture_Source_GCBatchFracture_Public_GCBatchFractureSettings_h__Script_GCBatchFracture_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Gregr_Plugins_GCBatchFracture_Source_GCBatchFracture_Public_GCBatchFractureSettings_h__Script_GCBatchFracture_Statics::ClassInfo),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_Gregr_Plugins_GCBatchFracture_Source_GCBatchFracture_Public_GCBatchFractureSettings_h__Script_GCBatchFracture_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Gregr_Plugins_GCBatchFracture_Source_GCBatchFracture_Public_GCBatchFractureSettings_h__Script_GCBatchFracture_Statics::EnumInfo));
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS

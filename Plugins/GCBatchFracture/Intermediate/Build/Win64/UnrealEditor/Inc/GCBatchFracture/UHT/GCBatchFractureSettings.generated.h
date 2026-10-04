// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "GCBatchFractureSettings.h"

#ifdef GCBATCHFRACTURE_GCBatchFractureSettings_generated_h
#error "GCBatchFractureSettings.generated.h already included, missing '#pragma once' in GCBatchFractureSettings.h"
#endif
#define GCBATCHFRACTURE_GCBatchFractureSettings_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class UGCBatchFractureSettings *************************************************
GCBATCHFRACTURE_API UClass* Z_Construct_UClass_UGCBatchFractureSettings_NoRegister();

#define FID_Gregr_Plugins_GCBatchFracture_Source_GCBatchFracture_Public_GCBatchFractureSettings_h_21_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUGCBatchFractureSettings(); \
	friend struct Z_Construct_UClass_UGCBatchFractureSettings_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend GCBATCHFRACTURE_API UClass* Z_Construct_UClass_UGCBatchFractureSettings_NoRegister(); \
public: \
	DECLARE_CLASS2(UGCBatchFractureSettings, UDeveloperSettings, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/GCBatchFracture"), Z_Construct_UClass_UGCBatchFractureSettings_NoRegister) \
	DECLARE_SERIALIZER(UGCBatchFractureSettings) \
	static const TCHAR* StaticConfigName() {return TEXT("EditorPerProjectUserSettings");} \



#define FID_Gregr_Plugins_GCBatchFracture_Source_GCBatchFracture_Public_GCBatchFractureSettings_h_21_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	UGCBatchFractureSettings(UGCBatchFractureSettings&&) = delete; \
	UGCBatchFractureSettings(const UGCBatchFractureSettings&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UGCBatchFractureSettings); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UGCBatchFractureSettings); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UGCBatchFractureSettings) \
	NO_API virtual ~UGCBatchFractureSettings();


#define FID_Gregr_Plugins_GCBatchFracture_Source_GCBatchFracture_Public_GCBatchFractureSettings_h_18_PROLOG
#define FID_Gregr_Plugins_GCBatchFracture_Source_GCBatchFracture_Public_GCBatchFractureSettings_h_21_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Gregr_Plugins_GCBatchFracture_Source_GCBatchFracture_Public_GCBatchFractureSettings_h_21_INCLASS_NO_PURE_DECLS \
	FID_Gregr_Plugins_GCBatchFracture_Source_GCBatchFracture_Public_GCBatchFractureSettings_h_21_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UGCBatchFractureSettings;

// ********** End Class UGCBatchFractureSettings ***************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Gregr_Plugins_GCBatchFracture_Source_GCBatchFracture_Public_GCBatchFractureSettings_h

// ********** Begin Enum EGCBatchFracturePreset ****************************************************
#define FOREACH_ENUM_EGCBATCHFRACTUREPRESET(op) \
	op(EGCBatchFracturePreset::FastPreview) \
	op(EGCBatchFracturePreset::Balanced) \
	op(EGCBatchFracturePreset::RuntimeSafe) \
	op(EGCBatchFracturePreset::Custom) 

enum class EGCBatchFracturePreset : uint8;
template<> struct TIsUEnumClass<EGCBatchFracturePreset> { enum { Value = true }; };
template<> GCBATCHFRACTURE_API UEnum* StaticEnum<EGCBatchFracturePreset>();
// ********** End Enum EGCBatchFracturePreset ******************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS

// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "EnhancedChildActorComponent.h"

#ifdef ENHANCEDCHILDACTORCOMPONENT_EnhancedChildActorComponent_generated_h
#error "EnhancedChildActorComponent.generated.h already included, missing '#pragma once' in EnhancedChildActorComponent.h"
#endif
#define ENHANCEDCHILDACTORCOMPONENT_EnhancedChildActorComponent_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

class AActor;

// ********** Begin Class UEnhancedChildActorComponent *********************************************
#define FID_PluginsBox_Plugins_EnhancedChildActorComponent_Source_EnhancedChildActorComponent_Public_EnhancedChildActorComponent_h_17_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execDestroyChildActor); \
	DECLARE_FUNCTION(execCreateChildActor); \
	DECLARE_FUNCTION(execGetChildActor);


ENHANCEDCHILDACTORCOMPONENT_API UClass* Z_Construct_UClass_UEnhancedChildActorComponent_NoRegister();

#define FID_PluginsBox_Plugins_EnhancedChildActorComponent_Source_EnhancedChildActorComponent_Public_EnhancedChildActorComponent_h_17_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUEnhancedChildActorComponent(); \
	friend struct Z_Construct_UClass_UEnhancedChildActorComponent_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend ENHANCEDCHILDACTORCOMPONENT_API UClass* Z_Construct_UClass_UEnhancedChildActorComponent_NoRegister(); \
public: \
	DECLARE_CLASS2(UEnhancedChildActorComponent, USceneComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/EnhancedChildActorComponent"), Z_Construct_UClass_UEnhancedChildActorComponent_NoRegister) \
	DECLARE_SERIALIZER(UEnhancedChildActorComponent)


#define FID_PluginsBox_Plugins_EnhancedChildActorComponent_Source_EnhancedChildActorComponent_Public_EnhancedChildActorComponent_h_17_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	UEnhancedChildActorComponent(UEnhancedChildActorComponent&&) = delete; \
	UEnhancedChildActorComponent(const UEnhancedChildActorComponent&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UEnhancedChildActorComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UEnhancedChildActorComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UEnhancedChildActorComponent) \
	NO_API virtual ~UEnhancedChildActorComponent();


#define FID_PluginsBox_Plugins_EnhancedChildActorComponent_Source_EnhancedChildActorComponent_Public_EnhancedChildActorComponent_h_14_PROLOG
#define FID_PluginsBox_Plugins_EnhancedChildActorComponent_Source_EnhancedChildActorComponent_Public_EnhancedChildActorComponent_h_17_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_PluginsBox_Plugins_EnhancedChildActorComponent_Source_EnhancedChildActorComponent_Public_EnhancedChildActorComponent_h_17_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_PluginsBox_Plugins_EnhancedChildActorComponent_Source_EnhancedChildActorComponent_Public_EnhancedChildActorComponent_h_17_INCLASS_NO_PURE_DECLS \
	FID_PluginsBox_Plugins_EnhancedChildActorComponent_Source_EnhancedChildActorComponent_Public_EnhancedChildActorComponent_h_17_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UEnhancedChildActorComponent;

// ********** End Class UEnhancedChildActorComponent ***********************************************

// ********** Begin ScriptStruct FEnhancedChildActorComponentInstanceData **************************
#define FID_PluginsBox_Plugins_EnhancedChildActorComponent_Source_EnhancedChildActorComponent_Public_EnhancedChildActorComponent_h_77_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FEnhancedChildActorComponentInstanceData_Statics; \
	ENHANCEDCHILDACTORCOMPONENT_API static class UScriptStruct* StaticStruct(); \
	typedef FSceneComponentInstanceData Super;


struct FEnhancedChildActorComponentInstanceData;
// ********** End ScriptStruct FEnhancedChildActorComponentInstanceData ****************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_PluginsBox_Plugins_EnhancedChildActorComponent_Source_EnhancedChildActorComponent_Public_EnhancedChildActorComponent_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS

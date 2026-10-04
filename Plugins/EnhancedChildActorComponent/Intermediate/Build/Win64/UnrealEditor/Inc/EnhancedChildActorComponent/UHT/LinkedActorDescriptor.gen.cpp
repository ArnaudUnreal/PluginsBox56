// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LinkedActorDescriptor.h"
#include "StructUtils/PropertyBag.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeLinkedActorDescriptor() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FGuid();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FInstancedPropertyBag();
ENGINE_API UClass* Z_Construct_UClass_AActor_NoRegister();
ENHANCEDCHILDACTORCOMPONENT_API UScriptStruct* Z_Construct_UScriptStruct_FLinkedActorDescriptor();
UPackage* Z_Construct_UPackage__Script_EnhancedChildActorComponent();
// ********** End Cross Module References **********************************************************

// ********** Begin ScriptStruct FLinkedActorDescriptor ********************************************
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FLinkedActorDescriptor;
class UScriptStruct* FLinkedActorDescriptor::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FLinkedActorDescriptor.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FLinkedActorDescriptor.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FLinkedActorDescriptor, (UObject*)Z_Construct_UPackage__Script_EnhancedChildActorComponent(), TEXT("LinkedActorDescriptor"));
	}
	return Z_Registration_Info_UScriptStruct_FLinkedActorDescriptor.OuterSingleton;
}
struct Z_Construct_UScriptStruct_FLinkedActorDescriptor_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Describes the child actor owned by an UEnhancedChildActorComponent.\n * Only this descriptor is serialized with the parent: the child itself is a runtime projection of it.\n */" },
#endif
		{ "ModuleRelativePath", "Public/LinkedActorDescriptor.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Describes the child actor owned by an UEnhancedChildActorComponent.\nOnly this descriptor is serialized with the parent: the child itself is a runtime projection of it." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ChildClass_MetaData[] = {
		{ "Category", "Linked Actor" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Class of the child actor to spawn. */" },
#endif
		{ "ModuleRelativePath", "Public/LinkedActorDescriptor.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Class of the child actor to spawn." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Overrides_MetaData[] = {
		{ "Category", "Linked Actor" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Property values applied to the child between SpawnActorDeferred and FinishSpawning, matched by name and type. */" },
#endif
		{ "ModuleRelativePath", "Public/LinkedActorDescriptor.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Property values applied to the child between SpawnActorDeferred and FinishSpawning, matched by name and type." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LinkGuid_MetaData[] = {
		{ "Category", "Linked Actor" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Stable identifier of the link between the parent and its child. */" },
#endif
		{ "ModuleRelativePath", "Public/LinkedActorDescriptor.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Stable identifier of the link between the parent and its child." },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FSoftClassPropertyParams NewProp_ChildClass;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Overrides;
	static const UECodeGen_Private::FStructPropertyParams NewProp_LinkGuid;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLinkedActorDescriptor>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FSoftClassPropertyParams Z_Construct_UScriptStruct_FLinkedActorDescriptor_Statics::NewProp_ChildClass = { "ChildClass", nullptr, (EPropertyFlags)0x0014000000000015, UECodeGen_Private::EPropertyGenFlags::SoftClass, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLinkedActorDescriptor, ChildClass), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ChildClass_MetaData), NewProp_ChildClass_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLinkedActorDescriptor_Statics::NewProp_Overrides = { "Overrides", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLinkedActorDescriptor, Overrides), Z_Construct_UScriptStruct_FInstancedPropertyBag, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Overrides_MetaData), NewProp_Overrides_MetaData) }; // 378924096
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLinkedActorDescriptor_Statics::NewProp_LinkGuid = { "LinkGuid", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLinkedActorDescriptor, LinkGuid), Z_Construct_UScriptStruct_FGuid, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LinkGuid_MetaData), NewProp_LinkGuid_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FLinkedActorDescriptor_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLinkedActorDescriptor_Statics::NewProp_ChildClass,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLinkedActorDescriptor_Statics::NewProp_Overrides,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLinkedActorDescriptor_Statics::NewProp_LinkGuid,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLinkedActorDescriptor_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FLinkedActorDescriptor_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_EnhancedChildActorComponent,
	nullptr,
	&NewStructOps,
	"LinkedActorDescriptor",
	Z_Construct_UScriptStruct_FLinkedActorDescriptor_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLinkedActorDescriptor_Statics::PropPointers),
	sizeof(FLinkedActorDescriptor),
	alignof(FLinkedActorDescriptor),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLinkedActorDescriptor_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FLinkedActorDescriptor_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FLinkedActorDescriptor()
{
	if (!Z_Registration_Info_UScriptStruct_FLinkedActorDescriptor.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FLinkedActorDescriptor.InnerSingleton, Z_Construct_UScriptStruct_FLinkedActorDescriptor_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_FLinkedActorDescriptor.InnerSingleton;
}
// ********** End ScriptStruct FLinkedActorDescriptor **********************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_PluginsBox_Plugins_EnhancedChildActorComponent_Source_EnhancedChildActorComponent_Public_LinkedActorDescriptor_h__Script_EnhancedChildActorComponent_Statics
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FLinkedActorDescriptor::StaticStruct, Z_Construct_UScriptStruct_FLinkedActorDescriptor_Statics::NewStructOps, TEXT("LinkedActorDescriptor"), &Z_Registration_Info_UScriptStruct_FLinkedActorDescriptor, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FLinkedActorDescriptor), 1794327177U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_PluginsBox_Plugins_EnhancedChildActorComponent_Source_EnhancedChildActorComponent_Public_LinkedActorDescriptor_h__Script_EnhancedChildActorComponent_2186593798(TEXT("/Script/EnhancedChildActorComponent"),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_PluginsBox_Plugins_EnhancedChildActorComponent_Source_EnhancedChildActorComponent_Public_LinkedActorDescriptor_h__Script_EnhancedChildActorComponent_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_PluginsBox_Plugins_EnhancedChildActorComponent_Source_EnhancedChildActorComponent_Public_LinkedActorDescriptor_h__Script_EnhancedChildActorComponent_Statics::ScriptStructInfo),
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS

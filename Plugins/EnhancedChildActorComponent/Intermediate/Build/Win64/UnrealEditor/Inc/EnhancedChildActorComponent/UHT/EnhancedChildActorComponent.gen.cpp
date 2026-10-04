// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "EnhancedChildActorComponent.h"
#include "LinkedActorDescriptor.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeEnhancedChildActorComponent() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FGuid();
ENGINE_API UClass* Z_Construct_UClass_AActor_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USceneComponent();
ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FSceneComponentInstanceData();
ENHANCEDCHILDACTORCOMPONENT_API UClass* Z_Construct_UClass_UEnhancedChildActorComponent();
ENHANCEDCHILDACTORCOMPONENT_API UClass* Z_Construct_UClass_UEnhancedChildActorComponent_NoRegister();
ENHANCEDCHILDACTORCOMPONENT_API UScriptStruct* Z_Construct_UScriptStruct_FEnhancedChildActorComponentInstanceData();
ENHANCEDCHILDACTORCOMPONENT_API UScriptStruct* Z_Construct_UScriptStruct_FLinkedActorDescriptor();
UPackage* Z_Construct_UPackage__Script_EnhancedChildActorComponent();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UEnhancedChildActorComponent Function CreateChildActor *******************
struct Z_Construct_UFunction_UEnhancedChildActorComponent_CreateChildActor_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Linked Actor" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Spawns the child actor from the descriptor. Destroys the previous one first. */" },
#endif
		{ "ModuleRelativePath", "Public/EnhancedChildActorComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Spawns the child actor from the descriptor. Destroys the previous one first." },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UEnhancedChildActorComponent_CreateChildActor_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UEnhancedChildActorComponent, nullptr, "CreateChildActor", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UEnhancedChildActorComponent_CreateChildActor_Statics::Function_MetaDataParams), Z_Construct_UFunction_UEnhancedChildActorComponent_CreateChildActor_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_UEnhancedChildActorComponent_CreateChildActor()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UEnhancedChildActorComponent_CreateChildActor_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UEnhancedChildActorComponent::execCreateChildActor)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->CreateChildActor();
	P_NATIVE_END;
}
// ********** End Class UEnhancedChildActorComponent Function CreateChildActor *********************

// ********** Begin Class UEnhancedChildActorComponent Function DestroyChildActor ******************
struct Z_Construct_UFunction_UEnhancedChildActorComponent_DestroyChildActor_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Linked Actor" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Destroys the child actor if it exists. */" },
#endif
		{ "ModuleRelativePath", "Public/EnhancedChildActorComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Destroys the child actor if it exists." },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UEnhancedChildActorComponent_DestroyChildActor_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UEnhancedChildActorComponent, nullptr, "DestroyChildActor", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UEnhancedChildActorComponent_DestroyChildActor_Statics::Function_MetaDataParams), Z_Construct_UFunction_UEnhancedChildActorComponent_DestroyChildActor_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_UEnhancedChildActorComponent_DestroyChildActor()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UEnhancedChildActorComponent_DestroyChildActor_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UEnhancedChildActorComponent::execDestroyChildActor)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->DestroyChildActor();
	P_NATIVE_END;
}
// ********** End Class UEnhancedChildActorComponent Function DestroyChildActor ********************

// ********** Begin Class UEnhancedChildActorComponent Function GetChildActor **********************
struct Z_Construct_UFunction_UEnhancedChildActorComponent_GetChildActor_Statics
{
	struct EnhancedChildActorComponent_eventGetChildActor_Parms
	{
		AActor* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Linked Actor" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Returns the spawned child actor, or nullptr if it does not exist. */" },
#endif
		{ "ModuleRelativePath", "Public/EnhancedChildActorComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Returns the spawned child actor, or nullptr if it does not exist." },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UEnhancedChildActorComponent_GetChildActor_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(EnhancedChildActorComponent_eventGetChildActor_Parms, ReturnValue), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UEnhancedChildActorComponent_GetChildActor_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UEnhancedChildActorComponent_GetChildActor_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UEnhancedChildActorComponent_GetChildActor_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UEnhancedChildActorComponent_GetChildActor_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UEnhancedChildActorComponent, nullptr, "GetChildActor", Z_Construct_UFunction_UEnhancedChildActorComponent_GetChildActor_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UEnhancedChildActorComponent_GetChildActor_Statics::PropPointers), sizeof(Z_Construct_UFunction_UEnhancedChildActorComponent_GetChildActor_Statics::EnhancedChildActorComponent_eventGetChildActor_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UEnhancedChildActorComponent_GetChildActor_Statics::Function_MetaDataParams), Z_Construct_UFunction_UEnhancedChildActorComponent_GetChildActor_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UEnhancedChildActorComponent_GetChildActor_Statics::EnhancedChildActorComponent_eventGetChildActor_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UEnhancedChildActorComponent_GetChildActor()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UEnhancedChildActorComponent_GetChildActor_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UEnhancedChildActorComponent::execGetChildActor)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(AActor**)Z_Param__Result=P_THIS->GetChildActor();
	P_NATIVE_END;
}
// ********** End Class UEnhancedChildActorComponent Function GetChildActor ************************

// ********** Begin Class UEnhancedChildActorComponent *********************************************
void UEnhancedChildActorComponent::StaticRegisterNativesUEnhancedChildActorComponent()
{
	UClass* Class = UEnhancedChildActorComponent::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "CreateChildActor", &UEnhancedChildActorComponent::execCreateChildActor },
		{ "DestroyChildActor", &UEnhancedChildActorComponent::execDestroyChildActor },
		{ "GetChildActor", &UEnhancedChildActorComponent::execGetChildActor },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UEnhancedChildActorComponent;
UClass* UEnhancedChildActorComponent::GetPrivateStaticClass()
{
	using TClass = UEnhancedChildActorComponent;
	if (!Z_Registration_Info_UClass_UEnhancedChildActorComponent.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("EnhancedChildActorComponent"),
			Z_Registration_Info_UClass_UEnhancedChildActorComponent.InnerSingleton,
			StaticRegisterNativesUEnhancedChildActorComponent,
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
	return Z_Registration_Info_UClass_UEnhancedChildActorComponent.InnerSingleton;
}
UClass* Z_Construct_UClass_UEnhancedChildActorComponent_NoRegister()
{
	return UEnhancedChildActorComponent::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UEnhancedChildActorComponent_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Utility" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Alternative to UChildActorComponent.\n * Spawns a child actor from a descriptor and attaches it to this component.\n */" },
#endif
		{ "HideCategories", "Trigger PhysicsVolume" },
		{ "IncludePath", "EnhancedChildActorComponent.h" },
		{ "ModuleRelativePath", "Public/EnhancedChildActorComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Alternative to UChildActorComponent.\nSpawns a child actor from a descriptor and attaches it to this component." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Descriptor_MetaData[] = {
		{ "Category", "Linked Actor" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Serialized description of the child. */" },
#endif
		{ "ModuleRelativePath", "Public/EnhancedChildActorComponent.h" },
		{ "ShowOnlyInnerProperties", "" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Serialized description of the child." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ChildActor_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** The spawned child. Never serialized: it is rebuilt from the descriptor. */" },
#endif
		{ "ModuleRelativePath", "Public/EnhancedChildActorComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The spawned child. Never serialized: it is rebuilt from the descriptor." },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_Descriptor;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ChildActor;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UEnhancedChildActorComponent_CreateChildActor, "CreateChildActor" }, // 3106063551
		{ &Z_Construct_UFunction_UEnhancedChildActorComponent_DestroyChildActor, "DestroyChildActor" }, // 4155259467
		{ &Z_Construct_UFunction_UEnhancedChildActorComponent_GetChildActor, "GetChildActor" }, // 2157235500
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UEnhancedChildActorComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UEnhancedChildActorComponent_Statics::NewProp_Descriptor = { "Descriptor", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UEnhancedChildActorComponent, Descriptor), Z_Construct_UScriptStruct_FLinkedActorDescriptor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Descriptor_MetaData), NewProp_Descriptor_MetaData) }; // 1794327177
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UEnhancedChildActorComponent_Statics::NewProp_ChildActor = { "ChildActor", nullptr, (EPropertyFlags)0x0144000000202000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UEnhancedChildActorComponent, ChildActor), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ChildActor_MetaData), NewProp_ChildActor_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UEnhancedChildActorComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UEnhancedChildActorComponent_Statics::NewProp_Descriptor,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UEnhancedChildActorComponent_Statics::NewProp_ChildActor,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UEnhancedChildActorComponent_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UEnhancedChildActorComponent_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_USceneComponent,
	(UObject* (*)())Z_Construct_UPackage__Script_EnhancedChildActorComponent,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UEnhancedChildActorComponent_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UEnhancedChildActorComponent_Statics::ClassParams = {
	&UEnhancedChildActorComponent::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UEnhancedChildActorComponent_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UEnhancedChildActorComponent_Statics::PropPointers),
	0,
	0x00B000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UEnhancedChildActorComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_UEnhancedChildActorComponent_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UEnhancedChildActorComponent()
{
	if (!Z_Registration_Info_UClass_UEnhancedChildActorComponent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UEnhancedChildActorComponent.OuterSingleton, Z_Construct_UClass_UEnhancedChildActorComponent_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UEnhancedChildActorComponent.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UEnhancedChildActorComponent);
UEnhancedChildActorComponent::~UEnhancedChildActorComponent() {}
// ********** End Class UEnhancedChildActorComponent ***********************************************

// ********** Begin ScriptStruct FEnhancedChildActorComponentInstanceData **************************
static_assert(std::is_polymorphic<FEnhancedChildActorComponentInstanceData>() == std::is_polymorphic<FSceneComponentInstanceData>(), "USTRUCT FEnhancedChildActorComponentInstanceData cannot be polymorphic unless super FSceneComponentInstanceData is polymorphic");
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FEnhancedChildActorComponentInstanceData;
class UScriptStruct* FEnhancedChildActorComponentInstanceData::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FEnhancedChildActorComponentInstanceData.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FEnhancedChildActorComponentInstanceData.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FEnhancedChildActorComponentInstanceData, (UObject*)Z_Construct_UPackage__Script_EnhancedChildActorComponent(), TEXT("EnhancedChildActorComponentInstanceData"));
	}
	return Z_Registration_Info_UScriptStruct_FEnhancedChildActorComponentInstanceData.OuterSingleton;
}
struct Z_Construct_UScriptStruct_FEnhancedChildActorComponentInstanceData_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Carries the link GUID across a rerun of the owner's construction script,\n * whatever the component's creation method (SCS, UCS or instance).\n */" },
#endif
		{ "ModuleRelativePath", "Public/EnhancedChildActorComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Carries the link GUID across a rerun of the owner's construction script,\nwhatever the component's creation method (SCS, UCS or instance)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LinkGuid_MetaData[] = {
		{ "ModuleRelativePath", "Public/EnhancedChildActorComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_LinkGuid;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FEnhancedChildActorComponentInstanceData>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FEnhancedChildActorComponentInstanceData_Statics::NewProp_LinkGuid = { "LinkGuid", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEnhancedChildActorComponentInstanceData, LinkGuid), Z_Construct_UScriptStruct_FGuid, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LinkGuid_MetaData), NewProp_LinkGuid_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FEnhancedChildActorComponentInstanceData_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEnhancedChildActorComponentInstanceData_Statics::NewProp_LinkGuid,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FEnhancedChildActorComponentInstanceData_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FEnhancedChildActorComponentInstanceData_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_EnhancedChildActorComponent,
	Z_Construct_UScriptStruct_FSceneComponentInstanceData,
	&NewStructOps,
	"EnhancedChildActorComponentInstanceData",
	Z_Construct_UScriptStruct_FEnhancedChildActorComponentInstanceData_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FEnhancedChildActorComponentInstanceData_Statics::PropPointers),
	sizeof(FEnhancedChildActorComponentInstanceData),
	alignof(FEnhancedChildActorComponentInstanceData),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000005),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FEnhancedChildActorComponentInstanceData_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FEnhancedChildActorComponentInstanceData_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FEnhancedChildActorComponentInstanceData()
{
	if (!Z_Registration_Info_UScriptStruct_FEnhancedChildActorComponentInstanceData.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FEnhancedChildActorComponentInstanceData.InnerSingleton, Z_Construct_UScriptStruct_FEnhancedChildActorComponentInstanceData_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_FEnhancedChildActorComponentInstanceData.InnerSingleton;
}
// ********** End ScriptStruct FEnhancedChildActorComponentInstanceData ****************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_PluginsBox_Plugins_EnhancedChildActorComponent_Source_EnhancedChildActorComponent_Public_EnhancedChildActorComponent_h__Script_EnhancedChildActorComponent_Statics
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FEnhancedChildActorComponentInstanceData::StaticStruct, Z_Construct_UScriptStruct_FEnhancedChildActorComponentInstanceData_Statics::NewStructOps, TEXT("EnhancedChildActorComponentInstanceData"), &Z_Registration_Info_UScriptStruct_FEnhancedChildActorComponentInstanceData, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FEnhancedChildActorComponentInstanceData), 2691293586U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UEnhancedChildActorComponent, UEnhancedChildActorComponent::StaticClass, TEXT("UEnhancedChildActorComponent"), &Z_Registration_Info_UClass_UEnhancedChildActorComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UEnhancedChildActorComponent), 3497967712U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_PluginsBox_Plugins_EnhancedChildActorComponent_Source_EnhancedChildActorComponent_Public_EnhancedChildActorComponent_h__Script_EnhancedChildActorComponent_4115894974(TEXT("/Script/EnhancedChildActorComponent"),
	Z_CompiledInDeferFile_FID_PluginsBox_Plugins_EnhancedChildActorComponent_Source_EnhancedChildActorComponent_Public_EnhancedChildActorComponent_h__Script_EnhancedChildActorComponent_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_PluginsBox_Plugins_EnhancedChildActorComponent_Source_EnhancedChildActorComponent_Public_EnhancedChildActorComponent_h__Script_EnhancedChildActorComponent_Statics::ClassInfo),
	Z_CompiledInDeferFile_FID_PluginsBox_Plugins_EnhancedChildActorComponent_Source_EnhancedChildActorComponent_Public_EnhancedChildActorComponent_h__Script_EnhancedChildActorComponent_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_PluginsBox_Plugins_EnhancedChildActorComponent_Source_EnhancedChildActorComponent_Public_EnhancedChildActorComponent_h__Script_EnhancedChildActorComponent_Statics::ScriptStructInfo),
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS

// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SlateNotificationsBFL.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeSlateNotificationsBFL() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_UBlueprintFunctionLibrary();
SLATENOTIFICATIONS_API UClass* Z_Construct_UClass_USlateNotificationsBFL();
SLATENOTIFICATIONS_API UClass* Z_Construct_UClass_USlateNotificationsBFL_NoRegister();
SLATENOTIFICATIONS_API UEnum* Z_Construct_UEnum_SlateNotifications_EMessageType();
UPackage* Z_Construct_UPackage__Script_SlateNotifications();
// ********** End Cross Module References **********************************************************

// ********** Begin Enum EMessageType **************************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EMessageType;
static UEnum* EMessageType_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EMessageType.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EMessageType.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_SlateNotifications_EMessageType, (UObject*)Z_Construct_UPackage__Script_SlateNotifications(), TEXT("EMessageType"));
	}
	return Z_Registration_Info_UEnum_EMessageType.OuterSingleton;
}
template<> SLATENOTIFICATIONS_API UEnum* StaticEnum<EMessageType>()
{
	return EMessageType_StaticEnum();
}
struct Z_Construct_UEnum_SlateNotifications_EMessageType_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Error.DisplayName", "Error" },
		{ "Error.Name", "EMessageType::Error" },
		{ "ModuleRelativePath", "Public/SlateNotificationsBFL.h" },
		{ "Success.DisplayName", "Success" },
		{ "Success.Name", "EMessageType::Success" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EMessageType::Success", (int64)EMessageType::Success },
		{ "EMessageType::Error", (int64)EMessageType::Error },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_SlateNotifications_EMessageType_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_SlateNotifications,
	nullptr,
	"EMessageType",
	"EMessageType",
	Z_Construct_UEnum_SlateNotifications_EMessageType_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_SlateNotifications_EMessageType_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_SlateNotifications_EMessageType_Statics::Enum_MetaDataParams), Z_Construct_UEnum_SlateNotifications_EMessageType_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_SlateNotifications_EMessageType()
{
	if (!Z_Registration_Info_UEnum_EMessageType.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EMessageType.InnerSingleton, Z_Construct_UEnum_SlateNotifications_EMessageType_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EMessageType.InnerSingleton;
}
// ********** End Enum EMessageType ****************************************************************

// ********** Begin Class USlateNotificationsBFL Function SlateNotify ******************************
struct Z_Construct_UFunction_USlateNotificationsBFL_SlateNotify_Statics
{
	struct SlateNotificationsBFL_eventSlateNotify_Parms
	{
		FText NotificationText;
		EMessageType MessageType;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "SlateNotifications" },
		{ "ModuleRelativePath", "Public/SlateNotificationsBFL.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NotificationText_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MessageType_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FTextPropertyParams NewProp_NotificationText;
	static const UECodeGen_Private::FBytePropertyParams NewProp_MessageType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_MessageType;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FTextPropertyParams Z_Construct_UFunction_USlateNotificationsBFL_SlateNotify_Statics::NewProp_NotificationText = { "NotificationText", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Text, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(SlateNotificationsBFL_eventSlateNotify_Parms, NotificationText), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NotificationText_MetaData), NewProp_NotificationText_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_USlateNotificationsBFL_SlateNotify_Statics::NewProp_MessageType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_USlateNotificationsBFL_SlateNotify_Statics::NewProp_MessageType = { "MessageType", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(SlateNotificationsBFL_eventSlateNotify_Parms, MessageType), Z_Construct_UEnum_SlateNotifications_EMessageType, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MessageType_MetaData), NewProp_MessageType_MetaData) }; // 742838492
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USlateNotificationsBFL_SlateNotify_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USlateNotificationsBFL_SlateNotify_Statics::NewProp_NotificationText,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USlateNotificationsBFL_SlateNotify_Statics::NewProp_MessageType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USlateNotificationsBFL_SlateNotify_Statics::NewProp_MessageType,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_USlateNotificationsBFL_SlateNotify_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_USlateNotificationsBFL_SlateNotify_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_USlateNotificationsBFL, nullptr, "SlateNotify", Z_Construct_UFunction_USlateNotificationsBFL_SlateNotify_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USlateNotificationsBFL_SlateNotify_Statics::PropPointers), sizeof(Z_Construct_UFunction_USlateNotificationsBFL_SlateNotify_Statics::SlateNotificationsBFL_eventSlateNotify_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04442401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_USlateNotificationsBFL_SlateNotify_Statics::Function_MetaDataParams), Z_Construct_UFunction_USlateNotificationsBFL_SlateNotify_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_USlateNotificationsBFL_SlateNotify_Statics::SlateNotificationsBFL_eventSlateNotify_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_USlateNotificationsBFL_SlateNotify()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_USlateNotificationsBFL_SlateNotify_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(USlateNotificationsBFL::execSlateNotify)
{
	P_GET_PROPERTY_REF(FTextProperty,Z_Param_Out_NotificationText);
	P_GET_ENUM_REF(EMessageType,Z_Param_Out_MessageType);
	P_FINISH;
	P_NATIVE_BEGIN;
	USlateNotificationsBFL::SlateNotify(Z_Param_Out_NotificationText,(EMessageType&)(Z_Param_Out_MessageType));
	P_NATIVE_END;
}
// ********** End Class USlateNotificationsBFL Function SlateNotify ********************************

// ********** Begin Class USlateNotificationsBFL ***************************************************
void USlateNotificationsBFL::StaticRegisterNativesUSlateNotificationsBFL()
{
	UClass* Class = USlateNotificationsBFL::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "SlateNotify", &USlateNotificationsBFL::execSlateNotify },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_USlateNotificationsBFL;
UClass* USlateNotificationsBFL::GetPrivateStaticClass()
{
	using TClass = USlateNotificationsBFL;
	if (!Z_Registration_Info_UClass_USlateNotificationsBFL.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("SlateNotificationsBFL"),
			Z_Registration_Info_UClass_USlateNotificationsBFL.InnerSingleton,
			StaticRegisterNativesUSlateNotificationsBFL,
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
	return Z_Registration_Info_UClass_USlateNotificationsBFL.InnerSingleton;
}
UClass* Z_Construct_UClass_USlateNotificationsBFL_NoRegister()
{
	return USlateNotificationsBFL::GetPrivateStaticClass();
}
struct Z_Construct_UClass_USlateNotificationsBFL_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "SlateNotificationsBFL.h" },
		{ "ModuleRelativePath", "Public/SlateNotificationsBFL.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_USlateNotificationsBFL_SlateNotify, "SlateNotify" }, // 75090160
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<USlateNotificationsBFL>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_USlateNotificationsBFL_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UBlueprintFunctionLibrary,
	(UObject* (*)())Z_Construct_UPackage__Script_SlateNotifications,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_USlateNotificationsBFL_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_USlateNotificationsBFL_Statics::ClassParams = {
	&USlateNotificationsBFL::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	0,
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_USlateNotificationsBFL_Statics::Class_MetaDataParams), Z_Construct_UClass_USlateNotificationsBFL_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_USlateNotificationsBFL()
{
	if (!Z_Registration_Info_UClass_USlateNotificationsBFL.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_USlateNotificationsBFL.OuterSingleton, Z_Construct_UClass_USlateNotificationsBFL_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_USlateNotificationsBFL.OuterSingleton;
}
USlateNotificationsBFL::USlateNotificationsBFL(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(USlateNotificationsBFL);
USlateNotificationsBFL::~USlateNotificationsBFL() {}
// ********** End Class USlateNotificationsBFL *****************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Gregr_Plugins_SlateNotifications_Source_SlateNotifications_Public_SlateNotificationsBFL_h__Script_SlateNotifications_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ EMessageType_StaticEnum, TEXT("EMessageType"), &Z_Registration_Info_UEnum_EMessageType, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 742838492U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_USlateNotificationsBFL, USlateNotificationsBFL::StaticClass, TEXT("USlateNotificationsBFL"), &Z_Registration_Info_UClass_USlateNotificationsBFL, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(USlateNotificationsBFL), 841885947U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Gregr_Plugins_SlateNotifications_Source_SlateNotifications_Public_SlateNotificationsBFL_h__Script_SlateNotifications_3780759816(TEXT("/Script/SlateNotifications"),
	Z_CompiledInDeferFile_FID_Gregr_Plugins_SlateNotifications_Source_SlateNotifications_Public_SlateNotificationsBFL_h__Script_SlateNotifications_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Gregr_Plugins_SlateNotifications_Source_SlateNotifications_Public_SlateNotificationsBFL_h__Script_SlateNotifications_Statics::ClassInfo),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_Gregr_Plugins_SlateNotifications_Source_SlateNotifications_Public_SlateNotificationsBFL_h__Script_SlateNotifications_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Gregr_Plugins_SlateNotifications_Source_SlateNotifications_Public_SlateNotificationsBFL_h__Script_SlateNotifications_Statics::EnumInfo));
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS

// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "SlateNotificationsBFL.h"

#ifdef SLATENOTIFICATIONS_SlateNotificationsBFL_generated_h
#error "SlateNotificationsBFL.generated.h already included, missing '#pragma once' in SlateNotificationsBFL.h"
#endif
#define SLATENOTIFICATIONS_SlateNotificationsBFL_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

enum class EMessageType : uint8;

// ********** Begin Class USlateNotificationsBFL ***************************************************
#define FID_Gregr_Plugins_SlateNotifications_Source_SlateNotifications_Public_SlateNotificationsBFL_h_18_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execSlateNotify);


SLATENOTIFICATIONS_API UClass* Z_Construct_UClass_USlateNotificationsBFL_NoRegister();

#define FID_Gregr_Plugins_SlateNotifications_Source_SlateNotifications_Public_SlateNotificationsBFL_h_18_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUSlateNotificationsBFL(); \
	friend struct Z_Construct_UClass_USlateNotificationsBFL_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend SLATENOTIFICATIONS_API UClass* Z_Construct_UClass_USlateNotificationsBFL_NoRegister(); \
public: \
	DECLARE_CLASS2(USlateNotificationsBFL, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/SlateNotifications"), Z_Construct_UClass_USlateNotificationsBFL_NoRegister) \
	DECLARE_SERIALIZER(USlateNotificationsBFL)


#define FID_Gregr_Plugins_SlateNotifications_Source_SlateNotifications_Public_SlateNotificationsBFL_h_18_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API USlateNotificationsBFL(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	USlateNotificationsBFL(USlateNotificationsBFL&&) = delete; \
	USlateNotificationsBFL(const USlateNotificationsBFL&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, USlateNotificationsBFL); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(USlateNotificationsBFL); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(USlateNotificationsBFL) \
	NO_API virtual ~USlateNotificationsBFL();


#define FID_Gregr_Plugins_SlateNotifications_Source_SlateNotifications_Public_SlateNotificationsBFL_h_15_PROLOG
#define FID_Gregr_Plugins_SlateNotifications_Source_SlateNotifications_Public_SlateNotificationsBFL_h_18_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Gregr_Plugins_SlateNotifications_Source_SlateNotifications_Public_SlateNotificationsBFL_h_18_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Gregr_Plugins_SlateNotifications_Source_SlateNotifications_Public_SlateNotificationsBFL_h_18_INCLASS_NO_PURE_DECLS \
	FID_Gregr_Plugins_SlateNotifications_Source_SlateNotifications_Public_SlateNotificationsBFL_h_18_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class USlateNotificationsBFL;

// ********** End Class USlateNotificationsBFL *****************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Gregr_Plugins_SlateNotifications_Source_SlateNotifications_Public_SlateNotificationsBFL_h

// ********** Begin Enum EMessageType **************************************************************
#define FOREACH_ENUM_EMESSAGETYPE(op) \
	op(EMessageType::Success) \
	op(EMessageType::Error) 

enum class EMessageType : uint8;
template<> struct TIsUEnumClass<EMessageType> { enum { Value = true }; };
template<> SLATENOTIFICATIONS_API UEnum* StaticEnum<EMessageType>();
// ********** End Enum EMessageType ****************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS

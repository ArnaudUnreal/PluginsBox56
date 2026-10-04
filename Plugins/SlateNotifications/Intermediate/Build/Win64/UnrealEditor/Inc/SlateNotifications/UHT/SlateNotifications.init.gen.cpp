// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSlateNotifications_init() {}
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_SlateNotifications;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_SlateNotifications()
	{
		if (!Z_Registration_Info_UPackage__Script_SlateNotifications.OuterSingleton)
		{
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/SlateNotifications",
				nullptr,
				0,
				PKG_CompiledIn | 0x00000000,
				0xCE35D3F0,
				0xD5295E50,
				METADATA_PARAMS(0, nullptr)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_SlateNotifications.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_SlateNotifications.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_SlateNotifications(Z_Construct_UPackage__Script_SlateNotifications, TEXT("/Script/SlateNotifications"), Z_Registration_Info_UPackage__Script_SlateNotifications, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0xCE35D3F0, 0xD5295E50));
PRAGMA_ENABLE_DEPRECATION_WARNINGS

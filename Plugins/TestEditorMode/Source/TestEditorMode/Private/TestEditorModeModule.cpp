// Copyright Arnaud Szobad (Mecanode). All Rights Reserved.

#include "TestEditorModeModule.h"
#include "TestEdMode.h"

#include "EditorModeRegistry.h"

#define LOCTEXT_NAMESPACE "FTestEditorModeModule"

void FTestEditorModeModule::StartupModule()
{
	FEditorModeRegistry::Get().RegisterMode<FTestEdMode>(
		FTestEdMode::EM_TestEdModeId,
		LOCTEXT("TestEditorModeName", "My Placement"),
		FSlateIcon(),
		true
	);
}

void FTestEditorModeModule::ShutdownModule()
{
	if (FModuleManager::Get().IsModuleLoaded("UnrealEd"))
	{
		FEditorModeRegistry::Get().UnregisterMode(FTestEdMode::EM_TestEdModeId);
	}
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FTestEditorModeModule, TestEditorMode)
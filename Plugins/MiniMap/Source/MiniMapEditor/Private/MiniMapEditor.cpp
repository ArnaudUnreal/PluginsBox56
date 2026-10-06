// Copyright Arnaud Szobad (Mecanode). All Rights Reserved.

#include "MiniMapEditor.h"
#include "SMiniMapPanel.h"
#include "Framework/Application/SlateApplication.h"
#include "Framework/Docking/TabManager.h"
#include "Modules/ModuleManager.h"
#include "Styling/AppStyle.h"
#include "Widgets/Docking/SDockTab.h"
#include "WorkspaceMenuStructure.h"
#include "WorkspaceMenuStructureModule.h"

#define LOCTEXT_NAMESPACE "FEditorMiniMapModule"

static const FName MiniMapTabName("MiniMapTab");

void FMiniMapEditorModule::StartupModule()
{
	// Listed automatically in Window > Level Editor
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(
		MiniMapTabName,
		FOnSpawnTab::CreateLambda([](const FSpawnTabArgs&)
		{
			return SNew(SDockTab)
			.TabRole(ETabRole::NomadTab)
			[
				SNew(SMiniMapPanel)
			];
		})
	)
	.SetDisplayName(LOCTEXT("MiniMap", "Mini-Map"))
	.SetTooltipText(LOCTEXT("MiniMapTooltip", "Open the Mini-Map tab."))
	.SetGroup(WorkspaceMenu::GetMenuStructure().GetLevelEditorCategory())
	.SetIcon(FSlateIcon(FAppStyle::GetAppStyleSetName(), "LevelEditor.Tabs.Viewports"));
}

void FMiniMapEditorModule::ShutdownModule()
{
	if (FSlateApplication::IsInitialized())
	{
		FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(MiniMapTabName);
	}
}

#undef LOCTEXT_NAMESPACE
IMPLEMENT_MODULE(FMiniMapEditorModule, MiniMapEditor)

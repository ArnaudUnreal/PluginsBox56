// Copyright Arnaud Szobad (Mecanode). All Rights Reserved.

#include "GCBatchFractureModule.h"
#include "ContentBrowserMenuContexts.h"
#include "Engine/StaticMesh.h"
#include "Misc/MessageDialog.h"
#include "Styling/AppStyle.h"
#include "ToolMenus.h"

#include "GCBatchFractureService.h"

#define LOCTEXT_NAMESPACE "GCBatchFractureModule"

void FGCBatchFractureModule::StartupModule()
{
    UToolMenus::RegisterStartupCallback(
        FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FGCBatchFractureModule::RegisterMenus));
}

void FGCBatchFractureModule::ShutdownModule()
{
    UToolMenus::UnRegisterStartupCallback(this);
    UToolMenus::UnregisterOwner(this);
}

/*
 * Registers the plugin action in the Unreal Editor UI.
 *
 * This function adds a custom entry to the Content Browser context menu so the
 * user can right-click selected Static Meshes and launch the batch fracture tool.
 *
 * It is editor-only and should be registered during the module startup.
 */
void FGCBatchFractureModule::RegisterMenus()
{
    UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("ContentBrowser.AssetContextMenu.StaticMesh");
    FToolMenuSection& Section = Menu->FindOrAddSection("GetAssetActions");
    AddMenuEntry(Section);
}

void FGCBatchFractureModule::AddMenuEntry(FToolMenuSection& Section)
{
    Section.AddDynamicEntry(
        "GCBatchFracture_Run",
        FNewToolMenuSectionDelegate::CreateLambda([](FToolMenuSection& InSection)
        {
            UContentBrowserAssetContextMenuContext* Context = InSection.FindContext<UContentBrowserAssetContextMenuContext>();
            if (!Context)
            {
                return;
            }

            // Only asset data here: assets are loaded when the action runs, not on right-click.
            const TArray<FAssetData> SelectedAssets = Context->SelectedAssets;
            if (SelectedAssets.IsEmpty())
            {
                return;
            }

            InSection.AddMenuEntry(
                "GCBatchFracture_RunEntry",
                LOCTEXT("RunBatchFractureLabel", "Batch Chaos Fracture ..."),
                LOCTEXT("RunBatchFractureTooltip", "Create Geometry Collections in a GC subfolder, apply the same default fracture settings, and save them asset by asset."),
                FSlateIcon(FAppStyle::GetAppStyleSetName(), "ClassIcon.StaticMesh"),
                FUIAction(FExecuteAction::CreateLambda([SelectedAssets]()
                {
                    TArray<UStaticMesh*> StaticMeshes;
                    StaticMeshes.Reserve(SelectedAssets.Num());

                    for (const FAssetData& AssetData : SelectedAssets)
                    {
                        if (!AssetData.IsInstanceOf(UStaticMesh::StaticClass()))
                        {
                            continue;
                        }

                        if (UStaticMesh* StaticMesh = Cast<UStaticMesh>(AssetData.GetAsset()))
                        {
                            StaticMeshes.AddUnique(StaticMesh);
                        }
                    }
                    FGCBatchFractureService::OpenOptionsDialogAndRun(StaticMeshes);
                })));
        }));
}

void FGCBatchFractureModule::ExecuteOnSelectedStaticMeshes()
{
    // Not used in this version. We execute directly from the tool menu lambda.
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FGCBatchFractureModule, GCBatchFracture)

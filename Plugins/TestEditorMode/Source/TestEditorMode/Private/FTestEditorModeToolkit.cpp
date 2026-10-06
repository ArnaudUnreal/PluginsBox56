// Copyright Arnaud Szobad (Mecanode). All Rights Reserved.

#include "TestEditorMode/Public/FTestEditorModeToolkit.h"
#include "TestEdMode.h"

#include "EditorModeManager.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/Layout/SExpandableArea.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Input/SButton.h"

void FTestEditorModeToolkit::Init(const TSharedPtr<IToolkitHost>& InitToolkitHost)
{
    ToolkitWidget =
        SNew(SScrollBox)

        + SScrollBox::Slot()
        [
            SNew(SVerticalBox)

            + SVerticalBox::Slot()
            .AutoHeight()
            .Padding(4.0f)
            [
                SNew(SExpandableArea)
                .InitiallyCollapsed(false)
                .AreaTitle(FText::FromString("Catégorie A"))
                .BodyContent()
                [
                    SNew(SVerticalBox)
                    + SVerticalBox::Slot().AutoHeight().Padding(2.0f)
                    [
                        MakeMeshButton(FText::FromString("Bouton A1"), TEXT("/Game/EditorMeshes/SM_A1.SM_A1"))
                    ]
                    + SVerticalBox::Slot().AutoHeight().Padding(2.0f)
                    [
                        MakeMeshButton(FText::FromString("Bouton A2"), TEXT("/Game/EditorMeshes/SM_A2.SM_A2"))
                    ]
                    + SVerticalBox::Slot().AutoHeight().Padding(2.0f)
                    [
                        MakeMeshButton(FText::FromString("Bouton A3"), TEXT("/Game/EditorMeshes/SM_A3.SM_A3"))
                    ]
                ]
            ]

            + SVerticalBox::Slot()
            .AutoHeight()
            .Padding(4.0f)
            [
                SNew(SExpandableArea)
                .InitiallyCollapsed(false)
                .AreaTitle(FText::FromString("Catégorie B"))
                .BodyContent()
                [
                    SNew(SVerticalBox)
                    + SVerticalBox::Slot().AutoHeight().Padding(2.0f)
                    [
                        MakeMeshButton(FText::FromString("Bouton B1"), TEXT("/Game/EditorMeshes/SM_B1.SM_B1"))
                    ]
                    + SVerticalBox::Slot().AutoHeight().Padding(2.0f)
                    [
                        MakeMeshButton(FText::FromString("Bouton B2"), TEXT("/Game/EditorMeshes/SM_B2.SM_B2"))
                    ]
                    + SVerticalBox::Slot().AutoHeight().Padding(2.0f)
                    [
                        MakeMeshButton(FText::FromString("Bouton B3"), TEXT("/Game/EditorMeshes/SM_B3.SM_B3"))
                    ]
                ]
            ]
        ];

    FModeToolkit::Init(InitToolkitHost);
}

TSharedRef<SWidget> FTestEditorModeToolkit::MakeMeshButton(const FText& Label, const FString& MeshPath)
{
    return SNew(SButton)
        .Text(Label)
        .OnClicked(FOnClicked::CreateSP(this, &FTestEditorModeToolkit::OnPlaceMesh, MeshPath));
}

FEdMode* FTestEditorModeToolkit::GetEditorMode() const
{
    return GLevelEditorModeTools().GetActiveMode(FTestEdMode::EM_TestEdModeId);
}

FReply FTestEditorModeToolkit::OnPlaceMesh(FString MeshPath)
{
    if (FTestEdMode* Mode = static_cast<FTestEdMode*>(GetEditorMode()))
    {
        Mode->PlaceMeshFromPath(MeshPath);
    }

    return FReply::Handled();
}
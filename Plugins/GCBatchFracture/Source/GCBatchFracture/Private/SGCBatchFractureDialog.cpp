// Copyright Arnaud Szobad 2026 All Rights Reserved.

#include "SGCBatchFractureDialog.h"
#include "GCBatchFractureSettings.h"
#include "Styling/AppStyle.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Input/SCheckBox.h"
#include "Widgets/Input/SComboBox.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SSeparator.h"
#include "Widgets/Layout/SUniformGridPanel.h"
#include "Widgets/SWindow.h"
#include "Widgets/Text/STextBlock.h"

#define LOCTEXT_NAMESPACE "SGCBatchFractureDialog"

static FText PresetToText(const EGCBatchFracturePreset Preset)
{
	switch (Preset)
	{
	case EGCBatchFracturePreset::FastPreview:
		return LOCTEXT("Preset_FastPreview", "Fast Preview");

	case EGCBatchFracturePreset::Balanced:
		return LOCTEXT("Preset_Balanced", "Balanced");

	case EGCBatchFracturePreset::RuntimeSafe:
		return LOCTEXT("Preset_RuntimeSafe", "Runtime Safe");

	case EGCBatchFracturePreset::Custom:
	default:
		return LOCTEXT("Preset_Custom", "Custom");
	}
}

static FText PresetToDescription(const EGCBatchFracturePreset Preset)
{
	switch (Preset)
	{
	case EGCBatchFracturePreset::FastPreview:
		return LOCTEXT(
			"PresetDesc_FastPreview",
			"Fast generation for previewing many assets. Uses fewer runtime safety steps.");

	case EGCBatchFracturePreset::Balanced:
		return LOCTEXT(
			"PresetDesc_Balanced",
			"Recommended default. Good balance between generation time, fracture detail and runtime collision.");

	case EGCBatchFracturePreset::RuntimeSafe:
		return LOCTEXT(
			"PresetDesc_RuntimeSafe",
			"Runtime Safe uses more conservative settings for Chaos runtime simulation. It can be significantly slower on complex meshes or multi-level fractures.");

	case EGCBatchFracturePreset::Custom:
	default:
		return LOCTEXT(
			"PresetDesc_Custom",
			"Uses the values currently set in Project Settings. Editing advanced settings switches the preset to Custom.");
	}
}

void SGCBatchFractureDialog::Construct(const FArguments& InArgs)
{
	SelectedAssetCount = InArgs._SelectedAssetCount;
	ParentWindow = InArgs._ParentWindow;
	OnConfirmed = InArgs._OnConfirmed;

	const UGCBatchFractureSettings* Settings = GetMutableDefault<UGCBatchFractureSettings>();
	
	const EGCBatchFracturePreset CurrentPreset = Settings
		? Settings->Preset
		: EGCBatchFracturePreset::Balanced;

	bSkipExistingAssets = Settings
		? Settings->bSkipExistingAssets
		: true;

	bNonOverlappingConvexHullsEnabled = Settings
		? Settings->bCreateNonOverlappingConvexHulls
		: false;

	PresetOptions.Add(MakeShared<EGCBatchFracturePreset>(EGCBatchFracturePreset::FastPreview));
	PresetOptions.Add(MakeShared<EGCBatchFracturePreset>(EGCBatchFracturePreset::Balanced));
	PresetOptions.Add(MakeShared<EGCBatchFracturePreset>(EGCBatchFracturePreset::RuntimeSafe));
	PresetOptions.Add(MakeShared<EGCBatchFracturePreset>(EGCBatchFracturePreset::Custom));

	for (const TSharedPtr<EGCBatchFracturePreset>& PresetOption : PresetOptions)
	{
		if (PresetOption.IsValid() && *PresetOption == CurrentPreset)
		{
			CurrentPresetOption = PresetOption;
			break;
		}
	}

	if (!CurrentPresetOption.IsValid())
	{
		CurrentPresetOption = PresetOptions[1];
	}

	ChildSlot
	[
		SNew(SBorder)
		.Padding(16.0f)
		.BorderImage(FAppStyle::GetBrush("ToolPanel.GroupBorder"))
		[
			SNew(SVerticalBox)

			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(STextBlock)
				.Text(LOCTEXT("DialogTitle", "GC Batch Fracture"))
				.Font(FAppStyle::GetFontStyle("HeadingMedium"))
			]

			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0.0f, 8.0f, 0.0f, 12.0f)
			[
				SNew(STextBlock)
				.Text(FText::Format(
					LOCTEXT("SelectedAssetsText", "{0} Static Mesh asset(s) selected."),
					FText::AsNumber(SelectedAssetCount)))
			]

			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SSeparator)
			]

			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0.0f, 12.0f, 0.0f, 4.0f)
			[
				SNew(STextBlock)
				.Text(LOCTEXT("PresetLabel", "Preset"))
				.Font(FAppStyle::GetFontStyle("PropertyWindow.BoldFont"))
			]

			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SComboBox<TSharedPtr<EGCBatchFracturePreset>>)
				.OptionsSource(&PresetOptions)
				.InitiallySelectedItem(CurrentPresetOption)
				.OnGenerateWidget(this, &SGCBatchFractureDialog::GeneratePresetComboWidget)
				.OnSelectionChanged(this, &SGCBatchFractureDialog::OnPresetChanged)
				[
					SNew(STextBlock)
					.Text(this, &SGCBatchFractureDialog::GetCurrentPresetText)
				]
			]

			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0.0f, 6.0f, 0.0f, 12.0f)
			[
				SNew(STextBlock)
				.Text(this, &SGCBatchFractureDialog::GetCurrentPresetDescription)
				.AutoWrapText(true)
				.ColorAndOpacity(FSlateColor::UseSubduedForeground())
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0.0f, 4.0f, 0.0f, 12.0f)
			[
				SNew(STextBlock)
				.Text(this, &SGCBatchFractureDialog::GetAdvancedWarningText)
				.Visibility(this, &SGCBatchFractureDialog::GetAdvancedWarningVisibility)
				.AutoWrapText(true)
				.ColorAndOpacity(FSlateColor(FLinearColor(1.0f, 0.65f, 0.1f)))
			]

			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SSeparator)
			]

			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0.0f, 12.0f, 0.0f, 0.0f)
			[
				SNew(SCheckBox)
				.IsChecked(this, &SGCBatchFractureDialog::GetSkipExistingCheckState)
				.OnCheckStateChanged(this, &SGCBatchFractureDialog::OnSkipExistingChanged)
				[
					SNew(STextBlock)
					.Text(LOCTEXT("SkipExistingLabel", "Skip existing Geometry Collection assets"))
				]
			]

			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(0.0f, 6.0f, 0.0f, 12.0f)
			[
				SNew(STextBlock)
				.Text(LOCTEXT(
					"SkipExistingDescription",
					"Recommended. When enabled, existing Geometry Collections are skipped. When disabled, new unique names are generated instead of overwriting existing assets."))
				.AutoWrapText(true)
				.ColorAndOpacity(FSlateColor::UseSubduedForeground())
			]

			+ SVerticalBox::Slot()
			.FillHeight(1.0f)
			[
				SNullWidget::NullWidget
			]

			+ SVerticalBox::Slot()
			.AutoHeight()
			.HAlign(HAlign_Right)
			[
				SNew(SUniformGridPanel)
				.SlotPadding(FMargin(4.0f, 0.0f))

				+ SUniformGridPanel::Slot(0, 0)
				[
					SNew(SButton)
					.Text(LOCTEXT("CancelButton", "Cancel"))
					.HAlign(HAlign_Center)
					.OnClicked(this, &SGCBatchFractureDialog::OnCancelClicked)
				]

				+ SUniformGridPanel::Slot(1, 0)
				[
					SNew(SButton)
					.Text(LOCTEXT("CreateButton", "Create Geometry Collections"))
					.HAlign(HAlign_Center)
					.ButtonStyle(FAppStyle::Get(), "PrimaryButton")
					.OnClicked(this, &SGCBatchFractureDialog::OnCreateClicked)
				]
			]
		]
	];
}

bool SGCBatchFractureDialog::IsNonOverlappingConvexHullEnabledInSettings() const
{
	// Every non-Custom preset disables non-overlapping hulls when applied on Create,
	// so the Project Settings value only matters for the Custom preset.
	return bNonOverlappingConvexHullsEnabled &&
		CurrentPresetOption.IsValid() &&
		*CurrentPresetOption == EGCBatchFracturePreset::Custom;
}

EVisibility SGCBatchFractureDialog::GetAdvancedWarningVisibility() const
{
	if (IsNonOverlappingConvexHullEnabledInSettings())
	{
		return EVisibility::Visible;
	}

	if (CurrentPresetOption.IsValid() &&
		*CurrentPresetOption == EGCBatchFracturePreset::RuntimeSafe)
	{
		return EVisibility::Visible;
	}

	return EVisibility::Collapsed;
}

FText SGCBatchFractureDialog::GetAdvancedWarningText() const
{
	if (IsNonOverlappingConvexHullEnabledInSettings())
	{
		return LOCTEXT(
			"NonOverlapWarning",
			"Warning: non-overlapping convex hull generation is enabled in Project Settings. This can significantly increase generation time and should be considered experimental.");
	}

	if (CurrentPresetOption.IsValid() &&
		*CurrentPresetOption == EGCBatchFracturePreset::RuntimeSafe)
	{
		return LOCTEXT(
			"RuntimeSafeWarning",
			"Runtime Safe may be significantly slower on complex meshes or large batches.");
	}

	return FText::GetEmpty();
}

TSharedRef<SWidget> SGCBatchFractureDialog::GeneratePresetComboWidget(
	TSharedPtr<EGCBatchFracturePreset> InPreset) const
{
	return SNew(STextBlock)
		.Text(InPreset.IsValid()
			? PresetToText(*InPreset)
			: LOCTEXT("InvalidPreset", "Invalid"));
}

void SGCBatchFractureDialog::OnPresetChanged(
	TSharedPtr<EGCBatchFracturePreset> NewPreset,
	ESelectInfo::Type SelectInfo)
{
	if (NewPreset.IsValid())
	{
		CurrentPresetOption = NewPreset;
	}
}

FText SGCBatchFractureDialog::GetCurrentPresetText() const
{
	return CurrentPresetOption.IsValid()
		? PresetToText(*CurrentPresetOption)
		: LOCTEXT("NoPreset", "No Preset");
}

FText SGCBatchFractureDialog::GetCurrentPresetDescription() const
{
	return CurrentPresetOption.IsValid()
		? PresetToDescription(*CurrentPresetOption)
		: FText::GetEmpty();
}

ECheckBoxState SGCBatchFractureDialog::GetSkipExistingCheckState() const
{
	return bSkipExistingAssets
		? ECheckBoxState::Checked
		: ECheckBoxState::Unchecked;
}

void SGCBatchFractureDialog::OnSkipExistingChanged(const ECheckBoxState NewState)
{
	bSkipExistingAssets = NewState == ECheckBoxState::Checked;
}

FReply SGCBatchFractureDialog::OnCreateClicked()
{
	UGCBatchFractureSettings* Settings = GetMutableDefault<UGCBatchFractureSettings>();

	if (Settings && CurrentPresetOption.IsValid())
	{
		Settings->Modify();

		Settings->Preset = *CurrentPresetOption;

		if (Settings->Preset != EGCBatchFracturePreset::Custom)
		{
			Settings->ApplyPresetToSettings();
		}

		Settings->bSkipExistingAssets = bSkipExistingAssets;

		Settings->SaveConfig();
	}

	if (const TSharedPtr<SWindow> Window = ParentWindow.Pin())
	{
		Window->RequestDestroyWindow();
	}

	OnConfirmed.ExecuteIfBound();

	return FReply::Handled();
}

FReply SGCBatchFractureDialog::OnCancelClicked()
{
	if (const TSharedPtr<SWindow> Window = ParentWindow.Pin())
	{
		Window->RequestDestroyWindow();
	}

	return FReply::Handled();
}

bool SGCBatchFractureDialog::IsRuntimeSafePresetSelected() const
{
	return CurrentPresetOption.IsValid() &&
		*CurrentPresetOption == EGCBatchFracturePreset::RuntimeSafe;
}


#undef LOCTEXT_NAMESPACE
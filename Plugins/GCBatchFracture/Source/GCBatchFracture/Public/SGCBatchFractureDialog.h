// Copyright Arnaud Szobad (Mecanode). All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class SWindow;

enum class EGCBatchFracturePreset : uint8;

/**
 * Dialog displayed before running the batch fracture operation.
 *
 * It lets the user choose a preset and a few common batch options without having
 * to open the Project Settings panel manually.
 */
class SGCBatchFractureDialog : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SGCBatchFractureDialog) {}
		SLATE_ARGUMENT(int32, SelectedAssetCount)
		SLATE_ARGUMENT(TSharedPtr<SWindow>, ParentWindow)
		SLATE_EVENT(FSimpleDelegate, OnConfirmed)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

private:
	TSharedRef<SWidget> GeneratePresetComboWidget(TSharedPtr<EGCBatchFracturePreset> InPreset) const;

	void OnPresetChanged(TSharedPtr<EGCBatchFracturePreset> NewPreset, ESelectInfo::Type SelectInfo);

	FText GetCurrentPresetText() const;
	FText GetCurrentPresetDescription() const;

	ECheckBoxState GetSkipExistingCheckState() const;
	void OnSkipExistingChanged(ECheckBoxState NewState);

	FReply OnCreateClicked();
	FReply OnCancelClicked();
	
	EVisibility GetAdvancedWarningVisibility() const;
	FText GetAdvancedWarningText() const;
	
	int32 SelectedAssetCount = 0;

	TWeakPtr<SWindow> ParentWindow;
	FSimpleDelegate OnConfirmed;

	TArray<TSharedPtr<EGCBatchFracturePreset>> PresetOptions;
	TSharedPtr<EGCBatchFracturePreset> CurrentPresetOption;

	bool IsRuntimeSafePresetSelected() const;
	bool IsNonOverlappingConvexHullEnabledInSettings() const;
	
	bool bSkipExistingAssets = true;
	bool bNonOverlappingConvexHullsEnabled = false;
};
#include "SMiniMapPanel.h"
#include "SMiniMapViewport.h"
#include "Styling/AppStyle.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Input/SCheckBox.h"
#include "Widgets/Input/SSearchBox.h"
#include "Widgets/Text/STextBlock.h"

#define LOCTEXT_NAMESPACE "SMiniMapPanel"

void SMiniMapPanel::Construct(const FArguments& InArgs)
{
	auto MakeToggle = [](const FText& Label, const FText& Tooltip,
		TFunction<bool()> Getter, TFunction<void(bool)> Setter, TAttribute<bool> IsEnabled = true)
	{
		return SNew(SCheckBox)
			.ToolTipText(Tooltip)
			.IsEnabled(IsEnabled)
			.IsChecked_Lambda([Getter]() { return Getter() ? ECheckBoxState::Checked : ECheckBoxState::Unchecked; })
			.OnCheckStateChanged_Lambda([Setter](ECheckBoxState State) { Setter(State == ECheckBoxState::Checked); })
			[
				SNew(STextBlock).Text(Label)
			];
	};

	ChildSlot
	[
		SNew(SVerticalBox)

		// Toolbar
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(4.f, 4.f)
		[
			SNew(SHorizontalBox)

			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			.Padding(0.f, 0.f, 6.f, 0.f)
			[
				SNew(SButton)
				.Text(LOCTEXT("Fit", "Fit"))
				.ToolTipText(LOCTEXT("FitTooltip", "Recompute the level bounds and reset pan/zoom."))
				.OnClicked_Lambda([this]() { Viewport->FitToLevel(); return FReply::Handled(); })
			]

			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			.Padding(0.f, 0.f, 10.f, 0.f)
			[
				MakeToggle(LOCTEXT("AllActors", "All actors"),
					LOCTEXT("AllActorsTooltip", "Show every actor of the level. Uncheck to use the filter."),
					[this]() { return Viewport->GetShowAllActors(); },
					[this](bool b) { Viewport->SetShowAllActors(b); })
			]

			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			.Padding(0.f, 0.f, 6.f, 0.f)
			[
				SNew(SButton)
				.Text(LOCTEXT("Capture", "Capture"))
				.ToolTipText(LOCTEXT("CaptureTooltip", "Render a top-down view of the level as map background (loaded areas only)."))
				.OnClicked_Lambda([this]() { Viewport->CaptureBackground(); return FReply::Handled(); })
			]

			+ SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			.Padding(0.f, 0.f, 10.f, 0.f)
			[
				MakeToggle(LOCTEXT("Background", "Background"),
					LOCTEXT("BackgroundTooltip", "Show the captured background image."),
					[this]() { return Viewport->GetShowBackground(); },
					[this](bool b) { Viewport->SetShowBackground(b); },
					TAttribute<bool>::CreateLambda([this]() { return Viewport->HasBackground(); }))
			]

			+ SHorizontalBox::Slot()
			.FillWidth(1.f)
			.VAlign(VAlign_Center)
			[
				SNew(SSearchBox)
				.HintText(LOCTEXT("FilterHint", "Filter actors (class or label)"))
				.ToolTipText(LOCTEXT("FilterTooltip", "Show only actors whose class or label contains the text. Available when 'All actors' is unchecked."))
				.IsEnabled_Lambda([this]() { return !Viewport->GetShowAllActors(); })
				.OnTextChanged_Lambda([this](const FText& Text) { Viewport->SetFilterText(Text.ToString()); })
			]
		]

		// Map
		+ SVerticalBox::Slot()
		.FillHeight(1.f)
		[
			SAssignNew(Viewport, SMiniMapViewport)
		]

		// Controls reminder
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(4.f, 2.f)
		[
			SNew(STextBlock)
			.Font(FAppStyle::GetFontStyle("SmallFont"))
			.ColorAndOpacity(FSlateColor::UseSubduedForeground())
			.Text(LOCTEXT("Help", "LMB: select actor / move camera   Ctrl+LMB: toggle selection   Double-click: focus   RMB drag: pan   Wheel: zoom"))
		]
	];
}

#undef LOCTEXT_NAMESPACE

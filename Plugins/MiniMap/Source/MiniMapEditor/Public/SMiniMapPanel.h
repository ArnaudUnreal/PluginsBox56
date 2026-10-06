// Copyright Arnaud Szobad (Mecanode). All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class SMiniMapViewport;

/**
 * Mini-map tab content: toolbar (fit, display toggles, background capture, actor filter)
 * on top of the SMiniMapViewport, with a short controls reminder below.
 */
class SMiniMapPanel : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SMiniMapPanel) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

private:
	TSharedPtr<SMiniMapViewport> Viewport;
};

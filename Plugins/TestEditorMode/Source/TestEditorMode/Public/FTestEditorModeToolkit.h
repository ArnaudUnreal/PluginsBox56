#pragma once

#include "Toolkits/BaseToolkit.h"

class FTestEditorModeToolkit : public FModeToolkit
{
public:
	virtual void Init(const TSharedPtr<IToolkitHost>& InitToolkitHost) override;

	virtual FName GetToolkitFName() const override
	{
		return FName("TestEditorModeToolkit");
	}

	virtual FText GetBaseToolkitName() const override
	{
		return FText::FromString("My Placement Mode");
	}

	virtual TSharedPtr<SWidget> GetInlineContent() const override
	{
		return ToolkitWidget;
	}

	virtual class FEdMode* GetEditorMode() const override;

private:
	TSharedPtr<SWidget> ToolkitWidget;

	TSharedRef<SWidget> MakeMeshButton(const FText& Label, const FString& MeshPath);
	FReply OnPlaceMesh(FString MeshPath);
};
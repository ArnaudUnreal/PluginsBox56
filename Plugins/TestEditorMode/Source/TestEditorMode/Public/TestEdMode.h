#pragma once

#include "EdMode.h"

class FTestEditorModeToolkit;

class FTestEdMode : public FEdMode
{
public:
	static const FEditorModeID EM_TestEdModeId;

	FTestEdMode();
	virtual ~FTestEdMode() override;

	virtual void Enter() override;
	virtual void Exit() override;
	virtual bool UsesToolkits() const override { return true; }

	void PlaceMeshFromPath(const FString& MeshPath);

private:
	bool ConfirmPlacement(const FString& AssetName) const;
	void GetSpawnTransformFromViewport(FVector& OutLocation, FRotator& OutRotation) const;
};
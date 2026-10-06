// Copyright Arnaud Szobad (Mecanode). All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ComponentVisualizer.h"


class PATROLPATHEDITOR_API FPatrolPathVisualizer : public FComponentVisualizer
{
public:                                                   
	virtual void DrawVisualization(const UActorComponent* Component, 
		const FSceneView* View, 
		FPrimitiveDrawInterface* PDI) override;
	
	virtual bool VisProxyHandleClick(FEditorViewportClient* inViewportClient, 
		HComponentVisProxy* VisProxy, const FViewportClick& Click) override;
	
	virtual UActorComponent* GetEditedComponent() const override;
	virtual void EndEditing() override;
	virtual bool GetWidgetLocation(const FEditorViewportClient* ViewportClient, FVector& OutLocation) const override;
	virtual bool HandleInputDelta(FEditorViewportClient* ViewportClient, FViewport* Viewport,
		FVector& DeltaTranslate, FRotator& DeltaRotate, FVector& DeltaScale ) override;
	
	
	TWeakObjectPtr<class UPatrolPathComponent> EditedComponent;
	int32 SelectedIndex = INDEX_NONE;
};
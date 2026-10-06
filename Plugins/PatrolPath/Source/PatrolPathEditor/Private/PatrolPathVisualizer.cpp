// Copyright Arnaud Szobad (Mecanode). All Rights Reserved.

#include "PatrolPathVisualizer.h"

#include "HPatrolPointProxy.h"
#include "PatrolPath/Public/PatrolPathComponent.h"

#define LOCTEXT_NAMESPACE "PatrolPathVisualizer"

void FPatrolPathVisualizer::DrawVisualization(const UActorComponent* Component, const FSceneView* View,
	FPrimitiveDrawInterface* PDI)
{
	const UPatrolPathComponent* Path = Cast<const UPatrolPathComponent>(Component);
	if (!Path) return;
	FLinearColor Color = FLinearColor::Green;
	int32 i = 0;	
	float Size = 12;
	while (i < Path->GetPointCount())
	{
		FVector P = Path->GetWorldPoint(i);
		// ajout
		Color = FLinearColor::Green;
		if (Path == EditedComponent.Get() && i == SelectedIndex)
		{
			Color = FLinearColor(1, 0.5, 0);
		}
		PDI->SetHitProxy(new HPatrolPointProxy(Path, i));
		PDI->DrawPoint(P, Color, Size, SDPG_Foreground);
		// ERREUR : Si omis, un clic sur un segment sélectionne le dernier point dessiné
		PDI->SetHitProxy(nullptr);
		int32 next = Path->GetNextPointIndex(i);
		if (next != INDEX_NONE)
		{
			PDI->DrawLine(P, Path->GetWorldPoint(next),FLinearColor::Green, SDPG_Foreground);
		}
		i++;
	}
}

bool FPatrolPathVisualizer::VisProxyHandleClick(FEditorViewportClient* inViewportClient, HComponentVisProxy* VisProxy,
	const FViewportClick& Click)
{
	HPatrolPointProxy* Proxy = HitProxyCast<HPatrolPointProxy>(VisProxy);
	if (!Proxy) return false;
	
	UActorComponent* Clicked = const_cast<UActorComponent*>(Proxy->Component.Get());
	EditedComponent = Cast<UPatrolPathComponent>(Clicked);
	SelectedIndex = Proxy->PointIndex;
	return true;
}

UActorComponent* FPatrolPathVisualizer::GetEditedComponent() const
{
	return EditedComponent.Get();
}

void FPatrolPathVisualizer::EndEditing()
{
	EditedComponent.Reset();
	SelectedIndex = INDEX_NONE;
}

#undef LOCTEXT_NAMESPACE

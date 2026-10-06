// Copyright Arnaud Szobad (Mecanode). All Rights Reserved.

#include "PatrolPathVisualizer.h"

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
		PDI->DrawPoint(P, Color, Size, SDPG_Foreground);
		int32 next = Path->GetNextPointIndex(i);
		if (next != INDEX_NONE)
		{
			PDI->DrawLine(P, Path->GetWorldPoint(next),Color, SDPG_Foreground);
		}
		i++;
	}
}

#undef LOCTEXT_NAMESPACE

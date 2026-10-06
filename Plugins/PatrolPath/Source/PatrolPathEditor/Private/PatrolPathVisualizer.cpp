// Copyright Arnaud Szobad (Mecanode). All Rights Reserved.

#include "PatrolPathVisualizer.h"

#include "HPatrolPointProxy.h"
#include "PatrolPathSettings.h"
#include "PatrolPath/Public/PatrolPathComponent.h"

#define LOCTEXT_NAMESPACE "PatrolPathVisualizer"

void FPatrolPathVisualizer::DrawVisualization(const UActorComponent* Component, const FSceneView* View,
	FPrimitiveDrawInterface* PDI)
{
	const UPatrolPathComponent* Path = Cast<const UPatrolPathComponent>(Component);
	const UPatrolPathSettings* Settings = GetDefault<UPatrolPathSettings>();
	if (!Path) return;
	FColor Color = Settings->PointColor;
	int32 i = 0;	
	float Size = Settings->PointSize;
	while (i < Path->GetPointCount())
	{
		FVector P = Path->GetWorldPoint(i);
		// ajout
		Color = Settings->PointColor;
		if (Path == EditedComponent.Get() && i == SelectedIndex)
		{
			Color = Settings->SelectedPointColor;
		}
		PDI->SetHitProxy(new HPatrolPointProxy(Path, i));
		PDI->DrawPoint(P, Color, Size, SDPG_Foreground);
		// ERREUR : Si omis, un clic sur un segment sélectionne le dernier point dessiné
		PDI->SetHitProxy(nullptr);
		int32 next = Path->GetNextPointIndex(i);
		if (next != INDEX_NONE)
		{
			PDI->DrawLine(P, Path->GetWorldPoint(next),Settings->PointColor, SDPG_Foreground);
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

bool FPatrolPathVisualizer::GetWidgetLocation(const FEditorViewportClient* ViewportClient, FVector& OutLocation) const
{
	UPatrolPathComponent* Path = EditedComponent.Get();
	if (Path && Path->Points.IsValidIndex(SelectedIndex))
	{
		OutLocation = Path->GetWorldPoint(SelectedIndex);
		return true;
	}
	return false;
}

bool FPatrolPathVisualizer::HandleInputDelta(FEditorViewportClient* ViewportClient, FViewport* Viewport,
	FVector& DeltaTranslate, FRotator& DeltaRotate, FVector& DeltaScale)
{
	UPatrolPathComponent* Path = EditedComponent.Get();
	if (!Path || !Path->Points.IsValidIndex(SelectedIndex)) return false;
	if (DeltaTranslate.IsZero()) return true;
	
	FScopedTransaction Transaction(LOCTEXT("MovePatrolPoint", "Move Patrol Point")); 
	// ERREUR - sans le modify, pas de ctrl-Z
	Path->Modify();
	
	// ERREUR : passage du Delta en World
	// Path->Points[SelectedIndex] = Path->Points[SelectedIndex] + DeltaTranslate;
	// CORRECTION
	FVector LocalDelta = Path->GetComponentTransform().InverseTransformVector(DeltaTranslate);
	Path->Points[SelectedIndex] = Path->Points[SelectedIndex] + LocalDelta;
	
	FProperty* PointsProperty = FindFProperty<FProperty>(UPatrolPathComponent::StaticClass(),
		GET_MEMBER_NAME_CHECKED(UPatrolPathComponent, Points));
	NotifyPropertyModified(Path, PointsProperty);
	return true;
}

#undef LOCTEXT_NAMESPACE
// Copyright Arnaud Szobad (Mecanode). All Rights Reserved.

#include "PatrolPathVisualizer.h"
#include "HPatrolPointProxy.h"
#include "HPatrolSegmentProxy.h"
#include "PatrolPathSettings.h"
#include "PatrolPath/Public/PatrolPathComponent.h"
#include "SceneManagement.h"
#include "ScopedTransaction.h"

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
		Color = Settings->PointColor;
		if (Path == EditedComponent.Get() && i == SelectedPointIndex)
		{
			Color = Settings->SelectedPointColor;
		}
		PDI->SetHitProxy(new HPatrolPointProxy(Path, i));
		PDI->DrawPoint(P, Color, Size, SDPG_Foreground);
		PDI->SetHitProxy(nullptr);
		int32 next = Path->GetNextPointIndex(i);
		if (next != INDEX_NONE)
		{
			PDI->SetHitProxy(new HPatrolSegmentProxy(Path, i));
			PDI->DrawLine(P, Path->GetWorldPoint(next),Settings->PointColor, SDPG_Foreground, Settings->LineWidth);
			PDI->SetHitProxy(nullptr);
		}
		i++;
	}
}

bool FPatrolPathVisualizer::VisProxyHandleClick(FEditorViewportClient* inViewportClient, HComponentVisProxy* VisProxy,
	const FViewportClick& Click)
{
	if (HPatrolPointProxy* PointProxy = HitProxyCast<HPatrolPointProxy>(VisProxy))
	{
		UActorComponent* Clicked = const_cast<UActorComponent*>(PointProxy->Component.Get());
		EditedComponent = Cast<UPatrolPathComponent>(Clicked);
		SelectedPointIndex = PointProxy->PointIndex;
		SelectedSegmentIndex = INDEX_NONE;
		PendingInsertIndex = INDEX_NONE;
		return true;
	}
	
	if (HPatrolSegmentProxy* SegmentProxy = HitProxyCast<HPatrolSegmentProxy>(VisProxy))
	{
		UActorComponent* Clicked = const_cast<UActorComponent*>(SegmentProxy->Component.Get());
		EditedComponent = Cast<UPatrolPathComponent>(Clicked);
		if (!EditedComponent.IsValid()) return false;
		SelectedSegmentIndex = SegmentProxy->SegmentStartIndex;
		
		FVector Trace = Click.GetOrigin() + Click.GetDirection() * HALF_WORLD_MAX;
		FVector Start = EditedComponent->GetWorldPoint(SelectedSegmentIndex);
		FVector End = EditedComponent->GetWorldPoint(EditedComponent->GetNextPointIndex(SelectedSegmentIndex));
		FVector PointOnTrace = FVector();
		FVector PointOnPath = FVector();
		FMath::SegmentDistToSegmentSafe(Click.GetOrigin(), Trace, Start, End, PointOnTrace, PointOnPath);
		
		PendingInsertLocation = EditedComponent->GetComponentTransform().InverseTransformPosition(PointOnPath);
		PendingInsertIndex = SelectedSegmentIndex;
		SelectedPointIndex = INDEX_NONE;
		return true;		
	}
	return false;
}

UActorComponent* FPatrolPathVisualizer::GetEditedComponent() const
{
	return EditedComponent.Get();
}

void FPatrolPathVisualizer::EndEditing()
{
	EditedComponent.Reset();
	SelectedPointIndex = INDEX_NONE;
	SelectedSegmentIndex = INDEX_NONE;
	PendingInsertIndex = INDEX_NONE;
}

bool FPatrolPathVisualizer::GetWidgetLocation(const FEditorViewportClient* ViewportClient, FVector& OutLocation) const
{
	UPatrolPathComponent* Path = EditedComponent.Get();
	if (Path && Path->Points.IsValidIndex(SelectedPointIndex))
	{
		OutLocation = Path->GetWorldPoint(SelectedPointIndex);
		return true;
	}
	return false;
}

bool FPatrolPathVisualizer::HandleInputDelta(FEditorViewportClient* ViewportClient, FViewport* Viewport,
	FVector& DeltaTranslate, FRotator& DeltaRotate, FVector& DeltaScale)
{
	UPatrolPathComponent* Path = EditedComponent.Get();
	if (!Path || !Path->Points.IsValidIndex(SelectedPointIndex)) return false;
	if (DeltaTranslate.IsZero()) return true;
	
	FScopedTransaction Transaction(LOCTEXT("MovePatrolPoint", "Move Patrol Point")); 
	// ERREUR - sans le modify, pas de ctrl-Z
	Path->Modify();
	
	// ERREUR : passage du Delta en World
	// Path->Points[SelectedPointIndex] = Path->Points[SelectedPointIndex] + DeltaTranslate;
	// CORRECTION
	FVector LocalDelta = Path->GetComponentTransform().InverseTransformVector(DeltaTranslate);
	Path->Points[SelectedPointIndex] = Path->Points[SelectedPointIndex] + LocalDelta;
	
	FProperty* PointsProperty = FindFProperty<FProperty>(UPatrolPathComponent::StaticClass(),
		GET_MEMBER_NAME_CHECKED(UPatrolPathComponent, Points));
	NotifyPropertyModified(Path, PointsProperty);
	return true;
}

TSharedPtr<SWidget> FPatrolPathVisualizer::GenerateContextMenu() const
{
	FMenuBuilder MenuBuilder(true, 0);
	MenuBuilder.AddMenuEntry(
	  LOCTEXT("AddPatrolPoint", "Add Point Here"),               // 1. libellé
	  LOCTEXT("AddPatrolPointTooltip", "Insert a point on this segment"), // 2. tooltip
	  FSlateIcon(),                                              // 3. icône (vide = aucune)
	  FUIAction(                                                 // 4. l'action
FExecuteAction::CreateLambda([this]()
		{
					  // au clic : insertion du point
		  }),
		  FCanExecuteAction::CreateLambda([this]()
		  {
				  // entrée active ?
		  	return EditedComponent.IsValid() && SelectedSegmentIndex != INDEX_NONE;
		  })
	  )
	);
	
	return FComponentVisualizer::GenerateContextMenu();
}

#undef LOCTEXT_NAMESPACE

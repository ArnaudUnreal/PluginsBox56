#include "SMiniMapViewport.h"
#include "Editor.h"
#include "EngineUtils.h"
#include "ActorEditorUtils.h"
#include "ScopedTransaction.h"
#include "Engine/Selection.h"
#include "GameFramework/Info.h"
#include "Misc/CoreDelegates.h"
#include "LevelEditorViewport.h"
#include "RenderingThread.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Framework/Application/SlateApplication.h"
#include "Rendering/DrawElements.h"
#include "Styling/CoreStyle.h"
#include "Widgets/Layout/SBorder.h"

#define LOCTEXT_NAMESPACE "SMiniMapViewport"

namespace MiniMap
{
	constexpr float ZoomMin = 0.1f;
	constexpr float ZoomMax = 50.f;
	constexpr float ZoomStepFactor = 1.15f;   // per wheel notch
	constexpr double MinBoundsExtent = 1000.0; // 10m half-size
	constexpr double MaxActorExtent = 1.0e6;   // 10km half-size: bigger bounds (sky spheres...) are ignored
	constexpr float PickRadiusPx = 6.f;
	constexpr float DotHalfSizePx = 2.f;
	constexpr float MinFootprintPx = 6.f;      // smaller footprints are drawn as dots
	constexpr int32 BackgroundResolution = 2048;

	static UWorld* GetEditorWorld()
	{
		return GEditor ? GEditor->GetEditorWorldContext().World() : nullptr;
	}

	static bool IsMappableActor(const AActor* A)
	{
		return IsValid(A)
			&& !A->IsTemplate()
			&& !A->IsEditorOnly()
			&& !A->IsHiddenEd()
			&& !A->IsA<AInfo>() // WorldSettings, GameMode...: no spatial meaning
			&& !FActorEditorUtils::IsABuilderBrush(A);
	}

	// 3D bounds usable on the map, invalid if none or unreasonably large
	static FBox GetActorBounds(const AActor* A)
	{
		const FBox Bounds = A->GetComponentsBoundingBox(/*bNonColliding*/ true);
		if (Bounds.IsValid && Bounds.GetExtent().GetMax() < MaxActorExtent)
		{
			return Bounds;
		}
		return FBox(ForceInit);
	}

	static FBox2D ToFootprint(const FBox& Bounds)
	{
		return Bounds.IsValid
			? FBox2D(FVector2D(Bounds.Min.X, Bounds.Min.Y), FVector2D(Bounds.Max.X, Bounds.Max.Y))
			: FBox2D(ForceInit);
	}

	static FLevelEditorViewportClient* GetActivePerspectiveClient()
	{
		if (!GEditor) return nullptr;
		if (GCurrentLevelEditingViewportClient && GCurrentLevelEditingViewportClient->IsPerspective())
		{
			return GCurrentLevelEditingViewportClient;
		}
		for (FLevelEditorViewportClient* VC : GEditor->GetLevelViewportClients())
		{
			if (VC && VC->IsPerspective()) return VC;
		}
		return nullptr;
	}

	static void AddLine(FSlateWindowElementList& Out, int32 Layer, const FGeometry& Geo,
		const FVector2D& A, const FVector2D& B, const FLinearColor& Col, float Thickness = 1.f)
	{
		TArray<FVector2f> Points;
		Points.Add(FVector2f(A));
		Points.Add(FVector2f(B));
		FSlateDrawElement::MakeLines(Out, Layer, Geo.ToPaintGeometry(), MoveTemp(Points),
			ESlateDrawEffect::None, Col, true, Thickness);
	}

	static void AddRectOutline(FSlateWindowElementList& Out, int32 Layer, const FGeometry& Geo,
		const FSlateRect& R, const FLinearColor& Col, float Thickness = 1.f)
	{
		TArray<FVector2f> Points;
		Points.Add(FVector2f(R.Left, R.Top));
		Points.Add(FVector2f(R.Right, R.Top));
		Points.Add(FVector2f(R.Right, R.Bottom));
		Points.Add(FVector2f(R.Left, R.Bottom));
		Points.Add(FVector2f(R.Left, R.Top));
		FSlateDrawElement::MakeLines(Out, Layer, Geo.ToPaintGeometry(), MoveTemp(Points),
			ESlateDrawEffect::None, Col, true, Thickness);
	}

	static void AddFilledRect(FSlateWindowElementList& Out, int32 Layer, const FGeometry& Geo,
		const FVector2D& TopLeft, const FVector2D& RectSize, const FSlateBrush* Brush, const FLinearColor& Col)
	{
		FSlateDrawElement::MakeBox(Out, Layer,
			Geo.ToPaintGeometry(RectSize, FSlateLayoutTransform(TopLeft)),
			Brush, ESlateDrawEffect::None, Col);
	}
}

void SMiniMapViewport::Construct(const FArguments& InArgs)
{
	Zoom = FMath::Clamp(InArgs._InitialZoom, MiniMap::ZoomMin, MiniMap::ZoomMax);

	// Use explicit bounds if provided, otherwise fit the current editor world
	if (InArgs._InitialWorldBounds.IsSet() && InArgs._InitialWorldBounds->bIsValid)
	{
		WorldBounds = InArgs._InitialWorldBounds.GetValue();
	}
	else
	{
		RecomputeWorldBounds();
	}

	// Keep pan/zoomed content from drawing over neighbouring panels
	SetClipping(EWidgetClipping::ClipToBounds);

	FEditorDelegates::MapChange.AddSP(this, &SMiniMapViewport::HandleMapChange);
	FCoreDelegates::OnActorLabelChanged.AddSP(this, &SMiniMapViewport::HandleActorLabelChanged);
	if (GEngine)
	{
		GEngine->OnLevelActorAdded().AddSP(this, &SMiniMapViewport::HandleActorAddedOrDeleted);
		GEngine->OnLevelActorDeleted().AddSP(this, &SMiniMapViewport::HandleActorAddedOrDeleted);
		GEngine->OnActorMoved().AddSP(this, &SMiniMapViewport::HandleActorMoved);
	}

	ChildSlot
	[
		SNew(SBorder)
		.BorderImage(FCoreStyle::Get().GetBrush("NoBorder"))
	];
}

SMiniMapViewport::~SMiniMapViewport()
{
	FEditorDelegates::MapChange.RemoveAll(this);
	FCoreDelegates::OnActorLabelChanged.RemoveAll(this);
	if (GEngine)
	{
		GEngine->OnLevelActorAdded().RemoveAll(this);
		GEngine->OnLevelActorDeleted().RemoveAll(this);
		GEngine->OnActorMoved().RemoveAll(this);
	}
}

void SMiniMapViewport::HandleMapChange(uint32 MapChangeFlags)
{
	// Background belongs to the previous level
	BackgroundRT.Reset();
	BackgroundBrush.SetResourceObject(nullptr);
	FitToLevel();
}

void SMiniMapViewport::HandleActorAddedOrDeleted(AActor* Actor)
{
	bActorCacheDirty = true;
}

void SMiniMapViewport::HandleActorMoved(AActor* Actor)
{
	if (bActorCacheDirty) return;
	if (const int32* Index = CachedActorIndices.Find(Actor))
	{
		CachedActors[*Index].Footprint = MiniMap::ToFootprint(MiniMap::GetActorBounds(Actor));
	}
}

void SMiniMapViewport::HandleActorLabelChanged(AActor* Actor)
{
	// Only the filter depends on the label
	if (!bShowAllActors && !FilterText.IsEmpty())
	{
		bActorCacheDirty = true;
	}
}

void SMiniMapViewport::SetShowAllActors(bool bInShow)
{
	bShowAllActors = bInShow;
	bActorCacheDirty = true;
}

void SMiniMapViewport::SetFilterText(const FString& InFilter)
{
	FilterText = InFilter.TrimStartAndEnd();
	bActorCacheDirty = true;
}

bool SMiniMapViewport::PassesFilter(const AActor* Actor) const
{
	return bShowAllActors
		|| FilterText.IsEmpty()
		|| Actor->GetClass()->GetName().Contains(FilterText)
		|| Actor->GetActorLabel().Contains(FilterText);
}

void SMiniMapViewport::EnsureActorCache() const
{
	if (!bActorCacheDirty) return;
	bActorCacheDirty = false;

	CachedActors.Reset();
	CachedActorIndices.Reset();

	UWorld* World = MiniMap::GetEditorWorld();
	if (!World) return;

	for (TActorIterator<AActor> It(World); It; ++It)
	{
		AActor* A = *It;
		if (!MiniMap::IsMappableActor(A) || !PassesFilter(A)) continue;

		FCachedActor& Entry = CachedActors.AddDefaulted_GetRef();
		Entry.Actor = A;
		Entry.Footprint = MiniMap::ToFootprint(MiniMap::GetActorBounds(A));
		CachedActorIndices.Add(A, CachedActors.Num() - 1);
	}
}

void SMiniMapViewport::RecomputeWorldBounds()
{
	WorldBounds = FBox2D(ForceInit);
	WorldMaxZ = 0.0;
	bActorCacheDirty = true;

	UWorld* World = MiniMap::GetEditorWorld();
	if (World)
	{
		bool bHasZ = false;
		for (TActorIterator<AActor> It(World); It; ++It)
		{
			AActor* A = *It;
			if (!MiniMap::IsMappableActor(A)) continue;

			const FBox Bounds = MiniMap::GetActorBounds(A);
			const double TopZ = Bounds.IsValid ? Bounds.Max.Z : A->GetActorLocation().Z;
			if (Bounds.IsValid)
			{
				WorldBounds += MiniMap::ToFootprint(Bounds);
			}
			else
			{
				const FVector Loc = A->GetActorLocation();
				WorldBounds += FVector2D(Loc.X, Loc.Y);
			}
			WorldMaxZ = bHasZ ? FMath::Max(WorldMaxZ, TopZ) : TopZ;
			bHasZ = true;
		}
	}

	// Fallback if empty
	if (!WorldBounds.bIsValid)
	{
		WorldBounds = FBox2D(FVector2D(-5000,-5000), FVector2D(5000,5000));
	}

	// Avoid degenerate bounds (single actor, aligned actors): enforce a minimum extent
	const FVector2D Center = WorldBounds.GetCenter();
	const FVector2D Extent = WorldBounds.GetExtent().ComponentMax(FVector2D(MiniMap::MinBoundsExtent, MiniMap::MinBoundsExtent));
	WorldBounds = FBox2D(Center - Extent, Center + Extent);
}

void SMiniMapViewport::FitToLevel()
{
	RecomputeWorldBounds();
	Zoom = 1.0f;
	Pan = FVector2D::ZeroVector;
}

void SMiniMapViewport::CaptureBackground()
{
	UWorld* World = MiniMap::GetEditorWorld();
	if (!World) return;

	// Square capture covering the current bounds
	const FVector2D Center = WorldBounds.GetCenter();
	const double Side = WorldBounds.GetSize().GetMax();

	if (!BackgroundRT.IsValid())
	{
		UTextureRenderTarget2D* RT = NewObject<UTextureRenderTarget2D>(GetTransientPackage(), NAME_None, RF_Transient);
		RT->ClearColor = FLinearColor::Black;
		RT->InitCustomFormat(MiniMap::BackgroundResolution, MiniMap::BackgroundResolution, PF_B8G8R8A8, false);
		RT->UpdateResourceImmediate(true);
		BackgroundRT.Reset(RT);
	}

	USceneCaptureComponent2D* Capture = NewObject<USceneCaptureComponent2D>(GetTransientPackage(), NAME_None, RF_Transient);
	Capture->ProjectionType = ECameraProjectionMode::Orthographic;
	Capture->OrthoWidth = Side;
	Capture->TextureTarget = BackgroundRT.Get();
	Capture->CaptureSource = ESceneCaptureSource::SCS_FinalColorLDR;
	Capture->bCaptureEveryFrame = false;
	Capture->bCaptureOnMovement = false;
	Capture->ShowFlags.SetFog(false);
	Capture->ShowFlags.SetVolumetricFog(false);

	// Looking straight down with image right = +X and image down = +Y (same as the map)
	Capture->SetWorldLocationAndRotation(
		FVector(Center.X, Center.Y, WorldMaxZ + 1000.0),
		FRotator(-90.f, -90.f, 0.f));

	Capture->RegisterComponentWithWorld(World);
	Capture->CaptureScene();
	FlushRenderingCommands(); // capture must be done before the component goes away
	Capture->DestroyComponent();

	BackgroundBounds = FBox2D(Center - FVector2D(Side * 0.5), Center + FVector2D(Side * 0.5));
	BackgroundBrush.SetResourceObject(BackgroundRT.Get());
	BackgroundBrush.ImageSize = FVector2D(MiniMap::BackgroundResolution);
	BackgroundBrush.DrawAs = ESlateBrushDrawType::Image;
	bShowBackground = true;
}

void SMiniMapViewport::MoveEditorCameraTo(const FVector& WorldPos)
{
	if (!GEditor) return;
	UWorld* World = MiniMap::GetEditorWorld();

	// Ground height under the clicked point
	FVector Target(WorldPos.X, WorldPos.Y, 0.0);
	if (World)
	{
		FHitResult Hit;
		const FCollisionQueryParams Params(SCENE_QUERY_STAT(MiniMapGroundTrace), /*bTraceComplex*/ true);
		if (World->LineTraceSingleByChannel(Hit,
			FVector(WorldPos.X, WorldPos.Y, HALF_WORLD_MAX),
			FVector(WorldPos.X, WorldPos.Y, -HALF_WORLD_MAX),
			ECC_Visibility, Params))
		{
			Target.Z = Hit.ImpactPoint.Z;
		}
	}

	// Active perspective camera: keep rotation, place it so it looks at Target
	if (FLevelEditorViewportClient* VC = MiniMap::GetActivePerspectiveClient())
	{
		const FVector Forward = VC->GetViewRotation().Vector();
		FVector NewLoc;
		if (Forward.Z < -0.1)
		{
			// Keep current height above ground, along the view direction
			const double Height = FMath::Max(VC->GetViewLocation().Z - Target.Z, 500.0);
			NewLoc = Target - Forward * (Height / -Forward.Z);
		}
		else
		{
			// Looking (almost) horizontally: step back from the point
			NewLoc = Target - Forward.GetSafeNormal2D() * 1000.0;
			NewLoc.Z = Target.Z + 300.0;
		}
		VC->SetViewLocation(NewLoc);
		VC->Invalidate();
	}

	// Recenter top/bottom ortho viewports too
	for (FLevelEditorViewportClient* VC : GEditor->GetLevelViewportClients())
	{
		if (VC && (VC->GetViewportType() == LVT_OrthoTop || VC->GetViewportType() == LVT_OrthoBottom))
		{
			const FVector Loc = VC->GetViewLocation();
			VC->SetViewLocation(FVector(Target.X, Target.Y, Loc.Z));
			VC->Invalidate();
		}
	}
}

double SMiniMapViewport::GetFitScale(const FVector2D& Size) const
{
	const FVector2D BSize = WorldBounds.GetSize();
	if (BSize.X <= KINDA_SMALL_NUMBER || BSize.Y <= KINDA_SMALL_NUMBER)
	{
		return 1.0;
	}
	// Same scale on both axes so the map is never stretched
	return FMath::Max(KINDA_SMALL_NUMBER, FMath::Min(Size.X / BSize.X, Size.Y / BSize.Y));
}

FVector2D SMiniMapViewport::WorldToMap(const FVector& W, const FVector2D& Size) const
{
	// Bounds centered in the widget with uniform scale, then pan/zoom
	// (World X → right, World Y → down, like the editor Top view)
	const FVector2D Rel = FVector2D(W.X, W.Y) - WorldBounds.GetCenter();
	const FVector2D Base = Rel * GetFitScale(Size) + Size * 0.5;
	return Base * Zoom + Pan;
}

FVector SMiniMapViewport::MapToWorld(const FVector2D& P, const FVector2D& Size) const
{
	// Inverse of WorldToMap
	const FVector2D Base = (P - Pan) / Zoom;
	const FVector2D XY = (Base - Size * 0.5) / GetFitScale(Size) + WorldBounds.GetCenter();
	return FVector(XY.X, XY.Y, 0.f);
}

FSlateRect SMiniMapViewport::FootprintToMap(const FBox2D& Footprint, const FVector2D& Size) const
{
	const FVector2D A = WorldToMap(FVector(Footprint.Min.X, Footprint.Min.Y, 0.f), Size);
	const FVector2D B = WorldToMap(FVector(Footprint.Max.X, Footprint.Max.Y, 0.f), Size);
	return FSlateRect(A, B);
}

AActor* SMiniMapViewport::FindActorAt(const FVector2D& LocalPos, const FVector2D& Size) const
{
	TArray<AActor*> Candidates;
	if (ShowsActorList())
	{
		EnsureActorCache();
		for (const FCachedActor& Entry : CachedActors)
		{
			if (AActor* A = Entry.Actor.Get()) Candidates.Add(A);
		}
	}
	if (GEditor)
	{
		TArray<AActor*> Selected;
		GEditor->GetSelectedActors()->GetSelectedObjects<AActor>(Selected);
		for (AActor* A : Selected) Candidates.AddUnique(A);
	}

	// Prefer dots under the cursor (closest), then the smallest footprint containing it
	AActor* Best = nullptr;
	double BestScore = TNumericLimits<double>::Max();
	for (AActor* A : Candidates)
	{
		if (!IsValid(A)) continue;

		const double DistPx = FVector2D::Distance(WorldToMap(A->GetActorLocation(), Size), LocalPos);
		if (DistPx <= MiniMap::PickRadiusPx)
		{
			if (DistPx < BestScore) { BestScore = DistPx; Best = A; }
			continue;
		}

		const int32* Index = CachedActorIndices.Find(A);
		const FBox2D Footprint = Index ? CachedActors[*Index].Footprint : MiniMap::ToFootprint(MiniMap::GetActorBounds(A));
		if (!Footprint.bIsValid) continue;

		const FSlateRect R = FootprintToMap(Footprint, Size);
		if (R.GetSize().GetMin() >= MiniMap::MinFootprintPx && R.ContainsPoint(LocalPos))
		{
			const double Score = MiniMap::PickRadiusPx + R.GetArea(); // always after dots
			if (Score < BestScore) { BestScore = Score; Best = A; }
		}
	}
	return Best;
}

void SMiniMapViewport::SelectActorFromMap(AActor* Actor, bool bToggle)
{
	if (!GEditor || !IsValid(Actor)) return;

	const FScopedTransaction Transaction(LOCTEXT("MiniMapSelectActor", "Select Actor (Mini-Map)"));
	if (bToggle)
	{
		GEditor->SelectActor(Actor, !Actor->IsSelected(), /*bNotify*/ true, /*bSelectEvenIfHidden*/ true);
	}
	else
	{
		GEditor->SelectNone(/*bNoteSelectionChange*/ false, /*bDeselectBSPSurfs*/ true);
		GEditor->SelectActor(Actor, true, /*bNotify*/ true, /*bSelectEvenIfHidden*/ true);
	}
}

int32 SMiniMapViewport::OnPaint(const FPaintArgs& Args, const FGeometry& Geo,
	const FSlateRect& CullingRect, FSlateWindowElementList& Out, int32 LayerId,
	const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	const FVector2D Size = Geo.GetLocalSize();
	const FSlateBrush* WhiteBrush = FCoreStyle::Get().GetBrush("WhiteBrush");
	const FSlateRect LocalRect(FVector2D::ZeroVector, Size);

	// One layer per kind of element so Slate can batch them
	const int32 BackLayer       = LayerId + 1;
	const int32 BackgroundLayer = LayerId + 2;
	const int32 GridLayer       = LayerId + 3;
	const int32 ActorLayer      = LayerId + 4;
	const int32 SelLayer        = LayerId + 5;
	const int32 CameraLayer     = LayerId + 6;

	// Background
	FSlateDrawElement::MakeBox(Out, BackLayer, Geo.ToPaintGeometry(), WhiteBrush, ESlateDrawEffect::None, BackColor);

	// Captured top-down image
	if (bShowBackground && BackgroundRT.IsValid() && BackgroundBounds.bIsValid)
	{
		const FSlateRect R = FootprintToMap(BackgroundBounds, Size);
		MiniMap::AddFilledRect(Out, BackgroundLayer, Geo, R.GetTopLeft(), R.GetSize(), &BackgroundBrush, FLinearColor::White);
	}

	// Dynamic grid step (keep ~80-160px between lines)
	const float TargetPx = 100.f;
	const FVector2D BoundsSize = WorldBounds.GetSize();
	const double WorldPerPx = 1.0 / (GetFitScale(Size) * FMath::Max(0.001f, Zoom));
	double StepWorld = GridBaseStepWorld;

	// Scale step to be near target pixel size
	if (WorldPerPx > KINDA_SMALL_NUMBER)
	{
		double StepPx = StepWorld / WorldPerPx;
		while (StepPx < TargetPx * 0.8f) { StepWorld *= 2.0; StepPx = StepWorld / WorldPerPx; }
		while (StepPx > TargetPx * 1.6f) { StepWorld *= 0.5; StepPx = StepWorld / WorldPerPx; }
	}

	if (BoundsSize.X > 0 && BoundsSize.Y > 0)
	{
		const double X0 = WorldBounds.Min.X;
		const double X1 = WorldBounds.Max.X;
		const double Y0 = WorldBounds.Min.Y;
		const double Y1 = WorldBounds.Max.Y;

		// Vertical lines along X
		for (double X = FMath::GridSnap<double>(X0, StepWorld); X <= X1 + KINDA_SMALL_NUMBER; X += StepWorld)
		{
			MiniMap::AddLine(Out, GridLayer, Geo, WorldToMap(FVector(X, Y0, 0.f), Size), WorldToMap(FVector(X, Y1, 0.f), Size), GridColor);
		}

		// Horizontal lines along Y
		for (double Y = FMath::GridSnap<double>(Y0, StepWorld); Y <= Y1 + KINDA_SMALL_NUMBER; Y += StepWorld)
		{
			MiniMap::AddLine(Out, GridLayer, Geo, WorldToMap(FVector(X0, Y, 0.f), Size), WorldToMap(FVector(X1, Y, 0.f), Size), GridColor);
		}

		// Axes (X=0, Y=0) if inside bounds
		if (X0 <= 0 && 0 <= X1)
		{
			MiniMap::AddLine(Out, GridLayer, Geo, WorldToMap(FVector(0, Y0, 0), Size), WorldToMap(FVector(0, Y1, 0), Size), AxisColor);
		}
		if (Y0 <= 0 && 0 <= Y1)
		{
			MiniMap::AddLine(Out, GridLayer, Geo, WorldToMap(FVector(X0, 0, 0), Size), WorldToMap(FVector(X1, 0, 0), Size), AxisColor);
		}
	}

	// Draws an actor as its footprint outline if big enough on screen, otherwise as a dot
	auto DrawActor = [&](const AActor* A, const FBox2D& Footprint, int32 Layer, const FLinearColor& Col, float Thickness)
	{
		if (Footprint.bIsValid)
		{
			const FSlateRect R = FootprintToMap(Footprint, Size);
			if (R.GetSize().GetMin() >= MiniMap::MinFootprintPx)
			{
				if (FSlateRect::DoRectanglesIntersect(R, LocalRect))
				{
					MiniMap::AddRectOutline(Out, Layer, Geo, R, Col, Thickness);
				}
				return;
			}
		}

		const FVector2D P = WorldToMap(A->GetActorLocation(), Size);
		const float Half = MiniMap::DotHalfSizePx * Thickness;
		if (LocalRect.ExtendBy(Half).ContainsPoint(P))
		{
			MiniMap::AddFilledRect(Out, Layer, Geo, P - FVector2D(Half), FVector2D(Half * 2.f), WhiteBrush, Col);
		}
	};

	// All actors, or filtered actors
	if (ShowsActorList())
	{
		EnsureActorCache();
		for (const FCachedActor& Entry : CachedActors)
		{
			const AActor* A = Entry.Actor.Get();
			if (!IsValid(A) || A->IsSelected()) continue;
			DrawActor(A, Entry.Footprint, ActorLayer, ActorColor, 1.f);
		}
	}

	// Selected actors, always shown
	if (GEditor)
	{
		TArray<AActor*> Selected;
		GEditor->GetSelectedActors()->GetSelectedObjects<AActor>(Selected);

		for (AActor* A : Selected)
		{
			if (!IsValid(A)) continue;
			const int32* Index = CachedActorIndices.Find(A);
			const FBox2D Footprint = Index ? CachedActors[*Index].Footprint : MiniMap::ToFootprint(MiniMap::GetActorBounds(A));
			DrawActor(A, Footprint, SelLayer, SelColor, 1.5f);
		}
	}

	// Active editor camera: position + horizontal field of view
	if (const FLevelEditorViewportClient* VC = MiniMap::GetActivePerspectiveClient())
	{
		const FVector2D P = WorldToMap(VC->GetViewLocation(), Size);
		const float Yaw = FMath::DegreesToRadians(VC->GetViewRotation().Yaw);
		const float HalfFov = FMath::DegreesToRadians(FMath::Clamp(VC->ViewFOV, 1.f, 170.f) * 0.5f);
		const float Len = 40.f;

		// World X/Y map directly to screen right/down, so yaw maps to the same screen angle
		const FVector2D Left  = P + FVector2D(FMath::Cos(Yaw - HalfFov), FMath::Sin(Yaw - HalfFov)) * Len;
		const FVector2D Right = P + FVector2D(FMath::Cos(Yaw + HalfFov), FMath::Sin(Yaw + HalfFov)) * Len;

		TArray<FVector2f> Wedge;
		Wedge.Add(FVector2f(Left));
		Wedge.Add(FVector2f(P));
		Wedge.Add(FVector2f(Right));
		FSlateDrawElement::MakeLines(Out, CameraLayer, Geo.ToPaintGeometry(), MoveTemp(Wedge),
			ESlateDrawEffect::None, CameraColor, true, 1.5f);

		MiniMap::AddFilledRect(Out, CameraLayer, Geo, P - FVector2D(3.f), FVector2D(6.f), WhiteBrush, CameraColor);
	}

	return CameraLayer;
}

FReply SMiniMapViewport::OnMouseButtonDown(const FGeometry& Geo, const FPointerEvent& E)
{
	if (E.GetEffectingButton() == EKeys::RightMouseButton)
	{
		bRmbDragging = true;
		// Local space so the drag follows the cursor regardless of DPI scale
		DragStart = Geo.AbsoluteToLocal(E.GetScreenSpacePosition());
		PanStart = Pan;
		return FReply::Handled().CaptureMouse(SharedThis(this));
	}
	if (E.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		const FVector2D Local = Geo.AbsoluteToLocal(E.GetScreenSpacePosition());
		const FVector2D Size = Geo.GetLocalSize();

		if (AActor* Actor = FindActorAt(Local, Size))
		{
			SelectActorFromMap(Actor, E.IsControlDown());
		}
		else
		{
			MoveEditorCameraTo(MapToWorld(Local, Size));
		}
		return FReply::Handled();
	}
	return FReply::Unhandled();
}

FReply SMiniMapViewport::OnMouseButtonDoubleClick(const FGeometry& Geo, const FPointerEvent& E)
{
	if (E.GetEffectingButton() == EKeys::LeftMouseButton && GEditor)
	{
		const FVector2D Local = Geo.AbsoluteToLocal(E.GetScreenSpacePosition());
		if (AActor* Actor = FindActorAt(Local, Geo.GetLocalSize()))
		{
			GEditor->MoveViewportCamerasToActor(*Actor, /*bActiveViewportOnly*/ true);
			return FReply::Handled();
		}
	}
	return FReply::Unhandled();
}

FReply SMiniMapViewport::OnMouseButtonUp(const FGeometry& Geo, const FPointerEvent& E)
{
	if (bRmbDragging && E.GetEffectingButton() == EKeys::RightMouseButton)
	{
		bRmbDragging = false;
		return FReply::Handled().ReleaseMouseCapture();
	}
	return FReply::Unhandled();
}

FReply SMiniMapViewport::OnMouseMove(const FGeometry& Geo, const FPointerEvent& E)
{
	if (bRmbDragging)
	{
		const FVector2D Delta = Geo.AbsoluteToLocal(E.GetScreenSpacePosition()) - DragStart;
		Pan = PanStart + Delta;
		return FReply::Handled();
	}
	return FReply::Unhandled();
}

FReply SMiniMapViewport::OnMouseWheel(const FGeometry& Geo, const FPointerEvent& E)
{
	// Multiplicative zoom: each notch scales by the same ratio at any zoom level
	const float OldZoom = Zoom;
	Zoom = FMath::Clamp(Zoom * FMath::Pow(MiniMap::ZoomStepFactor, E.GetWheelDelta()), MiniMap::ZoomMin, MiniMap::ZoomMax);

	// Keep the point under the cursor fixed
	const FVector2D MouseLocal = Geo.AbsoluteToLocal(E.GetScreenSpacePosition());
	const FVector2D Before = (MouseLocal - Pan) / OldZoom;
	const FVector2D After  = (MouseLocal - Pan) / Zoom;
	Pan += (After - Before) * Zoom;

	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE

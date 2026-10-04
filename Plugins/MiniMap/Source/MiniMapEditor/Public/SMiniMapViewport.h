#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Styling/SlateBrush.h"
#include "UObject/StrongObjectPtr.h"
#include "Engine/TextureRenderTarget2D.h"

class AActor;

/**
 * Top-down mini-map of the editor world:
 *  - Pan (RMB drag) / Zoom (Wheel, centered on cursor)
 *  - World-space grid, all actors (optional, filterable), selected actors highlighted
 *  - Active editor camera position and field of view
 *  - LMB on actor: select (Ctrl: toggle) / LMB on empty space: move editor camera there
 *  - Double-click on actor: focus editor camera on it
 *  - Optional top-down captured background image
 */
class SMiniMapViewport : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SMiniMapViewport)
		: _InitialZoom(1.0f)
	{}
		SLATE_ARGUMENT(TOptional<FBox2D>, InitialWorldBounds) // optional, fits current level if unset
		SLATE_ARGUMENT(float, InitialZoom)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	virtual ~SMiniMapViewport() override;

	// Re-scan current editor world and recompute world bounds (XY, from actor footprints)
	void RecomputeWorldBounds();

	// Recompute bounds and reset pan/zoom
	void FitToLevel();

	// Render a top-down orthographic capture of the current bounds as map background
	void CaptureBackground();
	bool HasBackground() const { return BackgroundRT.IsValid(); }

	void SetShowAllActors(bool bInShow) { bShowAllActors = bInShow; }
	bool GetShowAllActors() const { return bShowAllActors; }

	void SetShowBackground(bool bInShow) { bShowBackground = bInShow; }
	bool GetShowBackground() const { return bShowBackground; }

	// Case-insensitive substring on actor class name or label
	void SetFilterText(const FString& InFilter);

	// Move the active editor camera so it looks at WorldPos (ground Z traced), keeping its rotation
	static void MoveEditorCameraTo(const FVector& WorldPos);

	virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual FReply OnMouseButtonDoubleClick(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual FReply OnMouseWheel(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;

	// SWidget overrides
	virtual int32 OnPaint(const FPaintArgs& Args,
		const FGeometry& AllottedGeometry,
		const FSlateRect& MyCullingRect,
		FSlateWindowElementList& OutDrawElements,
		int32 LayerId,
		const FWidgetStyle& InWidgetStyle,
		bool bParentEnabled) const override;

private:
	struct FCachedActor
	{
		TWeakObjectPtr<AActor> Actor;
		FBox2D Footprint = FBox2D(ForceInit); // invalid if actor has no usable bounds
	};

	// Helpers
	FVector2D WorldToMap(const FVector& W, const FVector2D& Size) const;
	FVector    MapToWorld(const FVector2D& P, const FVector2D& Size) const;

	// Uniform pixels-per-world-unit at Zoom = 1 (fits bounds in widget, keeps aspect ratio)
	double GetFitScale(const FVector2D& Size) const;

	// Screen-space rect of a world footprint
	FSlateRect FootprintToMap(const FBox2D& Footprint, const FVector2D& Size) const;

	AActor* FindActorAt(const FVector2D& LocalPos, const FVector2D& Size) const;
	void SelectActorFromMap(AActor* Actor, bool bToggle);

	void EnsureActorCache() const;
	bool PassesFilter(const AActor* Actor) const;

	void HandleMapChange(uint32 MapChangeFlags);
	void HandleActorAddedOrDeleted(AActor* Actor);
	void HandleActorMoved(AActor* Actor);

	// State
	float Zoom = 1.0f;                     // ZoomMin .. ZoomMax
	FVector2D Pan = FVector2D::ZeroVector; // local-space pan in pixels
	FBox2D WorldBounds = FBox2D(ForceInit); // min/max XY
	double WorldMaxZ = 0.0;                // top of mapped actors, used to place the background capture

	bool bShowAllActors = true;
	bool bShowBackground = true;
	FString FilterText;

	// Actor cache (rebuilt lazily when the level changes)
	mutable TArray<FCachedActor> CachedActors;
	mutable TMap<TWeakObjectPtr<AActor>, int32> CachedActorIndices;
	mutable bool bActorCacheDirty = true;

	// Background capture
	TStrongObjectPtr<UTextureRenderTarget2D> BackgroundRT;
	FSlateBrush BackgroundBrush;
	FBox2D BackgroundBounds = FBox2D(ForceInit);

	// Input drag
	bool bRmbDragging = false;
	FVector2D DragStart = FVector2D::ZeroVector; // local space
	FVector2D PanStart = FVector2D::ZeroVector;

	// Visuals
	FLinearColor BackColor   = FLinearColor(0.07f,0.07f,0.07f,1.f);
	FLinearColor GridColor   = FLinearColor(0.15f,0.15f,0.15f,1.f);
	FLinearColor AxisColor   = FLinearColor(0.25f,0.25f,0.25f,1.f);
	FLinearColor ActorColor  = FLinearColor(0.35f,0.55f,0.75f,0.9f);
	FLinearColor SelColor    = FLinearColor(1.f,0.85f,0.2f,1.f);
	FLinearColor CameraColor = FLinearColor(0.3f,1.f,0.4f,1.f);

	// Grid every X cm (world), dynamic step computed from this base
	float GridBaseStepWorld = 100.f; // 1m
};

// Copyright Arnaud Szobad (Mecanode). All Rights Reserved.


#include "PatrolPathComponent.h"

UPatrolPathComponent::UPatrolPathComponent()
{
	Points.Append({ FVector(0,0,0), 
		FVector(300,0,0), 
		FVector(300,300,0), 
		FVector(0,300,0) });
	
	bClosedLoop = true;
	bDrawDebugInGame = false;
	PrimaryComponentTick.bCanEverTick = true;
}

void UPatrolPathComponent::BeginPlay()
{
	Super::BeginPlay();
	
	// 1. Correction du freeze du chemin
	FreezedTransform = GetComponentTransform();
	CurrentIndex = 0;
}

void UPatrolPathComponent::FollowPath(float DeltaTime)
{
	AActor* Owner = GetOwner();
	if (!Owner || !Points.IsValidIndex(CurrentIndex)) return;
	
	FVector Target = GetWorldPoint(CurrentIndex);
	FVector Direction = (Target - Owner->GetActorLocation()).GetSafeNormal2D();	// yaw only
	if (!Direction.IsNearlyZero())
	{
		FRotator Current = Owner->GetActorRotation();
		FRotator Desired = Current;
		Desired.Yaw = Direction.Rotation().Yaw;
		Owner->SetActorRotation(FMath::RInterpConstantTo(Current, Desired,DeltaTime, RotationSpeed));

	}
	
	FVector NewLocation = FMath::VInterpConstantTo(Owner->GetActorLocation(), Target, DeltaTime, Speed);
	Owner->SetActorLocation(NewLocation);
	if (FVector::Dist(NewLocation, Target) <= AcceptanceRadius)
	{
		CurrentIndex = GetNextPointIndex(CurrentIndex);
	}
}

FTransform UPatrolPathComponent::GetPathTransform() const
{
	if (HasBegunPlay())
	{
		return FreezedTransform;
	}
	return GetComponentTransform();
}

int32 UPatrolPathComponent::GetPointCount() const
{
	return Points.Num();
}

/**
 * Position monde d’un point
 * @param index int32
 * @return FVector
 */
FVector UPatrolPathComponent::GetWorldPoint(int32 index) const
{
	if (Points.IsValidIndex(index))
	{
		// ERREUR : le component bouge avec l'Actor
		// return GetComponentTransform().TransformPosition(Points[index]);
		// CORRECTION
		return GetPathTransform().TransformPosition(Points[index]);

	}
	// ERREUR : le component bouge avec l'Actor
	// return GetComponentLocation();
	// CORRECTION
	return GetPathTransform().GetLocation();
}

/**
 * Renvoie tous les points en espace monde, dans l’ordre du chemin
 * @return Result TArray<FVector> 
 */
TArray<FVector> UPatrolPathComponent::GetWorldPoints() const
{
	TArray<FVector> Result;
	Result.Reserve(GetPointCount());
	int32 i = 0;
	while (i < GetPointCount())
	{
		Result.Add(GetWorldPoint(i));
		i++;
	}
	return Result;
}

/**
 * Renvoie l’index du point qui suit Index, en tenant compte de la boucle fermée
 * @param index 
 * @return 
 */
int32 UPatrolPathComponent::GetNextPointIndex(int32 index) const
{
	if (index+1<GetPointCount())
	{
		return index+1;
	}
	if (bClosedLoop && GetPointCount()>2)
	{
		return 0;
	}
	return INDEX_NONE;
}

void UPatrolPathComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (bFollowPath) FollowPath(DeltaTime);
	
	#if ENABLE_DRAW_DEBUG
		if (bDrawDebugInGame)
		{
			FVector P;
			FColor Color = FColor::Green;
			float Size = 12;
			int32 next = 0;
			int32 i = 0;
			while (i < GetPointCount())
			{
				// P = Points[i]; ERREUR : le chemin ne tourne pas avec l'Actor
				P = GetWorldPoint(i); // Correction
				DrawDebugPoint(GetWorld(), P, Size, Color);
				next = GetNextPointIndex(i);
				if (next != INDEX_NONE)
				{
					DrawDebugLine(GetWorld(), P, GetWorldPoint(next), Color);
				}
				i++;
			}
		}
	#endif
		
}

 
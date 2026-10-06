// Copyright Arnaud Szobad (Mecanode). All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PatrolPathComponent.generated.h"


UCLASS(ClassGroup=(AI), meta=(BlueprintSpawnableComponent))
class PATROLPATH_API UPatrolPathComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	UPatrolPathComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
							   FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Patrol Path")
	TArray<FVector> Points;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Patrol Path")
	bool bClosedLoop;
	UPROPERTY(EditAnywhere, Category="Patrol Path|Debug")
	bool bDrawDebugInGame;
	
	UFUNCTION(BlueprintPure)
	int32 GetPointCount() const;
	UFUNCTION(BlueprintPure)
	FVector GetWorldPoint(int32 index) const;
	UFUNCTION(BlueprintPure)
	TArray<FVector> GetWorldPoints() const;
	UFUNCTION(BlueprintPure)
	int32 GetNextPointIndex(int32 index) const;
};

// // Copyright Arnaud Szobad 2026 All Rights Reserved.

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Patrol Path")
	bool bClosedLoop;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Patrol Path")
	bool bDrawDebugInGame;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Patrol Path|Follow")
	bool bFollowPath = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin=0), Category="Patrol Path|Follow")
	float Speed = 300;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin=0), Category="Patrol Path|Follow")
	float RotationSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin=1), Category="Patrol Path|Follow")
	float AcceptanceRadius = 10;
	
	UFUNCTION(BlueprintPure)
	int32 GetPointCount() const;
	UFUNCTION(BlueprintPure)
	FVector GetWorldPoint(int32 index) const;
	UFUNCTION(BlueprintPure)
	TArray<FVector> GetWorldPoints() const;
	UFUNCTION(BlueprintPure)
	int32 GetNextPointIndex(int32 index) const;
	
	virtual void BeginPlay() override;
	
private:
	int32 CurrentIndex = 0;
	FTransform FreezedTransform;
	
	void FollowPath(float DeltaTime);
	FTransform GetPathTransform() const;
	
	
};

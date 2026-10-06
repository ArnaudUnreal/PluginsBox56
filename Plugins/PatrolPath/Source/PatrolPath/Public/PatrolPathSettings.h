// // Copyright Arnaud Szobad 2026 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "PatrolPathSettings.generated.h"

/**
 * 
 */
UCLASS(Config=Game, DefaultConfig, meta=(DisplayName="Patrol Path"))
class PATROLPATH_API UPatrolPathSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:
	UPROPERTY(Config, EditAnywhere, Category="Display")
	FColor PointColor = FColor::Green;
	UPROPERTY(Config, EditAnywhere, Category="Display")
	FColor SelectedPointColor = FColor::Orange;
	UPROPERTY(Config, EditAnywhere, meta=(ClampMin=1), Category="Display")
	int32 PointSize = 12;
	
	virtual FName GetCategoryName() const override { return TEXT("Plugins"); }
};

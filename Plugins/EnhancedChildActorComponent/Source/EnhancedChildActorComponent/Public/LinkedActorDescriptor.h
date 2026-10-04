// Copyright Mecanode. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "StructUtils/PropertyBag.h"
#include "LinkedActorDescriptor.generated.h"

/**
 * Describes the child actor owned by an UEnhancedChildActorComponent.
 * Only this descriptor is serialized with the parent: the child itself is a runtime projection of it.
 */
USTRUCT(BlueprintType)
struct ENHANCEDCHILDACTORCOMPONENT_API FLinkedActorDescriptor
{
	GENERATED_BODY()

	/** Class of the child actor to spawn. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Linked Actor")
	TSoftClassPtr<AActor> ChildClass;

	/** Property values applied to the child between SpawnActorDeferred and FinishSpawning, matched by name and type. */
	UPROPERTY(EditAnywhere, Category = "Linked Actor")
	FInstancedPropertyBag Overrides;

	/** Stable identifier of the link between the parent and its child. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Linked Actor")
	FGuid LinkGuid;
};

// Copyright Arnaud Szobad (Mecanode). All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "LinkedActorDescriptor.h"
#include "EnhancedChildActorComponent.generated.h"

/**
 * Alternative to UChildActorComponent.
 * Spawns a child actor from a descriptor and attaches it to this component.
 */
UCLASS(ClassGroup = (Utility), meta = (BlueprintSpawnableComponent))
class ENHANCEDCHILDACTORCOMPONENT_API UEnhancedChildActorComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	UEnhancedChildActorComponent();

	/** Returns the spawned child actor, or nullptr if it does not exist. */
	UFUNCTION(BlueprintPure, Category = "Linked Actor")
	AActor* GetChildActor() const { return ChildActor; }

	/** Spawns the child actor from the descriptor. Destroys the previous one first. */
	UFUNCTION(BlueprintCallable, Category = "Linked Actor")
	void CreateChildActor();

	/** Destroys the child actor if it exists. */
	UFUNCTION(BlueprintCallable, Category = "Linked Actor")
	void DestroyChildActor();

	//~ Begin UObject Interface
	virtual void PostInitProperties() override;
	virtual void PostDuplicate(EDuplicateMode::Type DuplicateMode) override;
#if WITH_EDITOR
	virtual void PostEditImport() override;
#endif
	//~ End UObject Interface

	//~ Begin UActorComponent Interface
	virtual TStructOnScope<FActorComponentInstanceData> GetComponentInstanceData() const override;
	//~ End UActorComponent Interface

protected:
	//~ Begin UActorComponent Interface
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	//~ End UActorComponent Interface

	/** Gives this link a new GUID. Templates (CDO, Blueprint archetypes) are skipped so that each instance gets its own. */
	void RegenerateLinkGuid();

	/** Copies the descriptor overrides onto the child. Called between SpawnActorDeferred and FinishSpawning. */
	void ApplyOverrides(AActor* Child) const;

	/** Serialized description of the child. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Linked Actor", meta = (ShowOnlyInnerProperties))
	FLinkedActorDescriptor Descriptor;

private:
	/** The spawned child. Never serialized: it is rebuilt from the descriptor. */
	UPROPERTY(Transient, DuplicateTransient)
	TObjectPtr<AActor> ChildActor;

	friend struct FEnhancedChildActorComponentInstanceData;
};

/**
 * Carries the link GUID across a rerun of the owner's construction script,
 * whatever the component's creation method (SCS, UCS or instance).
 */
USTRUCT()
struct FEnhancedChildActorComponentInstanceData : public FSceneComponentInstanceData
{
	GENERATED_BODY()

	FEnhancedChildActorComponentInstanceData() = default;
	explicit FEnhancedChildActorComponentInstanceData(const UEnhancedChildActorComponent* SourceComponent);

	virtual bool ContainsData() const override;
	virtual void ApplyToComponent(UActorComponent* Component, const ECacheApplyPhase CacheApplyPhase) override;

	UPROPERTY()
	FGuid LinkGuid;
};

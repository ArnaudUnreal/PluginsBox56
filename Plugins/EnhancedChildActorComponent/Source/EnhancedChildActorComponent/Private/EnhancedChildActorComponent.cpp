// Copyright Mecanode. All Rights Reserved.

#include "EnhancedChildActorComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"

DEFINE_LOG_CATEGORY_STATIC(LogEnhancedChildActor, Log, All);

UEnhancedChildActorComponent::UEnhancedChildActorComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UEnhancedChildActorComponent::RegenerateLinkGuid()
{
	if (!IsTemplate())
	{
		Descriptor.LinkGuid = FGuid::NewGuid();
	}
}

void UEnhancedChildActorComponent::PostInitProperties()
{
	Super::PostInitProperties();

	// On load, the serialized GUID overwrites this one right after.
	// On a construction script rerun, FEnhancedChildActorComponentInstanceData restores the previous one.
	if (!Descriptor.LinkGuid.IsValid())
	{
		RegenerateLinkGuid();
	}
}

void UEnhancedChildActorComponent::PostDuplicate(EDuplicateMode::Type DuplicateMode)
{
	Super::PostDuplicate(DuplicateMode);

	// A plain duplicate is a new link. PIE and world duplication keep the GUID so the link stays identifiable.
	if (DuplicateMode == EDuplicateMode::Normal)
	{
		RegenerateLinkGuid();
	}
}

#if WITH_EDITOR
void UEnhancedChildActorComponent::PostEditImport()
{
	Super::PostEditImport();

	// Copy-paste and editor duplication (Ctrl+D, Alt+drag) go through text import: the copy is a new link.
	RegenerateLinkGuid();
}
#endif

FEnhancedChildActorComponentInstanceData::FEnhancedChildActorComponentInstanceData(const UEnhancedChildActorComponent* SourceComponent)
	: FSceneComponentInstanceData(SourceComponent)
	, LinkGuid(SourceComponent->Descriptor.LinkGuid)
{
}

bool FEnhancedChildActorComponentInstanceData::ContainsData() const
{
	return LinkGuid.IsValid() || Super::ContainsData();
}

void FEnhancedChildActorComponentInstanceData::ApplyToComponent(UActorComponent* Component, const ECacheApplyPhase CacheApplyPhase)
{
	Super::ApplyToComponent(Component, CacheApplyPhase);

	CastChecked<UEnhancedChildActorComponent>(Component)->Descriptor.LinkGuid = LinkGuid;
}

TStructOnScope<FActorComponentInstanceData> UEnhancedChildActorComponent::GetComponentInstanceData() const
{
	return MakeStructOnScope<FActorComponentInstanceData, FEnhancedChildActorComponentInstanceData>(this);
}

void UEnhancedChildActorComponent::ApplyOverrides(AActor* Child) const
{
	const UPropertyBag* BagStruct = Descriptor.Overrides.GetPropertyBagStruct();
	if (!BagStruct)
	{
		return;
	}

	const uint8* BagMemory = Descriptor.Overrides.GetValue().GetMemory();
	UClass* ChildClass = Child->GetClass();

	for (const FPropertyBagPropertyDesc& Desc : BagStruct->GetPropertyDescs())
	{
		const FProperty* SourceProperty = Desc.CachedProperty;
		const FProperty* TargetProperty = ChildClass->FindPropertyByName(Desc.Name);

		if (!SourceProperty || !TargetProperty || !TargetProperty->SameType(SourceProperty))
		{
			UE_LOG(LogEnhancedChildActor, Warning, TEXT("%s: override '%s' has no matching property on %s."),
				*GetPathName(), *Desc.Name.ToString(), *ChildClass->GetName());
			continue;
		}

		TargetProperty->CopyCompleteValue(
			TargetProperty->ContainerPtrToValuePtr<void>(Child),
			SourceProperty->ContainerPtrToValuePtr<void>(BagMemory));
	}
}

void UEnhancedChildActorComponent::DestroyChildActor()
{
	if (IsValid(ChildActor))
	{
		ChildActor->Destroy();
	}
	ChildActor = nullptr;
}

void UEnhancedChildActorComponent::CreateChildActor()
{
	DestroyChildActor();

	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	// TODO: async loading will replace this synchronous load.
	UClass* ChildClass = Descriptor.ChildClass.LoadSynchronous();
	if (!ChildClass)
	{
		return;
	}

	const FTransform SpawnTransform = GetComponentTransform();

	AActor* NewChild = World->SpawnActorDeferred<AActor>(
		ChildClass,
		SpawnTransform,
		GetOwner(),
		nullptr,
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	if (!NewChild)
	{
		return;
	}

	ApplyOverrides(NewChild);
	NewChild->FinishSpawning(SpawnTransform);

	// The child's components only exist after FinishSpawning (construction script), so attach afterwards.
	NewChild->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	ChildActor = NewChild;
}

void UEnhancedChildActorComponent::BeginPlay()
{
	Super::BeginPlay();

	CreateChildActor();
}

void UEnhancedChildActorComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	DestroyChildActor();

	Super::EndPlay(EndPlayReason);
}

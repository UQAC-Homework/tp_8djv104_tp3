#include "InteractionRangeComponent.h"

/// Gets the components of the given actor overlapping the given component
static TArray<UPrimitiveComponent*> GetActorOverlappingComponents(
	const UPrimitiveComponent* Component,
	AActor* Actor
)
{
	TArray<UPrimitiveComponent*> OverlappingComponents;
	Component->GetOverlappingComponents(OverlappingComponents);

	return OverlappingComponents.FilterByPredicate([Actor](const UPrimitiveComponent* Comp)
	{
		return Comp && Comp->GetOwner() == Actor;
	});
}

void UInteractionRangeComponent::OnComponentOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                         UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                                                         bool bFromSweep, const FHitResult& SweepResult) const
{
	if (!OnActorEnterRange.IsBound())
		return;

	if (OtherActor == GetOwner())
		return;

	const auto OverlappingComponents = GetActorOverlappingComponents(
		OverlappedComponent,
		OtherActor
	);

	const auto bContainsOtherComponent = OverlappingComponents.ContainsByPredicate(
		[OtherComp](const UPrimitiveComponent* Comp)
		{
			return Comp != OtherComp;
		}
	);

	if (bContainsOtherComponent)
		return;

	OnActorEnterRange.Broadcast(OtherActor);
}

void UInteractionRangeComponent::OnComponentOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                       UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) const
{
	if (!OnActorExitRange.IsBound())
		return;

	if (OtherActor == GetOwner())
		return;

	const auto OverlappingComponents = GetActorOverlappingComponents(
		OverlappedComponent,
		OtherActor
	);

	if (OverlappingComponents.Num() > 0)
		return;

	OnActorExitRange.Broadcast(OtherActor);
}

UInteractionRangeComponent::UInteractionRangeComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInteractionRangeComponent::SetCollisionRange(UPrimitiveComponent* InRangeCollision)
{
	if (RangeCollision)
	{
		RangeCollision->OnComponentBeginOverlap.RemoveDynamic(
			this, &UInteractionRangeComponent::OnComponentOverlapBegin
		);

		RangeCollision->OnComponentEndOverlap.RemoveDynamic(
			this, &UInteractionRangeComponent::OnComponentOverlapEnd
		);
	}

	check(InRangeCollision);
	RangeCollision = InRangeCollision;

	RangeCollision->OnComponentBeginOverlap.AddDynamic(
		this,
		&UInteractionRangeComponent::OnComponentOverlapBegin
	);

	RangeCollision->OnComponentEndOverlap.AddDynamic(
		this,
		&UInteractionRangeComponent::OnComponentOverlapEnd
	);
}

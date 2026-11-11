#include "InteractionRangeComponent.h"

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
	if (OtherActor == GetOwner())
		return;

	const TArray<UPrimitiveComponent*> OverlappingComponents = GetActorOverlappingComponents(
		OverlappedComponent, OtherActor);
	const auto bContainsOtherComponent = OverlappingComponents.ContainsByPredicate(
		[OtherComp](const UPrimitiveComponent* Comp)
		{
			return Comp != OtherComp;
		});

	if (bContainsOtherComponent)
		return;

	OnActorEnterRange.Broadcast(OtherActor);
}

void UInteractionRangeComponent::OnComponentOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                       UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) const
{
	if (OtherActor == GetOwner())
		return;

	TArray<UPrimitiveComponent*> OverlappingComponents;
	OverlappedComponent->GetOverlappingComponents(OverlappingComponents);

	const auto bIsOverlapping = OverlappingComponents.ContainsByPredicate([OtherActor](const UPrimitiveComponent* Comp)
	{
		return Comp && Comp->GetOwner() == OtherActor;
	});

	if (bIsOverlapping)
		return;

	OnActorExitRange.Broadcast(OtherActor);
}

UInteractionRangeComponent::UInteractionRangeComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInteractionRangeComponent::Initialize(UPrimitiveComponent* InRangeCollision)
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

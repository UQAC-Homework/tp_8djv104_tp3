#include "InteractableComponent.h"

UInteractableComponent::UInteractableComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
}

void UInteractableComponent::EnableFeedback(AActor* Instigator) const
{
	if (!OnEnterFeedback.IsBound())
		return;

	check(Instigator);
	const auto Owner = Cast<APawn>(Instigator);

	check(Owner);
	OnEnterFeedback.Broadcast(Owner);
}

void UInteractableComponent::DisableFeedback(AActor* Instigator) const
{
	if (!OnExitFeedback.IsBound())
		return;

	check(Instigator);
	const auto Owner = Cast<APawn>(Instigator);

	check(Owner);
	OnExitFeedback.Broadcast(Owner);
}

void UInteractableComponent::Interact()
{
}

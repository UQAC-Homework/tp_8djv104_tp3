#include "InteractableComponent.h"

UInteractableComponent::UInteractableComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
}

void UInteractableComponent::EnableFeedback(APawn* Instigator) const
{
	if (!OnEnterFeedback.IsBound())
		return;

	check(Instigator);
	OnEnterFeedback.Broadcast(Instigator);
}

void UInteractableComponent::DisableFeedback(APawn* Instigator) const
{
	if (!OnExitFeedback.IsBound())
		return;

	check(Instigator);
	OnExitFeedback.Broadcast(Instigator);
}

void UInteractableComponent::Interact_Implementation(APawn* Instigator)
{
	OnInteract.Broadcast(Instigator);
}

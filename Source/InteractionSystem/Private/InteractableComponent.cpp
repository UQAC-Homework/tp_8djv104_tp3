#include "InteractableComponent.h"

UInteractableComponent::UInteractableComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInteractableComponent::EnableFeedback(AActor* Instigator)
{
	if (!OnEnterFeedback.IsBound())
		return;

	check(Instigator);
	const auto Owner = Cast<APawn>(Instigator);

	check(Owner);
	OnEnterFeedback.Broadcast(Owner);
}

void UInteractableComponent::DisableFeedback(AActor* Instigator)
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

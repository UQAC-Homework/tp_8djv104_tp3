#include "InteractorComponent.h"

UInteractorComponent::UInteractorComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInteractorComponent::EnterFeedback(AActor* Actor)
{
	const auto Owner = GetOwner();
	check(Owner);
	
	if (Owner->HasAuthority())
		return;

	check(Actor);
	const auto Interactable = Actor->GetComponentByClass<UInteractableComponent>();

	if (!Interactable)
		return;

	Interactables.AddUnique(Interactable);
	Interactable->EnableFeedback(Owner);
}

void UInteractorComponent::ExitFeedback(AActor* Actor)
{
	const auto Owner = GetOwner();
	check(Owner);
	
	if (Owner->HasAuthority())
		return;

	check(Actor);
	const auto Interactable = Actor->GetComponentByClass<UInteractableComponent>();

	if (!Interactable)
		return;

	Interactables.RemoveSingle(Interactable);
	Interactable->DisableFeedback(Owner);
}

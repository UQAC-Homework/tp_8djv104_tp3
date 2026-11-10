#include "InteractorComponent.h"

/// Tries to get the interactable component from the given actor
static FORCEINLINE UInteractableComponent* GetInteractable(const AActor* Actor)
{
	if (!Actor)
		return nullptr;
	
	return  Actor->GetComponentByClass<UInteractableComponent>();
}

/// Tries to get the pawn of the owner of the given component
static FORCEINLINE APawn* GetOwnerPawn(const UActorComponent* Component)
{
	if (!Component)
		return nullptr;
	
	return Cast<APawn>(Component->GetOwner());
}

void UInteractorComponent::Server_Interact_Implementation(AActor* Actor)
{
	const auto Interactable = GetInteractable(Actor);
	check(Interactable);
	
	const auto Pawn = GetOwnerPawn(this);
	check(Pawn);

	Interactable->Interact(Pawn);
}

bool UInteractorComponent::Server_Interact_Validate(AActor* Actor)
{
	if (!Actor)
		return false;
	
	if (!Actor->IsValidLowLevel())
		return false;
	
	const auto Pawn = GetOwnerPawn(this);
	
	if (!Pawn)
		return false;
	
	const auto Interactable = GetInteractable(Actor);

	if (!Interactable)
		return false;
	
	return Interactables.Contains(Interactable);
}

UInteractorComponent::UInteractorComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
}

void UInteractorComponent::EnterFeedback(const AActor* Actor)
{
	const auto Interactable = GetInteractable(Actor);

	if (!Interactable)
		return;

	if (Interactables.Contains(Interactable))
		return;

	Interactables.Add(Interactable);
	
	const auto Pawn = GetOwnerPawn(this);
	check(Pawn);

	if (Pawn->IsLocallyControlled())
		Interactable->EnableFeedback(Pawn);
}

void UInteractorComponent::ExitFeedback(const AActor* Actor)
{
	const auto Interactable = GetInteractable(Actor);

	if (!Interactable)
		return;
	
	if (!Interactables.Contains(Interactable))
		return;

	Interactables.Remove(Interactable);
	
	const auto Pawn = GetOwnerPawn(this);
	check(Pawn);

	if (Pawn->IsLocallyControlled())
		Interactable->DisableFeedback(Pawn);
}

void UInteractorComponent::Interact(AActor* Actor)
{
	const auto Interactable = GetInteractable(Actor);

	if (!Interactable)
		return;
	
	if (!Interactables.Contains(Interactable))
		return;
	
	const auto Pawn = GetOwnerPawn(this);
	check(Pawn);
	
	if (Pawn->IsLocallyControlled())
		Server_Interact(Actor);
}

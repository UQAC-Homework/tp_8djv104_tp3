#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractableComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFeedback, APawn*, Instigator);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteract, APawn*, Instigator);

#define INTERACT "Interact"

/// Component responsible to handle incoming interactions
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class INTERACTIONSYSTEM_API UInteractableComponent : public UActorComponent
{
	GENERATED_BODY()

	/// Called when an interactor has entered its range
	UPROPERTY(BlueprintAssignable, Category=INTERACT)
	FOnFeedback OnEnterFeedback;

	/// Called when an interactor has exited its range
	UPROPERTY(BlueprintAssignable, Category=INTERACT)
	FOnFeedback OnExitFeedback;

	/// Called when an interactor interacts with this object
	UPROPERTY(BlueprintAssignable, Category=INTERACT)
	FOnInteract OnInteract;

public:
	UInteractableComponent();

	/// Enables the feedback of an interaction
	void EnableFeedback(APawn* Instigator) const;

	/// Disables the feedback of an interaction
	void DisableFeedback(APawn* Instigator) const;

	/// Interacts with this interaction
	UFUNCTION(Server, Reliable)
	void Interact(APawn* Instigator);
};

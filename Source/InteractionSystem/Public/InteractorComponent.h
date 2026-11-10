#pragma once

#include "CoreMinimal.h"
#include "InteractableComponent.h"
#include "Components/ActorComponent.h"
#include "InteractorComponent.generated.h"

#define INTERACT "Interact"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class INTERACTIONSYSTEM_API UInteractorComponent : public UActorComponent
{
	GENERATED_BODY()

	/// List of every interactable in range
	TArray<TWeakObjectPtr<UInteractableComponent>> Interactables;
	
	/// Interacts with the given actor on the server
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_Interact(AActor* Actor);

public:
	UInteractorComponent();

	/// Enters the feedback range of the given actor
	void EnterFeedback(const AActor* Actor);

	/// Exits the feedback range of the given actor
	void ExitFeedback(const AActor* Actor);
	
	/// Interacts with the given actor
	UFUNCTION(BlueprintCallable, Category=INTERACT)
	void Interact(AActor* Actor);
};

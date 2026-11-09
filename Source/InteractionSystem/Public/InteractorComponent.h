#pragma once

#include "CoreMinimal.h"
#include "InteractableComponent.h"
#include "Components/ActorComponent.h"
#include "InteractorComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class INTERACTIONSYSTEM_API UInteractorComponent : public UActorComponent
{
	GENERATED_BODY()

	/// List of every interactable in range
	TArray<TWeakObjectPtr<UInteractableComponent>> Interactables;

public:
	UInteractorComponent();

	/// Enters the feedback range of the given actor
	void EnterFeedback(AActor* Actor);

	/// Exits the feedback range of the given actor
	void ExitFeedback(AActor* Actor);
};

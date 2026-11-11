#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionRangeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActorEnterRange, AActor*, Actor);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActorExitRange, AActor*, Actor);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class INTERACTIONSYSTEM_API UInteractionRangeComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY()
	TObjectPtr<UPrimitiveComponent> RangeCollision;

	/// Called when a component enters the interaction range
	UFUNCTION()
	void OnComponentOverlapBegin(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	) const;

	/// Called when a component exits the interaction range
	UFUNCTION()
	void OnComponentOverlapEnd(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
	) const;

public:
	UInteractionRangeComponent();

	/// Initializes the collision range with the given collision
	void Initialize(UPrimitiveComponent* InRangeCollision);

	/// Called when an actor enters the interaction range
	UPROPERTY(BlueprintAssignable, Category="Interaction")
	FOnActorEnterRange OnActorEnterRange;

	/// Called when an actor exits the interaction range
	UPROPERTY(BlueprintAssignable, Category="Interaction")
	FOnActorExitRange OnActorExitRange;
};

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbilitySystemInterface.h"
#include "HealthAttributeSet.h"
#include "GameplayActor.generated.h"

UCLASS()
class TP_GAS_API AGameplayActor : public AActor, public IAbilitySystemInterface {
	GENERATED_BODY()

public:
	AGameplayActor();

	virtual void PostInitializeComponents() override;

protected:
	virtual void BeginPlay() override;

public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Health")
	void ReceiveHealthChanged(float NewHealth, float OldHealth);

	UFUNCTION(BlueprintImplementableEvent, Category = "Health")
	void ReceiveMaxHealthChanged(float MaxNewHealth, float MaxOldHealth);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UAbilitySystemComponent> AbilitySystem;

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	TObjectPtr<UHealthAttributeSet> HealthAttributeSet;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health", meta = (ClampMin = 0))
	float InitialHealth;
};
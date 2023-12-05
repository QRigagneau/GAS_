#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemComponent.h"
#include "HealthAttributeSet.h"
#include "AbilitySystemInterface.h"
#include "CharacterBase.generated.h"

UCLASS()
class TP_GAS_API ACharacterBase : public ACharacter, public IAbilitySystemInterface {
	GENERATED_BODY()

public:
	ACharacterBase();

	virtual void PostInitializeComponents() override;

	virtual void PossessedBy(AController* NewController) override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UAbilitySystemComponent> AbilitySystem;

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	TObjectPtr<UHealthAttributeSet> HealthAttributeSet;
};
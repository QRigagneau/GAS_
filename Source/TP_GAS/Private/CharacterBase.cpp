#include "CharacterBase.h"

ACharacterBase::ACharacterBase() {
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("Ability System"));
	AbilitySystem->SetIsReplicated(true);
	AbilitySystem->SetReplicationMode(EGameplayEffectReplicationMode::Full);
}

void ACharacterBase::PostInitializeComponents() {
	Super::PostInitializeComponents();

	HealthAttributeSet = NewObject<UHealthAttributeSet>(this);
	AbilitySystem->AddAttributeSetSubobject(HealthAttributeSet.Get());

	HealthAttributeSet->InitMaxHealth(100);
	HealthAttributeSet->InitHealth(100);
}

void ACharacterBase::PossessedBy(AController* NewController) {
	Super::PossessedBy(NewController);
	AbilitySystem->InitAbilityActorInfo(this, this);

}

UAbilitySystemComponent* ACharacterBase::GetAbilitySystemComponent() const {
	return AbilitySystem;
}

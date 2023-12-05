#include "GameplayActor.h"

AGameplayActor::AGameplayActor() {
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("Ability System"));
	AbilitySystem->SetIsReplicated(true);
	AbilitySystem->SetReplicationMode(EGameplayEffectReplicationMode::Full);
}

#define BIND_ATTRIBUTE_DELEGATE(AttributeSetName, AttributeName) AbilitySystem->GetGameplayAttributeValueChangeDelegate(##AttributeSetName##->Get##AttributeName##Attribute()) \
.AddLambda([this](const FOnAttributeChangeData& Data) { \
    const float NewValue = Data.NewValue; \
    const float OldValue = Data.OldValue; \
    Receive##AttributeName##Changed(NewValue, OldValue); \
});

void AGameplayActor::BeginPlay()
{
	AbilitySystem->InitAbilityActorInfo(this, this);

	

	BIND_ATTRIBUTE_DELEGATE(HealthAttributeSet, Health)
	BIND_ATTRIBUTE_DELEGATE(HealthAttributeSet, MaxHealth)

	Super::BeginPlay();
}

void AGameplayActor::PostInitializeComponents() {
	HealthAttributeSet = NewObject<UHealthAttributeSet>(this);
	AbilitySystem->AddAttributeSetSubobject(HealthAttributeSet.Get());

	HealthAttributeSet->InitMaxHealth(InitialHealth);
	HealthAttributeSet->InitHealth(InitialHealth);

	Super::PostInitializeComponents();
}

void AGameplayActor::BeginPlay() {
	AbilitySystem->InitAbilityActorInfo(this, this);
	Super::BeginPlay();
}

UAbilitySystemComponent* AGameplayActor::GetAbilitySystemComponent() const {
	return AbilitySystem;
}
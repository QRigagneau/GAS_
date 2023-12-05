#include "HealthAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

void UHealthAttributeSet::OnRep_Health(const FGameplayAttributeData & OldHealth) {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHealthAttributeSet, Health, OldHealth);
}

void UHealthAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHealthAttributeSet, MaxHealth, OldMaxHealth);
}

void UHealthAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UHealthAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UHealthAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
}

void UHealthAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) {
	if (Attribute == GetHealthAttribute()) {
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
	}
	else if (Attribute == GetMaxHealthAttribute()) {
		NewValue = FMath::Max(NewValue, 0.0f);
	}
}

void UHealthAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) {
	Super::PostGameplayEffectExecute(Data);

	const FGameplayAttribute Attribute = Data.EvaluatedData.Attribute;
	if (Attribute == GetHealthAttribute()) {
		SetHealth(FMath::Clamp(Attribute.GetNumericValue(this), 0.0f, GetMaxHealth()));
	}
	else if (Attribute == GetMaxHealthAttribute()) {
		SetMaxHealth(FMath::Max(Attribute.GetNumericValue(this), 0.0f));
	}
}

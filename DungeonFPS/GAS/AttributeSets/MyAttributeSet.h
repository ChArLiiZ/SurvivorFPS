// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "GameplayEffectExtension.h"
#include "MyAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

struct FGameplayEffectModCallbackData;

DECLARE_MULTICAST_DELEGATE_FourParams(FMyAttributeEvent, AActor* /*EffectInstigator*/, AActor* /*EffectCauser*/,
	const FGameplayEffectSpec& /*EffectSpec*/, float /*EffectMagnitude*/);
DECLARE_MULTICAST_DELEGATE_FiveParams(FMyAttributeDamageEvent, AActor* /*EffectInstigator*/, AActor* /*EffectCauser*/,
	const FGameplayTagContainer& /*GameplayTagContainer*/, float /*Damage*/, bool /*IsCrit*/);
/**
 * 
 */
UCLASS()
class DUNGEONFPS_API UMyAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

	UMyAttributeSet();

public:
	UPROPERTY(Category="Attributes", BlueprintReadOnly, ReplicatedUsing= OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, Health);
	UPROPERTY(Category="Attributes", BlueprintReadOnly, ReplicatedUsing= OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, MaxHealth);
	UPROPERTY(Category="Attributes", BlueprintReadOnly)
	FGameplayAttributeData InDamage;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, InDamage);

	UPROPERTY(Category="Attributes", BlueprintReadOnly)
	FGameplayAttributeData CritChance;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, CritChance);
	UPROPERTY(Category="Attributes", BlueprintReadOnly)
	FGameplayAttributeData CritDamage;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, CritDamage);
	UPROPERTY(Category="Attributes", BlueprintReadOnly)
	FGameplayAttributeData AllDmgMulti;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, AllDmgMulti);
	
	
	
	mutable FMyAttributeEvent OnOutOfHealth;
	mutable FMyAttributeDamageEvent OnDamageTaken;
	
	bool bOutOfHealth;

	

	
	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);

	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);

	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void ClampAttributeOnChange(const FGameplayAttribute& Attribute, float& NewValue) const;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;




	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};

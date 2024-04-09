// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "WeaponAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

struct FGameplayEffectModCallbackData;

DECLARE_MULTICAST_DELEGATE_FourParams(FMyAttributeEvent, AActor* /*EffectInstigator*/, AActor* /*EffectCauser*/,
	const FGameplayEffectSpec& /*EffectSpec*/, float /*EffectMagnitude*/);

/**
 * 
 */
UCLASS()
class DUNGEONFPS_API UWeaponAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

	UWeaponAttributeSet();

public:
	
	UPROPERTY(Category="Attributes", BlueprintReadOnly)
	FGameplayAttributeData Ammo;
	ATTRIBUTE_ACCESSORS(UWeaponAttributeSet, Ammo);
	UPROPERTY(Category="Attributes", BlueprintReadOnly)
	FGameplayAttributeData MaxAmmo;
	ATTRIBUTE_ACCESSORS(UWeaponAttributeSet, MaxAmmo);
	UPROPERTY(Category="Attributes", BlueprintReadOnly)
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(UWeaponAttributeSet, Damage);
	UPROPERTY(Category="Attributes", BlueprintReadOnly)
	FGameplayAttributeData RateOfFire;
	ATTRIBUTE_ACCESSORS(UWeaponAttributeSet, RateOfFire);
	UPROPERTY(Category="Attributes", BlueprintReadOnly)
	FGameplayAttributeData RecoilLevel;
	ATTRIBUTE_ACCESSORS(UWeaponAttributeSet, RecoilLevel);



	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void ClampAttributeOnChange(const FGameplayAttribute& Attribute, float& NewValue) const;
};

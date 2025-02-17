// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "EnemyAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

struct FGameplayEffectModCallbackData;

/**
 * 
 */
UCLASS()
class DUNGEONFPS_API UEnemyAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	UEnemyAttributeSet();

public:
	UPROPERTY(Category="Attributes", BlueprintReadOnly)
	FGameplayAttributeData Attack;
	ATTRIBUTE_ACCESSORS(UEnemyAttributeSet, Attack);
};

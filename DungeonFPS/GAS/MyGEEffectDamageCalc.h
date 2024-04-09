// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "MyGEEffectDamageCalc.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONFPS_API UMyGEEffectDamageCalc : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:

	UMyGEEffectDamageCalc();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};

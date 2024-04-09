// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyBFL.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONFPS_API UMyBFL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()


public:
	UFUNCTION(BlueprintCallable, Category="Calculations")
	static FHitResult FindClosestHitResult(const FVector Center, const TArray<FHitResult> HitResults, float& Distance);
	UFUNCTION(BlueprintCallable, Category="Calculations")
	static void CalBloodDecalTransform(const FHitResult HitResult, const float Radius, bool& CanSpawn, FTransform& SpawnTransform);
	UFUNCTION(BlueprintCallable, Category="Calculations", BlueprintPure)
	static void GetRandomItemWithWeights(const TArray<int> Weights, int& Index);
	
};

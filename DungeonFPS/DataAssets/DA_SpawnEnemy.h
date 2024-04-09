// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DungeonFPS/MyEnemy.h"
#include "Engine/DataAsset.h"
#include "DA_SpawnEnemy.generated.h"

/**
 * 
 */


USTRUCT(BlueprintType, Blueprintable)
struct FS_EnemySpawnInfo
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int SpawnWeight;
	
};
UCLASS(BlueprintType, Blueprintable)
class DUNGEONFPS_API UDA_SpawnEnemy : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<TSubclassOf<AMyEnemy>, FS_EnemySpawnInfo> EnemySpawnInfos;


	UFUNCTION(BlueprintCallable, BlueprintPure)
	void GetWeights(TArray<int>& Weights);
};

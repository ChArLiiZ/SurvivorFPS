// Fill out your copyright notice in the Description page of Project Settings.


#include "DA_SpawnEnemy.h"

void UDA_SpawnEnemy::GetWeights(TArray<int>& Weights)
{
	TArray<FS_EnemySpawnInfo> ValueArray;
	EnemySpawnInfos.GenerateValueArray(ValueArray);
	TArray<int> weights;
	for (FS_EnemySpawnInfo Values : ValueArray)
	{
		weights.Add(Values.SpawnWeight);
	}
	Weights = weights;
}

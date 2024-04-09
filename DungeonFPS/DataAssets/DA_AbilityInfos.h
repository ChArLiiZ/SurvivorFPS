// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Engine/DataAsset.h"
#include "DA_AbilityInfos.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType, Blueprintable)
struct FS_AbilityInfo
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Icon;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTagContainer  CooldownTag;
	
	
};

UCLASS(BlueprintType, Blueprintable)
class DUNGEONFPS_API UDA_AbilityInfos : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<TSubclassOf<UGameplayAbility>, FS_AbilityInfo> AbilityInfos;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyCharacter.h"
#include "GAS/AttributeSets/EnemyAttributeSet.h"
#include "MyEnemy.generated.h"

UCLASS()
class DUNGEONFPS_API AMyEnemy : public AMyCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyEnemy();

	UPROPERTY(Category="GAS", VisibleAnywhere, BlueprintReadOnly)
	UEnemyAttributeSet* EnemyAttributeSet;

	UPROPERTY(Category="Attacks", EditAnywhere, BlueprintReadWrite)
	TMap<UAnimMontage*, int> BasicAttackMontages;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};

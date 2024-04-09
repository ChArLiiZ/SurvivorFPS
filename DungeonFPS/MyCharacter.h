// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GAS/MyASC.h"
#include "GAS/AttributeSets/MyAttributeSet.h"
#include "MyCharacter.generated.h"

UCLASS()
class DUNGEONFPS_API AMyCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName WeaknessName;
	UPROPERTY(Category="GAS", EditAnywhere, BlueprintReadWrite)
	UMyASC* AbilitySystemComponent;
	UPROPERTY(Category="GAS", EditAnywhere, BlueprintReadWrite)
	UMyAttributeSet* AttributeSet;
	
	UPROPERTY(BlueprintReadWrite)
	bool IsDead = false;

	UPROPERTY(BlueprintReadWrite)
	FVector KnockBackDirection;
	UPROPERTY(BlueprintReadWrite)
	float KnockBackForce;



	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	

	virtual void InitializeAbilities();
	virtual void InitializeEffects();
	
	UPROPERTY(Category="GAS", EditDefaultsOnly, BlueprintReadWrite)
	TMap<UInputAction*, TSubclassOf<UGameplayAbility>> DefaultAbilities;
	UPROPERTY(Category="GAS", EditDefaultsOnly, BlueprintReadWrite)
	TArray<TSubclassOf<UGameplayEffect>> DefaultEffects;

	virtual void OnHealthChanged_ToDelegate(const FOnAttributeChangeData& Data);
	UFUNCTION(Category="GAS", BlueprintNativeEvent, BlueprintCallable)
	void OnHealthChanged(float NewValue, float OldValue);

	virtual void OnOutOfHealthChanged_ToDelegate(AActor* DamageInstigator, AActor* DamageCauser,
		const FGameplayEffectSpec& DamageEffectSpec, float DamageMagnitude);
	UFUNCTION(Category="GAS", BlueprintNativeEvent, BlueprintCallable)
	void OnOutOfHealthChanged(AActor* DamageInstigator, AActor* DamageCauser,
		const FGameplayEffectSpec& DamageEffectSpec, float DamageMagnitude);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnReceivedDamage(float DamageAmount);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Dead();

	virtual void PossessedBy(AController* NewController) override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	

	
};

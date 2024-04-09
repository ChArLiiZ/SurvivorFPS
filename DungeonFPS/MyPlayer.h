// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "MyCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputMappingContext.h"
#include "GAS/AttributeSets/WeaponAttributeSet.h"
#include "MyPlayer.generated.h"

class AWeaponBase;

UCLASS()
class DUNGEONFPS_API AMyPlayer : public AMyCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyPlayer();


	UPROPERTY(Category="Camera", EditAnywhere, BlueprintReadWrite)
	USpringArmComponent* SpringArm;
	UPROPERTY(Category="Camera", EditAnywhere, BlueprintReadWrite)
	UCameraComponent* Camera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* FireSpot;
	
	UPROPERTY(Category="Input", EditAnywhere, BlueprintReadOnly)
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(Category="Weapon", BlueprintReadWrite)
	AWeaponBase* Weapon_Equipped_1;
	UPROPERTY(Category="Weapon", BlueprintReadWrite)
	AWeaponBase* Weapon_Equipped_2;
	UPROPERTY(Category="Weapon", BlueprintReadWrite)
	AWeaponBase* Weapon_Using;

	UPROPERTY(Category="GAS", VisibleAnywhere, BlueprintReadOnly)
	UWeaponAttributeSet* WeaponAttributeSet;

	UPROPERTY(Category="Timers", BlueprintReadOnly)
	FTimerHandle SetWeaponAbilities_Timer;

	


	

	UFUNCTION(BlueprintNativeEvent)
	void Fire(const FInputActionValue& Value);

	UFUNCTION(Category="Weapon", BlueprintCallable)
	void EquipWeapon(AWeaponBase* Weapon);
	UFUNCTION(Category="Weapon", BlueprintCallable, BlueprintPure)
	bool IsUsingWeapon_1();
	UFUNCTION(Category="Weapon", BlueprintNativeEvent, BlueprintCallable)
	void SwitchWeapon();
	UFUNCTION(Category="Weapon")
	void SetAttributesFromWeapon() const;
	UFUNCTION(Category="Weapon", BlueprintNativeEvent, BlueprintCallable)
	void SetWeaponAbilities();
	UFUNCTION(Category="Weapon", BlueprintNativeEvent, BlueprintCallable)
	void ClearWeaponAbilities();

	UFUNCTION(Category="HUD", BlueprintNativeEvent)
	void HUD_FireEffects();

	virtual void OnAmmoChanged_ToDelegate(const FOnAttributeChangeData& Data);
	UFUNCTION(Category="GAS", BlueprintNativeEvent)
	void OnAmmoChanged(float NewValue, float OldValue);
	
	//virtual void OnRep_PlayerState() override;
	//virtual void PossessedBy(AController* NewController) override;
	


	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};

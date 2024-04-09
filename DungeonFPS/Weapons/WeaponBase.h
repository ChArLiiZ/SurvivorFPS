// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GameFramework/Actor.h"
#include "NiagaraFunctionLibrary.h"
#include "InputAction.h"
#include "DungeonFPS/GAS/MyASC.h"
#include "DungeonFPS/GAS/AttributeSets/WeaponAttributeSet.h"
#include "GameFramework/SpringArmComponent.h"
#include "WeaponBase.generated.h"

struct FGameplayAbilitySpecHandle;
class UGameplayAbility;
class AMyPlayer;
class UBillboardComponent;

UENUM(BlueprintType)
enum EWeaponTypes
{
	Pistol,
	AssaultRifle,
	Shotgun,
	SniperRifle,
	Katana
};


UCLASS()
class DUNGEONFPS_API AWeaponBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeaponBase();

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* Outline;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* VfxSpot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USpringArmComponent* SpringArm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Arrow;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBillboardComponent* PickUpButton;

	UPROPERTY(Category = "Attributes", EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EWeaponTypes> WeaponType;

	UPROPERTY(Category = "Attributes", BlueprintReadWrite)
	FName SlotName;
	UPROPERTY(Category = "Attributes", BlueprintReadWrite)
	USoundBase* FireSfx;
	UPROPERTY(Category = "Attributes", BlueprintReadWrite)
	UNiagaraSystem* FireVfx;
	UPROPERTY(Category= "Attributes", BlueprintReadWrite)
	float Ammo = 10.0;
	UPROPERTY(Category= "Attributes", BlueprintReadWrite)
	float MaxAmmo = 10.0;
	UPROPERTY(Category= "Attributes", BlueprintReadWrite)
	float Damage = 10.0;
	UPROPERTY(Category = "Attributes", BlueprintReadWrite)
	float RateOfFire = 2.0;
	UPROPERTY(Category = "Attributes", BlueprintReadWrite)
	float RecoilLevel = 1.0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FVector AimLocation;

	UPROPERTY(Category = "Recoil", BlueprintReadWrite)
	FTransform RecoilTransform;
	

	UPROPERTY(Category= "Attributes", EditDefaultsOnly, BlueprintReadOnly)
	UDataTable* DT_WeaponAttributes;
	
	
	UPROPERTY(BlueprintReadWrite)
	AMyPlayer* PlayerRef;
	
	UPROPERTY(Category="Animations", BlueprintReadWrite)
	UAnimMontage* Fire_Montage;
	UPROPERTY(Category="Animations", BlueprintReadWrite)
	UAnimMontage* Reload_Montage;

	UPROPERTY(Category="GAS", BlueprintReadWrite)
	TMap<UInputAction*, TSubclassOf<UGameplayAbility>> WeaponAbilities;
	UPROPERTY(Category="GAS", BlueprintReadWrite)
	TArray<FGameplayAbilitySpecHandle> WeaponAbilityHandles;
	UPROPERTY(Category="GAS", BlueprintReadWrite)
	TArray<TSubclassOf<UGameplayEffect>> WeaponEffects;
	
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void PlayReloadAnim(float PlayRate);

	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Fire_Effects();
	UFUNCTION(BlueprintNativeEvent)
	void Fire_Recoil();

	
	UFUNCTION(BlueprintNativeEvent)
	void InitializeAttributes();

	UFUNCTION(BlueprintCallable)
	void SetWeaponEquipped(AMyPlayer* Player, bool IsEquipped, bool IsUsing);

	

	
	
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};

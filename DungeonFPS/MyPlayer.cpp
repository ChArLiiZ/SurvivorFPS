// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayer.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Weapons/WeaponBase.h"


// Sets default values
AMyPlayer::AMyPlayer()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetMesh());
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	FireSpot = CreateDefaultSubobject<USceneComponent>(TEXT("FireSpot"));
	FireSpot->SetupAttachment(Camera);

	WeaponAttributeSet = CreateDefaultSubobject<UWeaponAttributeSet>(TEXT("WeaponAttributeSet"));

	
	

	
	
	
	
}

// Called to bind functionality to input
void AMyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		
	}
}

// Called when the game starts or when spawned
void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();

	if (const APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(WeaponAttributeSet->GetAmmoAttribute()).AddUObject(
		this, &AMyPlayer::OnAmmoChanged_ToDelegate);

	
	
}

// Called every frame
void AMyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}






void AMyPlayer::Fire_Implementation(const FInputActionValue& Value)
{
	
}

void AMyPlayer::OnAmmoChanged_ToDelegate(const FOnAttributeChangeData& Data)
{
	OnAmmoChanged(Data.NewValue, Data.OldValue);
	Weapon_Using->Ammo = Data.NewValue;
}

void AMyPlayer::OnAmmoChanged_Implementation(float NewValue, float OldValue)
{
}

void AMyPlayer::HUD_FireEffects_Implementation()
{
}


void AMyPlayer::EquipWeapon(AWeaponBase* Weapon)
{
	if (Weapon_Using && Weapon_Equipped_2)
	{
		Weapon_Using->SetWeaponEquipped(this, false, false);
	}
	
	if (Weapon_Equipped_2)
	{
		if (IsUsingWeapon_1())
		{
			Weapon_Equipped_1 = Weapon;
		}
		else
		{
			Weapon_Equipped_2 = Weapon;
		}

		Weapon->SetWeaponEquipped(this, true, true);
	
	}
	else if (!Weapon_Equipped_1)
	{
		Weapon_Equipped_1 = Weapon;
		Weapon->SetWeaponEquipped(this, true, true);
	}
	else
	{
		Weapon_Equipped_2 = Weapon;
		Weapon->SetWeaponEquipped(this, true, false);
		SwitchWeapon();
	}
	
	
	
}

void AMyPlayer::SetAttributesFromWeapon() const
{
	WeaponAttributeSet->SetMaxAmmo(Weapon_Using->MaxAmmo);
	WeaponAttributeSet->SetAmmo(Weapon_Using->Ammo);
	WeaponAttributeSet->SetDamage(Weapon_Using->Damage);
	WeaponAttributeSet->SetRateOfFire(Weapon_Using->RateOfFire);
	WeaponAttributeSet->SetRecoilLevel(Weapon_Using->RecoilLevel);
	
}

bool AMyPlayer::IsUsingWeapon_1()
{
	if (!Weapon_Using)
		return true;
	if (Weapon_Using == Weapon_Equipped_1)
		return true;
	return false;
}


void AMyPlayer::SetWeaponAbilities_Implementation()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue,"SetWeaponAbilities",  true);
	for (const auto& Ability : Weapon_Using->WeaponAbilities)
	{
		const FGameplayAbilitySpecHandle AbilityHandle =
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability.Value, 1, 0, this));
		AbilitySystemComponent->SetInputBinding(Ability.Key, AbilityHandle);
		Weapon_Using->WeaponAbilityHandles.Add(AbilityHandle);
	}
}

void AMyPlayer::ClearWeaponAbilities_Implementation()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue,"ClearWeaponAbilities",  true);
	for (const auto& AbilityHandle : Weapon_Using->WeaponAbilityHandles)
	{
		AbilitySystemComponent->ClearInputBinding(AbilityHandle);
		AbilitySystemComponent->ClearAbility(AbilityHandle);
	}
	Weapon_Using->WeaponAbilityHandles.Empty();
}

void AMyPlayer::SwitchWeapon_Implementation()
{
	/*
	if (IsUsingWeapon_1() && Weapon_Equipped_2)
	{
		Weapon_Using = Weapon_Equipped_2;
		Weapon_Equipped_2->SetActorHiddenInGame(false);
		Weapon_Equipped_1->SetActorHiddenInGame(true);
		
		ClearWeaponAbilities();
		if (SetWeaponAbilities_Timer.IsValid())
			GetWorldTimerManager().ClearTimer(SetWeaponAbilities_Timer);
		GetWorldTimerManager().SetTimer(SetWeaponAbilities_Timer, Weapon_Equipped_2, &AWeaponBase::SetWeaponAbilities, 0.1f, false);
		
	}
	else
	{
		Weapon_Using = Weapon_Equipped_1;
		Weapon_Equipped_1->SetActorHiddenInGame(false);
		Weapon_Equipped_2->SetActorHiddenInGame(true);
		ClearWeaponAbilities();
		if (SetWeaponAbilities_Timer.IsValid())
			GetWorldTimerManager().ClearTimer(SetWeaponAbilities_Timer);
		GetWorldTimerManager().SetTimer(SetWeaponAbilities_Timer, Weapon_Equipped_1, &AWeaponBase::SetWeaponAbilities, 0.1f, false);
		GetWorldTimerManager().PauseTimer(SetWeaponAbilities_Timer);
	}
	*/
	SetAttributesFromWeapon();
	bool foundAmmo;
	OnAmmoChanged(GetAbilitySystemComponent()->GetGameplayAttributeValue(WeaponAttributeSet->GetAmmoAttribute(), foundAmmo),
		GetAbilitySystemComponent()->GetGameplayAttributeValue(WeaponAttributeSet->GetMaxAmmoAttribute(), foundAmmo));
	
	
}















// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"

#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/BillboardComponent.h"
#include "DungeonFPS/MyPlayer.h"


// Sets default values
AWeaponBase::AWeaponBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	RootComponent = Mesh;
	Outline = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Outline"));
	Outline->SetCollisionResponseToAllChannels(ECR_Ignore);
	Outline->SetupAttachment(Mesh);
	Outline->SetBoundsScale(5);
	Outline->SetWorldScale3D(FVector(-1, -1, -1));
	VfxSpot = CreateDefaultSubobject<USceneComponent>(TEXT("FireSpot"));
	VfxSpot->SetupAttachment(Mesh);
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Mesh);
	Arrow = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(SpringArm);
	PickUpButton = CreateDefaultSubobject<UBillboardComponent>(TEXT("PickUpButton"));
	PickUpButton->SetupAttachment(SpringArm);
	
	
	
}


// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	InitializeAttributes();
	
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

void AWeaponBase::InitializeAttributes_Implementation()
{
	
}

void AWeaponBase::SetWeaponEquipped(AMyPlayer* Player, bool IsEquipped, bool IsUsing)
{
	PlayerRef = Player;
	if (IsEquipped)
	{
		
		Mesh->SetSimulatePhysics(false);
		Arrow->SetVisibility(false);
		PickUpButton->SetVisibility(false);
		AttachToComponent(PlayerRef->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, SlotName);
		if (IsUsing)
		{
			SetActorHiddenInGame(false);
			PlayerRef->Weapon_Using = this;
			PlayerRef->SetWeaponAbilities();
			bool foundAmmo;
			PlayerRef->SetAttributesFromWeapon();
			PlayerRef->OnAmmoChanged(PlayerRef->GetAbilitySystemComponent()->GetGameplayAttributeValue(PlayerRef->WeaponAttributeSet->GetAmmoAttribute(), foundAmmo),
				PlayerRef->GetAbilitySystemComponent()->GetGameplayAttributeValue(PlayerRef->WeaponAttributeSet->GetMaxAmmoAttribute(), foundAmmo));
		}
		else
		{
			SetActorHiddenInGame(true);
		}
	}
	else
	{
		SetActorHiddenInGame(false);
		Arrow->SetVisibility(true);
		PickUpButton->SetVisibility(true);
		DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		PlayerRef->ClearWeaponAbilities();
		Mesh->SetSimulatePhysics(true);
	}
}






void AWeaponBase::Fire_Effects_Implementation()
{
	UGameplayStatics::SpawnSoundAttached(FireSfx, VfxSpot, FName("None"), FVector::ZeroVector,
		FRotator::ZeroRotator, EAttachLocation::SnapToTarget);
	UNiagaraFunctionLibrary::SpawnSystemAttached(FireVfx, VfxSpot, FName("None"), 
		FVector::ZeroVector, FRotator::ZeroRotator,
		EAttachLocation::SnapToTarget, true,
		true, ENCPoolMethod::AutoRelease, true);
	PlayerRef->PlayAnimMontage(Fire_Montage);
	Fire_Recoil();
	PlayerRef->HUD_FireEffects();
}

void AWeaponBase::Fire_Recoil_Implementation()
{
}

void AWeaponBase::PlayReloadAnim_Implementation(float PlayRate)
{
	Mesh->PlayAnimation(Reload_Montage, false);
}















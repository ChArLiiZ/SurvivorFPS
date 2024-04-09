// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "AbilitySystemComponent.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetCollisionObjectType(ECC_PhysicsBody);
	GetMesh()->SetCollisionResponseToAllChannels(ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);

	AbilitySystemComponent = CreateDefaultSubobject<UMyASC>(TEXT("AbilitySystemComp"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UMyAttributeSet>(TEXT("AttributeSet"));

	

	
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	InitializeAbilities();

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHealthAttribute()).AddUObject(
		this, &AMyCharacter::OnHealthChanged_ToDelegate);

	AttributeSet->OnOutOfHealth.AddUObject(this, &AMyCharacter::OnOutOfHealthChanged_ToDelegate);
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

UAbilitySystemComponent* AMyCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AMyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	//GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Blue, "Possessed", true);

	if (!AbilitySystemComponent)
		return;

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	InitializeAbilities();
	InitializeEffects();
}

void UMyAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	if (Data.EvaluatedData.Attribute != GetInDamageAttribute())
		return;

	const float InDamageDone = GetInDamage();
	SetInDamage(0.0f);
	if (InDamageDone >= 0.0f)
	{
		const float NewHealth = GetHealth() - InDamageDone;
		SetHealth(FMath::Clamp(NewHealth, 0.0f, GetMaxHealth()));

		if (GetHealth() <= 0.0f && !bOutOfHealth)
		{
			if (OnOutOfHealth.IsBound())
			{
				const FGameplayEffectContextHandle& EffectContext = Data.EffectSpec.GetEffectContext();
				AActor* Instigator = EffectContext.GetOriginalInstigator();
				AActor* Causer = EffectContext.GetEffectCauser();
				OnOutOfHealth.Broadcast(Instigator, Causer, Data.EffectSpec, Data.EvaluatedData.Magnitude);
			}
		}
	}
}

void AMyCharacter::OnReceivedDamage_Implementation(float DamageAmount)
{
	
}

void AMyCharacter::OnOutOfHealthChanged_ToDelegate(AActor* DamageInstigator, AActor* DamageCauser,
	const FGameplayEffectSpec& DamageEffectSpec, float DamageMagnitude)
{
	OnOutOfHealthChanged(DamageInstigator, DamageCauser, DamageEffectSpec, DamageMagnitude);
}

void AMyCharacter::OnOutOfHealthChanged_Implementation(AActor* DamageInstigator, AActor* DamageCauser,
	const FGameplayEffectSpec& DamageEffectSpec, float DamageMagnitude)
{
	Dead();
}

void AMyCharacter::Dead_Implementation()
{
	IsDead = true;
}





void AMyCharacter::InitializeAbilities()
{
	if (!AbilitySystemComponent)
		return;

	for (const auto& Ability : DefaultAbilities)
	{
		const FGameplayAbilitySpecHandle AbilityHandle = AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(
			Ability.Value, 1, 0,this));

		AbilitySystemComponent->SetInputBinding(Ability.Key, AbilityHandle);
	}

	
}

void AMyCharacter::InitializeEffects()
{
	if (!AbilitySystemComponent)
		return;

	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	for (TSubclassOf<UGameplayEffect>& Effect : DefaultEffects)
	{
		FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(Effect, 1, EffectContext);
		if (SpecHandle.IsValid())
		{
			FActiveGameplayEffectHandle GEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
			
		}
	}
	
}

void AMyCharacter::OnHealthChanged_ToDelegate(const FOnAttributeChangeData& Data)
{
	OnHealthChanged(Data.NewValue, Data.OldValue);
}

void AMyCharacter::OnHealthChanged_Implementation(float NewValue, float OldValue)
{
	
}



// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGCharacterBase.h"
#include <Components/WidgetComponent.h>
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

#include "../../Ability/RPGAbilitySystemComponent.h"
#include "../../Ability/RPGAttributeSet.h"
#include "../../RPGGameState.h"
#include "MultiplayerRPG/UI/HealthyBar/UI_EnemyHealthyBar.h"
#include <MultiplayerRPG/Common/RPGMethodUntil.h>
#include "../../Component/FightComponent.h"

// Sets default values
ARPGCharacterBase::ARPGCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Initialize and attach the health bar widget.
	EnemyHealthyBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("EnemyHealthyBar"));
	EnemyHealthyBar->SetupAttachment(RootComponent);
	EnemyHealthyBar->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Initialize and replicate the FightComponent.
	FightComponent = CreateDefaultSubobject<UFightComponent>(TEXT("FightComponent"));
	FightComponent->SetIsReplicated(true);

	// Initialize and replicate the AbilitySystemComponent.
	AbilitySystemComponent = CreateDefaultSubobject<URPGAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);

	// Initialize the AttributeSet.
	RPGAttributeSet = CreateDefaultSubobject<URPGAttributeSet>(TEXT("RPGAttributeSet"));
}

// Handles health changes and updates the enemy health bar.
void ARPGCharacterBase::HandleHealthChanged_Implementation(float InHealthPercent)
{
	if (EnemyHealthyBar) 
	{
		// Update the health bar widget if valid.
		if (UUI_EnemyHealthyBar* HealthyBar = Cast<UUI_EnemyHealthyBar>(EnemyHealthyBar->GetUserWidgetObject())) 
		{
			HealthyBar->SetHealthPercent(InHealthPercent);
		}
	}
}

// Determines if the character is alive based on health.
bool ARPGCharacterBase::IsAlive()
{
	return RPGAttributeSet->GetHealth() > 0;
}

// Called when the game starts or when spawned
void ARPGCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	// Initialize the AbilitySystemComponent's actor info if on the server.
	if (AbilitySystemComponent && GetLocalRole() == ENetRole::ROLE_Authority)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}

	// Add the RPGAttributeSet to the AbilitySystemComponent's attributes.
	TArray<UAttributeSet*> RPGAttributeSets;
	RPGAttributeSets.Add(RPGAttributeSet);
	AbilitySystemComponent->SetSpawnedAttributes(RPGAttributeSets);

	// Update the health bar at the start.
	HandleHealthChanged(RPGAttributeSet->GetHealth() / RPGAttributeSet->GetMaxHealth());
}

// Called every frame
void ARPGCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARPGCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// Blueprint-exposed function to activate a skill using a GameplayTag
void ARPGCharacterBase::K2_ActiveSkill(FGameplayTag SkillName)
{
	ActiveSkill(SkillName);
}

void ARPGCharacterBase::SpawnDamageNum_Implementation(AActor* InActor, float InNum, const FLinearColor& InColor)
{
	RPGMethodUntil::SpawnDamageNum(InActor, InNum, InColor);
}

void ARPGCharacterBase::CallUpdateCooldownOnClient_Implementation(const FName& InTagName, float InCooldownValue)
{
	UpdateSkillCooldownDelegate.ExecuteIfBound(InTagName, InCooldownValue);
}

// Plays the "hit" animation or response for the character.
void ARPGCharacterBase::PlayHit_Implementation()
{
	GetFightComponent()->PlayHit();
}

// Plays the "death" animation or response for the character.
void ARPGCharacterBase::PlayDie_Implementation()
{
	GetFightComponent()->PlayDie();
}

// Activates a skill by its name provided as a string
void ARPGCharacterBase::ActiveSkillByString_Implementation(const FString& SkillName)
{
	GetFightComponent()->ActiveSkill(SkillName);
}

// Activates a skill by its name provided as a GameplayTag
void ARPGCharacterBase::ActiveSkill_Implementation(FGameplayTag SkillName)
{
	GetFightComponent()->ActiveSkill(SkillName);
}



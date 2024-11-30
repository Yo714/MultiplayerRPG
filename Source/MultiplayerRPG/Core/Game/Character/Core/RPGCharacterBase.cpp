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
#include "../../UI/HealthyBar/UI_EnemyHealthyBar.h"

// Sets default values
ARPGCharacterBase::ARPGCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<URPGAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);

	RPGAttributeSet = CreateDefaultSubobject<URPGAttributeSet>(TEXT("RPGAttributeSet"));

	EnemyHealthyBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("EnemyHealthyBar"));
	EnemyHealthyBar->SetupAttachment(RootComponent);
	EnemyHealthyBar->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ARPGCharacterBase::HandleHealthChanged(float InHealthPercent)
{
	if (EnemyHealthyBar) 
	{
		if (UUI_EnemyHealthyBar* HealthyBar = Cast<UUI_EnemyHealthyBar>(EnemyHealthyBar->GetUserWidgetObject())) 
		{
			HealthyBar->SetHealthPercent(InHealthPercent);
		}
	}
}

// Called when the game starts or when spawned
void ARPGCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	if (AbilitySystemComponent && GetLocalRole() == ENetRole::ROLE_Authority)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}

	TArray<UAttributeSet*> RPGAttributeSets;
	RPGAttributeSets.Add(Cast<UAttributeSet>(RPGAttributeSet));
	AbilitySystemComponent->SetSpawnedAttributes(RPGAttributeSets);

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


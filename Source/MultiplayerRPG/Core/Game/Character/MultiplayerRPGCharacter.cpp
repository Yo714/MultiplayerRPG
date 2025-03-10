// Copyright Epic Games, Inc. All Rights Reserved.

#include "MultiplayerRPGCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "../RPGGameState.h"
#include "Core/RPGCharacterBase.h"
#include "Components/WidgetComponent.h"
#include <TimerManager.h>
#include "../../../Common/RPGMethodUntil.h"
#include "../Component/FightComponent.h"
	

//DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AMultiplayerRPGCharacter

AMultiplayerRPGCharacter::AMultiplayerRPGCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)







}

// Updates the health UI and spawns a damage number
void AMultiplayerRPGCharacter::UpdateHealth_Implementation(float InPercent)
{
	// Bind and call the UI update function
	UpdateHealthProgress.ExecuteIfBound(InPercent);
	//RPGMethodUntil::SpawnDamageNum(this, RPGAttributeSet->GetDamage());
}

// Updates the mana 
void AMultiplayerRPGCharacter::UpdateMana_Implementation(float InPercent)
{
	// Bind and call the mana progress update function
	UpdateManaProgress.ExecuteIfBound(InPercent);
}

// Updates the stamina UI
void AMultiplayerRPGCharacter::UpdateStamina_Implementation(float InPercent)
{
	// Bind and call the stamina progress update function
	UpdateStaminaProgress.ExecuteIfBound(InPercent);
}

// Updates all progress bars (health, mana, stamina) at once
void AMultiplayerRPGCharacter::UpdateProgress()
{
	// Clear any existing timers
	GetWorldTimerManager().ClearTimer(UpdateProgressHandle);

	UpdateHealth(1);
	UpdateMana(1);
	UpdateStamina(1);
}

void AMultiplayerRPGCharacter::BeginPlay()
{

	Super::BeginPlay();

	// Set visibility of enemy health bar based on player role (server/client)
	if (GetLocalRole() != ENetRole::ROLE_Authority)
	{
		if (EnemyHealthyBar)
		{
			if (this == Cast<AMultiplayerRPGCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn()))
			{
				EnemyHealthyBar->SetVisibility(false);
			}
		}
	}

	// Set up timer to update progress on the server
	if (GetLocalRole() == ENetRole::ROLE_Authority)
	{
		GetWorld()->GetTimerManager().SetTimer(UpdateProgressHandle, this, &AMultiplayerRPGCharacter::UpdateProgress, 1.0, false, 0.3);
	}
}

// Handles combo attack press event
void AMultiplayerRPGCharacter::ComboAttackOnPressed_Implementation()
{
	GetFightComponent()->ComboAttackOnPressed();
}

// Handles combo attack release event
void AMultiplayerRPGCharacter::ComboAttackOnReleased_Implementation()
{
	GetFightComponent()->ComboAttackOnReleased();
}

// Server-side implementation of montage playing logic
void AMultiplayerRPGCharacter::K2_MontagePlayServer(UAnimMontage* InNewAnimMontage, float InPlayRate, float InTimeToStartMontageAt, bool bStopAllMontages, FName InStartSectionName)
{
	MontagePlayServer(InNewAnimMontage, InPlayRate, InTimeToStartMontageAt, bStopAllMontages, InStartSectionName);
}

void AMultiplayerRPGCharacter::MontagePlayServer_Implementation(UAnimMontage* InNewAnimMontage, float InPlayRate, float InTimeToStartMontageAt, bool bStopAllMontages, FName InStartSectionName)
{
	if (InNewAnimMontage) 
	{
		MontagePlayMulticast(InNewAnimMontage, InPlayRate, InTimeToStartMontageAt, bStopAllMontages, InStartSectionName);
	}
}

void AMultiplayerRPGCharacter::MontagePlayMulticast_Implementation(UAnimMontage* InNewAnimMontage, float InPlayRate, float InTimeToStartMontageAt, bool bStopAllMontages, FName InStartSectionName)
{
	if (GetMesh() && InNewAnimMontage)
	{
		if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance()) 
		{
			if (AnimInstance->Montage_Play(InNewAnimMontage, InPlayRate, EMontagePlayReturnType::MontageLength, InTimeToStartMontageAt, bStopAllMontages) > 0.f) 
			{
				if (InStartSectionName != NAME_None) 
				{
					AnimInstance->Montage_JumpToSection(InStartSectionName, InNewAnimMontage);
				}
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void AMultiplayerRPGCharacter::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void AMultiplayerRPGCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMultiplayerRPGCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMultiplayerRPGCharacter::Look);

		//ComboAttack
		PlayerInputComponent->BindAction("ComboAttack", IE_Pressed, this, &AMultiplayerRPGCharacter::ComboAttackOnPressed);
		PlayerInputComponent->BindAction("ComboAttack", IE_Released, this, &AMultiplayerRPGCharacter::ComboAttackOnReleased);
	}
	else
	{
		//UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AMultiplayerRPGCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AMultiplayerRPGCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

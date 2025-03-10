//Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Logging/LogMacros.h"
#include "../Ability/RPGAbilitySystemComponent.h"
#include "../Ability/RPGAttributeSet.h"
#include "Core/RPGCharacterBase.h"
#include "MultiplayerRPGCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

//DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);
class URPGAbilitySystemComponent;
class URPGAttributeSet;
class UGameplayAbility;

DECLARE_DELEGATE_OneParam(FUpdateProgressState, float)

UCLASS(config=Game)
class AMultiplayerRPGCharacter : public ARPGCharacterBase
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;


public: 
	AMultiplayerRPGCharacter();

	UFUNCTION(NetMulticast, Unreliable)
	void UpdateHealth(float InPercent);
	UFUNCTION(NetMulticast, Unreliable)
	void UpdateMana(float InPercent);
	UFUNCTION(NetMulticast, Unreliable)
	void UpdateStamina(float InPercent);

	FUpdateProgressState UpdateHealthProgress;
	FUpdateProgressState UpdateManaProgress;
	FUpdateProgressState UpdateStaminaProgress;

private:
	FTimerHandle UpdateProgressHandle;
protected:
	UFUNCTION()
	void UpdateProgress();


protected:
	void BeginPlay();


public:
	UFUNCTION(Server, Reliable)
	void ComboAttackOnPressed();

	UFUNCTION(Server, Reliable)
	void ComboAttackOnReleased();

	UFUNCTION(BlueprintCallable)
	void K2_MontagePlayServer(UAnimMontage* InNewAnimMontage, float InPlayRate = 1.0f, float InTimeToStartMontageAt = 0.f, bool bStopAllMontages = true, FName InStartSectionName = NAME_None);

	UFUNCTION(Server, UnReliable)
	void MontagePlayServer(UAnimMontage* InNewAnimMontage, float InPlayRate, float InTimeToStartMontageAt = 0.f, bool bStopAllMontages = true, FName InStartSectionName = NAME_None);

	UFUNCTION(NetMulticast, UnReliable)
	void MontagePlayMulticast(UAnimMontage* InNewAnimMontage, float InPlayRate, float InTimeToStartMontageAt = 0.f, bool bStopAllMontages = true, FName InStartSectionName = NAME_None);














protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
			

protected:

	virtual void NotifyControllerChanged() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};


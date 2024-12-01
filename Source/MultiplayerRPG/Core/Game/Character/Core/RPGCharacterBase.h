// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../../Ability/RPGAbilitySystemComponent.h"
#include "../../Ability/RPGAttributeSet.h"
#include "RPGCharacterBase.generated.h"

class URPGAbilitySystemComponent;
class URPGAttributeSet;
class UGameplayAbility;
class UWidgetComponent;
UCLASS()
class MULTIPLAYERRPG_API ARPGCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	//GAS
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = RPGCharacter, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<URPGAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = RPGCharacter, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<URPGAttributeSet> RPGAttributeSet;

	UPROPERTY(Category = RPGCharacterBase, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* EnemyHealthyBar;


public:
	// Sets default values for this character's properties
	ARPGCharacterBase();

	FGameplayAbilitySpecHandle RegisterGameAbility(TArray<UGameplayAbility*> InAbilities);

	UFUNCTION(NetMulticast, Unreliable)
	virtual void HandleHealthChanged(float InHealthPercent);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


protected:
	TMap<FName, FGameplayAbilitySpecHandle> Skills;

};

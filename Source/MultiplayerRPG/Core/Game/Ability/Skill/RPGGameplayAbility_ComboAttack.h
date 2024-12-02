// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../RPGGameplayAbility.h"
#include "RPGGameplayAbility_ComboAttack.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERRPG_API URPGGameplayAbility_ComboAttack : public URPGGameplayAbility
{
	GENERATED_BODY()
	
public:
	URPGGameplayAbility_ComboAttack();

	virtual void ActivateAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData);
	
	
	
};

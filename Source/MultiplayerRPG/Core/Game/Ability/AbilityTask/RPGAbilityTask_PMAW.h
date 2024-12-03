// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "RPGAbilityTask_PMAW.generated.h"

// Delegate for broadcasting damage events with an associated tag and event data.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMontageWaitSimpleForDamageEventDelegate, FGameplayTag, EventTag, FGameplayEventData, EventData);
/**
 * 
 */
UCLASS()
class MULTIPLAYERRPG_API URPGAbilityTask_PMAW : public UAbilityTask_PlayMontageAndWait
{
	GENERATED_BODY()
	
public:
	URPGAbilityTask_PMAW();

	UPROPERTY(BlueprintAssignable)
	FMontageWaitSimpleForDamageEventDelegate DamageEventRecived;

	virtual void Activate() override;
	virtual void OnDestroy(bool AbilityEnded) override;

	static URPGAbilityTask_PMAW* CreatePMAWDamegeEventProxy(
		UGameplayAbility* OwningAbility,
		FName TaskInstanceName,
		UAnimMontage* MontageToPlay,
		FGameplayTagContainer InEventTags,
		float Rate = 1.f,
		FName StartSection = NAME_None,
		bool bStopWhenAbilityEnds = true,
		float AnimRootMotionTranslationScale = 1.f,
		float StartTimeSeconds = 0.f);

private:
	void OnDamageGameplayEvent(FGameplayTag InGameplayTag, const FGameplayEventData* Payload);

private:
	FDelegateHandle EventHandle;

private:
	UPROPERTY()
	FGameplayTagContainer EventTags;
};

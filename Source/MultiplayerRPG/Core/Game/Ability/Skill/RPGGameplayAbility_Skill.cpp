// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGGameplayAbility_Skill.h"
#include "../../Character/MultiplayerRPGCharacter.h"


URPGGameplayAbility_Skill::URPGGameplayAbility_Skill()
{
}

void URPGGameplayAbility_Skill::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		return;
	}

	if (AMultiplayerRPGCharacter* Character = Cast<AMultiplayerRPGCharacter>(ActorInfo->OwnerActor))
	{
		if (PlayMontage(*FString::FromInt(0)))
		{
		}
	}
}

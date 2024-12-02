// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGGameplayAbility_ComboAttack.h"
#include "../../Character/MultiplayerRPGCharacter.h"

URPGGameplayAbility_ComboAttack::URPGGameplayAbility_ComboAttack()
{
}

void URPGGameplayAbility_ComboAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		return;
	}

	if (AMultiplayerRPGCharacter* InCharacter = Cast<AMultiplayerRPGCharacter>(ActorInfo->OwnerActor))
	{
		if (PlayMontage(*FString::FromInt(InCharacter->GetFightComponent()->GetComboCheck()->ComboIndex)))
		{
			UE_LOG(LogTemp, Log, TEXT("URPGGameplayAbility_ComboAttack %i"), InCharacter->GetFightComponent()->GetComboCheck()->ComboIndex);
		}
	}
}

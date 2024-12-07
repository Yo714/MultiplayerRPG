// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGGameplayAbility_Skill.h"
#include "../../Character/MultiplayerRPGCharacter.h"


URPGGameplayAbility_Skill::URPGGameplayAbility_Skill()
{
}

// Activates the skill ability.
void URPGGameplayAbility_Skill::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	//Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	// Attempt to commit the ability (e.g., apply cooldown, spend resources).
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		return;
	}

	// Cast the owner actor to AMultiplayerRPGCharacter to ensure it has the expected type.
	if (AMultiplayerRPGCharacter* Character = Cast<AMultiplayerRPGCharacter>(ActorInfo->OwnerActor))
	{
		CallUpdateCooldownOnClient();
		if (PlayMontage(*FString::FromInt(0)))
		{
		}
	}
}

void URPGGameplayAbility_Skill::CallUpdateCooldownOnClient()
{
	if (UGameplayEffect* InCooldownGA = GetCooldownGameplayEffect())
	{
		float CDValue = 0.f;
		if (InCooldownGA->DurationMagnitude.GetStaticMagnitudeIfPossible(GetAbilityLevel(), CDValue) && CDValue != 0.f)
		{
			if (ARPGCharacterBase* InCharacterBase = Cast<ARPGCharacterBase>(GetActorInfo().OwnerActor)) 
			{
				InCharacterBase->CallUpdateCooldownOnClient(*AbilityTags.ToStringSimple(), CDValue);
			}
		}
	}
}

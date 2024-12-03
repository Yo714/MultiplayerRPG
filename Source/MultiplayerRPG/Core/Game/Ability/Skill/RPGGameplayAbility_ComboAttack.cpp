// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGGameplayAbility_ComboAttack.h"
#include "../../Character/MultiplayerRPGCharacter.h"

URPGGameplayAbility_ComboAttack::URPGGameplayAbility_ComboAttack()
{
}

// Activates the combo attack ability.
void URPGGameplayAbility_ComboAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	// Attempt to commit the ability (e.g., apply cooldown, spend resources).
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		return;
	}

	// Cast the owner actor to AMultiplayerRPGCharacter to access character-specific functionality.
	if (AMultiplayerRPGCharacter* InCharacter = Cast<AMultiplayerRPGCharacter>(ActorInfo->OwnerActor))
	{
		// Play the montage corresponding to the current combo index.
		if (PlayMontage(*FString::FromInt(InCharacter->GetFightComponent()->GetComboCheck()->ComboIndex)))
		{
			UE_LOG(LogTemp, Log, TEXT("URPGGameplayAbility_ComboAttack %i"), InCharacter->GetFightComponent()->GetComboCheck()->ComboIndex);
		}
	}
}

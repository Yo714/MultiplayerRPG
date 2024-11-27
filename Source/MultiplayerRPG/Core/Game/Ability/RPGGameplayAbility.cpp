// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGGameplayAbility.h"
#include "MultiplayerRPG/MultiplayerRPGCharacter.h"
#include "AbilityTask/RPGAbilityTask_PMAW.h"


URPGGameplayAbility::URPGGameplayAbility()
{

}

void URPGGameplayAbility::OnCompleted()
{
	K2_OnCompleted();
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void URPGGameplayAbility::OnBlendOut()
{
	K2_OnBlendOut();
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void URPGGameplayAbility::OnInterrupted()
{
	K2_OnInterrupted();
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void URPGGameplayAbility::OnCancelled()
{
	K2_OnCancelled();
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void URPGGameplayAbility::OnDamageGameplayEvent(FGameplayTag InGameplayTag, FGameplayEventData Payload)
{
	UE_LOG(LogTemp, Log, TEXT("URPGGameplayAbility::OnDamageGameplayEvent"));
}

void URPGGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
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

void URPGGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

UAbilityTask_PlayMontageAndWait* URPGGameplayAbility::CreatePlayMontageAngWaitProxy(FName TaskInstanceName, UAnimMontage* InMontageToPlay, float Rate, FName StartSection, bool bStopWhenAbilityEnds, float AnimRootMotionTranslationScale, float StartTimeSeconds)
{
	URPGAbilityTask_PMAW* InWait = URPGAbilityTask_PMAW::CreatePMAWDamegeEventProxy(
		this,
		TaskInstanceName,
		InMontageToPlay,
		AbilityTags,
		Rate,
		StartSection,
		bStopWhenAbilityEnds,
		AnimRootMotionTranslationScale,
		StartTimeSeconds);

	if (InWait) 
	{
		InWait->OnCompleted.AddDynamic(this, &URPGGameplayAbility::OnCompleted);
		InWait->OnBlendOut.AddDynamic(this, &URPGGameplayAbility::OnBlendOut);
		InWait->OnCancelled.AddDynamic(this, &URPGGameplayAbility::OnCancelled);
		InWait->OnInterrupted.AddDynamic(this, &URPGGameplayAbility::OnInterrupted);
		InWait->DamageEventRecived.AddDynamic(this, &URPGGameplayAbility::OnDamageGameplayEvent);

		InWait->Activate();

		return InWait;
	}

	return nullptr;
}

UAbilityTask_PlayMontageAndWait* URPGGameplayAbility::PlayMontage(FName StartSection)
{
	return CreatePlayMontageAngWaitProxy(NAME_None, MontageToPlay, 1.f, StartSection);
}

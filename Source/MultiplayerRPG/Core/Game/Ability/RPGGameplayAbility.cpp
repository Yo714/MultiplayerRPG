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
	FGameplayAbilityTargetData_ActorArray* NewTargetData_ActorArray = new FGameplayAbilityTargetData_ActorArray();
	const AActor* InstigatorActor = Payload.Instigator.Get();
	NewTargetData_ActorArray->TargetActorArray.Add(const_cast<AActor*>(InstigatorActor));

	FGameplayAbilityTargetDataHandle TargetHandleData;
	TargetHandleData.Add(NewTargetData_ActorArray);

	for (auto& Tmp : EffectMap) 
	{
		FGameplayEffectSpecHandle NewHandle = GetAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(
			Tmp.Value, 1, MakeEffectContext(CurrentSpecHandle, CurrentActorInfo));

		if (NewHandle.IsValid()) 
		{
			FGameplayAbilitySpec* AbilitySpec = GetAbilitySystemComponentFromActorInfo()->FindAbilitySpecFromHandle(CurrentSpecHandle);
			ApplyAbilityTagsToGameplayEffectSpec(*NewHandle.Data.Get(), AbilitySpec);
			if (AbilitySpec) 
			{
				NewHandle.Data->SetByCallerTagMagnitudes = AbilitySpec->SetByCallerTagMagnitudes;
			}
		}

		TArray<FActiveGameplayEffectHandle> ActiveGameplayEffectHandles = K2_ApplyGameplayEffectSpecToTarget(NewHandle, TargetHandleData);
	}
}

void URPGGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	//Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	//if (!CommitAbility(Handle, ActorInfo, ActivationInfo)) 
	//{
	//	return;
	//}


	if (!CommitAbilityCooldown(Handle, ActorInfo, ActivationInfo, true)) 
	{
		return;
	}
	
	if (AMultiplayerRPGCharacter* Character = Cast<AMultiplayerRPGCharacter>(ActorInfo->OwnerActor))
	{
		if (PlayMontage(*FString::FromInt(0)))
		{
		}
	}

	//if (TriggerEventData && bHasBlueprintActivateFromEvent)
	//{
	//	// A Blueprinted ActivateAbility function must call CommitAbility somewhere in its execution chain.
	//	K2_ActivateAbilityFromEvent(*TriggerEventData);
	//}
	//else if (bHasBlueprintActivate)
	//{
	//	// A Blueprinted ActivateAbility function must call CommitAbility somewhere in its execution chain.
	//	K2_ActivateAbility();
	//}
	//else if (bHasBlueprintActivateFromEvent)
	//{
	//	//UE_LOG(LogAbilitySystem, Warning, TEXT("Ability %s expects event data but none is being supplied. Use 'Activate Ability' instead of 'Activate Ability From Event' in the Blueprint."), *GetName());
	//	constexpr bool bReplicateEndAbility = false;
	//	constexpr bool bWasCancelled = true;
	//	EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	//}
	//else
	//{
	//	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	//	{
	//		if (AMultiplayerRPGCharacter* Character = Cast<AMultiplayerRPGCharacter>(ActorInfo->OwnerActor))
	//		{
	//			if (PlayMontage(*FString::FromInt(0)))
	//			{
	//			}
	//		}
	//	}
	//}

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

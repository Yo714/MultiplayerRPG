// Fill out your copyright notice in the Description page of Project Settings.

#include "RPGAbilityTask_PMAW.h"
#include <Abilities/Tasks/AbilityTask.h>
#include <AbilitySystemGlobals.h>
#include "../RPGAbilitySystemComponent.h"


URPGAbilityTask_PMAW::URPGAbilityTask_PMAW()
{

}

void URPGAbilityTask_PMAW::Activate()
{
	if (Ability == nullptr)
	{
		return;
	}

	if (RPGAbilitySystemComponent)
	{
		const FGameplayAbilityActorInfo* ActorInfo = Ability->GetCurrentActorInfo();
		UAnimInstance* AnimInstance = ActorInfo->GetAnimInstance();

		if (AnimInstance != nullptr)
		{
			EventHandle = RPGAbilitySystemComponent->AddGameplayEventTagContainerDelegate(
				EventTags,
				FGameplayEventTagMulticastDelegate::FDelegate::CreateUObject(this, &URPGAbilityTask_PMAW::OnDamageGameplayEvent));
		}
	}

	Super::Activate();
}

void URPGAbilityTask_PMAW::OnDestroy(bool AbilityEnded)
{
	if (RPGAbilitySystemComponent)
	{
		RPGAbilitySystemComponent->RemoveGameplayEventTagContainerDelegate(EventTags, EventHandle);
	}

	Super::OnDestroy(AbilityEnded);
}

URPGAbilityTask_PMAW* URPGAbilityTask_PMAW::CreatePMAWDamegeEventProxy(UGameplayAbility* OwningAbility, FName TaskInstanceName, UAnimMontage* MontageToPlay, FGameplayTagContainer InEventTags, float Rate, FName StartSection, bool bStopWhenAbilityEnds, float AnimRootMotionTranslationScale, float StartTimeSeconds)
{
	UAbilitySystemGlobals::NonShipping_ApplyGlobalAbilityScaler_Rate(Rate);

	URPGAbilityTask_PMAW* MyObj = NewAbilityTask<URPGAbilityTask_PMAW>(OwningAbility, TaskInstanceName);
	MyObj->MontageToPlay = MontageToPlay;
	MyObj->Rate = Rate;
	MyObj->StartSection = StartSection;
	MyObj->AnimRootMotionTranslationScale = AnimRootMotionTranslationScale;
	MyObj->bStopWhenAbilityEnds = bStopWhenAbilityEnds;
	MyObj->StartTimeSeconds = StartTimeSeconds;
	MyObj->EventTags = InEventTags;

	return MyObj;
}

void URPGAbilityTask_PMAW::OnDamageGameplayEvent(FGameplayTag InGameplayTag, const FGameplayEventData* Payload)
{
	if (ShouldBroadcastAbilityTaskDelegates()) 
	{
		FGameplayEventData EventData = *Payload;
		EventData.EventTag = InGameplayTag;

		DamageEventRecived.Broadcast(InGameplayTag, EventData);
	}

}

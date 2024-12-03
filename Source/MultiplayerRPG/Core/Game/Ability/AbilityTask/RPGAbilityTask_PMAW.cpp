// Fill out your copyright notice in the Description page of Project Settings.

#include "RPGAbilityTask_PMAW.h"
#include <Abilities/Tasks/AbilityTask.h>
#include <AbilitySystemGlobals.h>
#include "../RPGAbilitySystemComponent.h"


URPGAbilityTask_PMAW::URPGAbilityTask_PMAW()
{

}

// Activate the task and start listening for gameplay events.
void URPGAbilityTask_PMAW::Activate()
{
	if (Ability == nullptr)
	{
		return;
	}

	if (AbilitySystemComponent.IsValid())
	{
		// Get the animation instance from the actor info.
		const FGameplayAbilityActorInfo* ActorInfo = Ability->GetCurrentActorInfo();
		UAnimInstance* AnimInstance = ActorInfo->GetAnimInstance();

		if (AnimInstance != nullptr)
		{
			// Register a delegate for gameplay events associated with the specified tags.
			EventHandle = AbilitySystemComponent->AddGameplayEventTagContainerDelegate(
				EventTags,
				FGameplayEventTagMulticastDelegate::FDelegate::CreateUObject(this, &URPGAbilityTask_PMAW::OnDamageGameplayEvent));
		}
	}

	Super::Activate();
}

// Called when the task is destroyed to clean up resources.
void URPGAbilityTask_PMAW::OnDestroy(bool AbilityEnded)
{
	if (AbilitySystemComponent.IsValid())
	{
		// Remove the registered gameplay event delegate.
		AbilitySystemComponent->RemoveGameplayEventTagContainerDelegate(EventTags, EventHandle);
	}

	Super::OnDestroy(AbilityEnded);
}

// Factory method for creating an instance of this ability task.
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

// Callback for handling gameplay events when they occur.
void URPGAbilityTask_PMAW::OnDamageGameplayEvent(FGameplayTag InGameplayTag, const FGameplayEventData* Payload)
{
	if (ShouldBroadcastAbilityTaskDelegates()) 
	{
		FGameplayEventData EventData = *Payload;
		EventData.EventTag = InGameplayTag;

		DamageEventRecived.Broadcast(InGameplayTag, EventData);
	}

}

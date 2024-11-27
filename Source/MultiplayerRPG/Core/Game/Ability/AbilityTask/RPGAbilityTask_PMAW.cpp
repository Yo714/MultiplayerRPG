// Fill out your copyright notice in the Description page of Project Settings.


#include "../RPGAbilitySystemComponent.h"
#include "RPGAbilityTask_PMAW.h"
#include <Abilities/Tasks/AbilityTask.h>
#include <AbilitySystemGlobals.h>


URPGAbilityTask_PMAW::URPGAbilityTask_PMAW()
{
}

void URPGAbilityTask_PMAW::Activate()
{
	//if (!Ability)
	//{
	//	return;
	//}

	//// 获取技能的 ActorInfo
	//const FGameplayAbilityActorInfo* ActorInfo = Ability->GetCurrentActorInfo();
	//if (!ActorInfo)
	//{
	//	return;
	//}

	//// 从 ActorInfo 获取 AbilitySystemComponent
	//UAbilitySystemComponent* ASC = ActorInfo->AbilitySystemComponent.Get();
	//if (!ASC)
	//{
	//	return;
	//}

	//// 检查 AnimInstance 是否存在
	//UAnimInstance* AnimInstance = ActorInfo->GetAnimInstance();
	//if (!AnimInstance)
	//{
	//	return;
	//}

	//// 设置事件代理
	//EventHandle = ASC->AddGameplayEventTagContainerDelegate(
	//	FGameplayTagContainer(),
	//	FGameplayEventTagMulticastDelegate::FDelegate::CreateUObject(this, &URPGAbilityTask_PMAW::OnDamageGameplayEvent)
	//);

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
				FGameplayTagContainer(),
				FGameplayEventTagMulticastDelegate::FDelegate::CreateUObject(this, &URPGAbilityTask_PMAW::OnDamageGameplayEvent));
		}
	}

	Super::Activate();
}

void URPGAbilityTask_PMAW::OnDestroy(bool AbilityEnded)
{
	//if (UAbilitySystemComponent* ASC = AbilitySystemComponent.Get())
	//{
	//	ASC->RemoveGameplayEventTagContainerDelegate(EventTags, EventHandle);
	//}

	//Super::OnDestroy(AbilityEnded);
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

	//if (OwningAbility)
	//{
	//	const FGameplayAbilityActorInfo* ActorInfo = OwningAbility->GetCurrentActorInfo();
	//	if (ActorInfo)
	//	{
	//		MyObj->AbilitySystemComponent = ActorInfo->AbilitySystemComponent.Get();
	//	}
	//}

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

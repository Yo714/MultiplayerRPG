// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyState_CheckCombo.h"
#include "../Component/FightComponent.h"
#include "../Character/MultiplayerRPGCharacter.h"

UAnimNotifyState_CheckCombo::UAnimNotifyState_CheckCombo() 
{

}

void UAnimNotifyState_CheckCombo::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	if (MeshComp->GetOuter() && MeshComp->GetOuter()->GetWorld() && MeshComp->GetOuter()->GetWorld()->IsNetMode(NM_DedicatedServer))
	{
		if (AMultiplayerRPGCharacter* InCharacter = Cast<AMultiplayerRPGCharacter>(MeshComp->GetOuter()))
		{
			InCharacter->GetFightComponent()->GetComboCheck()->bShortPress = false;
			InCharacter->GetFightComponent()->GetComboCheck()->UpdateComboIndex();
			UE_LOG(LogTemp, Log, TEXT("UpdateComboIndex NotifyBegin %i"), InCharacter->GetFightComponent()->GetComboCheck()->ComboIndex);
		}
	}
}

void UAnimNotifyState_CheckCombo::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);
}

void UAnimNotifyState_CheckCombo::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	if (MeshComp->GetOuter() && MeshComp->GetOuter()->GetWorld() && MeshComp->GetOuter()->GetWorld()->IsNetMode(NM_DedicatedServer))
	{
		if (AMultiplayerRPGCharacter* InCharacter = Cast<AMultiplayerRPGCharacter>(MeshComp->GetOuter()))
		{
			if ((InCharacter->GetFightComponent()->GetComboCheck()->bLongPress || InCharacter->GetFightComponent()->GetComboCheck()->bShortPress))
			{
				InCharacter->ActiveSkillByString("Character.Skill.ComboAttack");

				UE_LOG(LogTemp, Log, TEXT("UpdateComboIndex NotifyEnd %i"), InCharacter->GetFightComponent()->GetComboCheck()->ComboIndex);
			}
		}
	}
}

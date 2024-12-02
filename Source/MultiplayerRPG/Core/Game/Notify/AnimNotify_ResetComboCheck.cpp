// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_ResetComboCheck.h"
#include "../Character/MultiplayerRPGCharacter.h"
#include "../Component/FightComponent.h"

UAnimNotify_ResetComboCheck::UAnimNotify_ResetComboCheck()
{
}

FString UAnimNotify_ResetComboCheck::GetNotifyName_Implementation() const
{
	return Super::GetNotifyName_Implementation();
}

void UAnimNotify_ResetComboCheck::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if (AMultiplayerRPGCharacter* Character = Cast<AMultiplayerRPGCharacter>(MeshComp->GetOuter()))
	{
		Character->GetFightComponent()->GetComboCheck()->Reset();
	}
}

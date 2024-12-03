// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_ResetComboCheck.h"
#include "../Character/MultiplayerRPGCharacter.h"
#include "../Component/FightComponent.h"

UAnimNotify_ResetComboCheck::UAnimNotify_ResetComboCheck()
{
}

// Returns the name of this animation notify, typically shown in the animation editor
FString UAnimNotify_ResetComboCheck::GetNotifyName_Implementation() const
{
	return Super::GetNotifyName_Implementation();
}

// This method is called when the animation notify is triggered during the animation
void UAnimNotify_ResetComboCheck::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	// Ensure the MeshComp has an associated character (this is the character or entity)
	if (AMultiplayerRPGCharacter* Character = Cast<AMultiplayerRPGCharacter>(MeshComp->GetOuter()))
	{
		// Access the FightComponent and reset the combo check to the initial state
		Character->GetFightComponent()->GetComboCheck()->Reset();
	}
}

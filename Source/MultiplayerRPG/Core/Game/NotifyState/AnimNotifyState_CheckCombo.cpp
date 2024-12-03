// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyState_CheckCombo.h"
#include "../Component/FightComponent.h"
#include "../Character/MultiplayerRPGCharacter.h"

UAnimNotifyState_CheckCombo::UAnimNotifyState_CheckCombo() 
{

}

// Called when the animation state begins (at the start of the animation state)
void UAnimNotifyState_CheckCombo::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	// Ensure we are on the server side (in a networked game) before processing combo logic
	if (MeshComp->GetOuter() && MeshComp->GetOuter()->GetWorld() && MeshComp->GetOuter()->GetWorld()->IsNetMode(NM_DedicatedServer))
	{
		// Cast the outer actor to AMultiplayerRPGCharacter (the character the animation belongs to)
		if (AMultiplayerRPGCharacter* InCharacter = Cast<AMultiplayerRPGCharacter>(MeshComp->GetOuter()))
		{
			// Reset short press state and update the combo index
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

// Called when the animation state ends (at the end of the animation state)
void UAnimNotifyState_CheckCombo::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	// Ensure we are on the server side (in a networked game) before processing combo 
	if (MeshComp->GetOuter() && MeshComp->GetOuter()->GetWorld() && MeshComp->GetOuter()->GetWorld()->IsNetMode(NM_DedicatedServer))
	{
		// Cast the outer actor to AMultiplayerRPGCharacter (the character the animation belongs to)
		if (AMultiplayerRPGCharacter* InCharacter = Cast<AMultiplayerRPGCharacter>(MeshComp->GetOuter()))
		{
			// Check if the combo input was either a short press or a long press
			if ((InCharacter->GetFightComponent()->GetComboCheck()->bLongPress || InCharacter->GetFightComponent()->GetComboCheck()->bShortPress))
			{
				// Trigger the combo attack skill if the combo condition is met
				InCharacter->ActiveSkillByString("Character.Skill.ComboAttack");

				UE_LOG(LogTemp, Log, TEXT("UpdateComboIndex NotifyEnd %i"), InCharacter->GetFightComponent()->GetComboCheck()->ComboIndex);
			}
		}
	}
}

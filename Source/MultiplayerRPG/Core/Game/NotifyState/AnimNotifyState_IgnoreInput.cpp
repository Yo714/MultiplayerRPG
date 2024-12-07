// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyState_IgnoreInput.h"
#include "GameFramework/Character.h"

UAnimNotifyState_IgnoreInput::UAnimNotifyState_IgnoreInput()
{
}

void UAnimNotifyState_IgnoreInput::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	if (ACharacter* InCharacter = Cast<ACharacter>(MeshComp->GetOuter()))
	{
		if (InCharacter->GetWorld()->IsNetMode(ENetMode::NM_Client))
		{
			if (InCharacter->GetLocalRole() == ENetRole::ROLE_AutonomousProxy)
			{
				InCharacter->DisableInput(InCharacter->GetWorld()->GetFirstPlayerController());
			}
		}
		else if (InCharacter->GetWorld()->IsNetMode(ENetMode::NM_Standalone) || 
			InCharacter->GetWorld()->IsNetMode(ENetMode::NM_ListenServer))
		{
			InCharacter->DisableInput(InCharacter->GetWorld()->GetFirstPlayerController());
		}
	}
}

void UAnimNotifyState_IgnoreInput::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);

}

void UAnimNotifyState_IgnoreInput::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	if (ACharacter* InCharacter = Cast<ACharacter>(MeshComp->GetOuter()))
	{
		if (InCharacter->GetWorld()->IsNetMode(ENetMode::NM_Client))
		{
			if (InCharacter->GetLocalRole() == ENetRole::ROLE_AutonomousProxy)
			{
				InCharacter->EnableInput(InCharacter->GetWorld()->GetFirstPlayerController());
			}
		}
		else if (InCharacter->GetWorld()->IsNetMode(ENetMode::NM_Standalone) ||
			InCharacter->GetWorld()->IsNetMode(ENetMode::NM_ListenServer))
		{
			InCharacter->EnableInput(InCharacter->GetWorld()->GetFirstPlayerController());
		}
	}
}

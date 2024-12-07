// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyState_StopRotation.h"
#include "GameFramework/Character.h"

UAnimNotifyState_StopRotation::UAnimNotifyState_StopRotation()
{
}

void UAnimNotifyState_StopRotation::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	if (ACharacter* InCharacter = Cast<ACharacter>(MeshComp->GetOuter()))
	{
		InCharacter->bUseControllerRotationYaw = false;
	}

}

void UAnimNotifyState_StopRotation::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);
}

void UAnimNotifyState_StopRotation::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	if (ACharacter* InCharacter = Cast<ACharacter>(MeshComp->GetOuter()))
	{
		InCharacter->bUseControllerRotationYaw = true;
	}
}

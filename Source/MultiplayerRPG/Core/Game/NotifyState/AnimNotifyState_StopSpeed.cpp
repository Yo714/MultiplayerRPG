// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyState_StopSpeed.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UAnimNotifyState_StopSpeed::UAnimNotifyState_StopSpeed()
	:MaxWalkSpeed(0.f)
{
}

void UAnimNotifyState_StopSpeed::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	if (ACharacter* InCharacter = Cast<ACharacter>(MeshComp->GetOuter()))
	{
		MaxWalkSpeed = InCharacter->GetCharacterMovement()->MaxWalkSpeed;
		InCharacter->GetCharacterMovement()->MaxWalkSpeed = 0.f;
	}
}

void UAnimNotifyState_StopSpeed::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);

}

void UAnimNotifyState_StopSpeed::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	if (ACharacter* InCharacter = Cast<ACharacter>(MeshComp->GetOuter()))
	{
		InCharacter->GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
	}
}

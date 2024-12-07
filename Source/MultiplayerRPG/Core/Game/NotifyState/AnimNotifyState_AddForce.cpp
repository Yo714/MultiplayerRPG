// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyState_AddForce.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"


UAnimNotifyState_AddForce::UAnimNotifyState_AddForce()
	:Super()
	, DirectionForce(1.0f, 0.f, 0.f)
	, ForceSize(180000.f)
	, TotalDurationConsuming(0.f)
	, ForceSizeConsuming(0.f)
{

}

void UAnimNotifyState_AddForce::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	if (ACharacter* InCharacter = Cast<ACharacter>(MeshComp->GetOuter()))
	{
		FVector NewFirection = GetCurrentCharacterDirection(InCharacter);

		InCharacter->GetCharacterMovement()->AddImpulse(ForceSize * NewFirection, true);
	}
}

void UAnimNotifyState_AddForce::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);

	/*if (TotalDurationConsuming > 0.f)
	{
		if (ACharacter* InCharacter = Cast<ACharacter>(MeshComp->GetOuter()))
		{
			FVector NewFirection = GetCurrentCharacterDirection(InCharacter);

			InCharacter->GetCharacterMovement()->AddForce(ForceSizeConsuming * NewFirection);

			if (ForceSizeConsuming > 0.f)
			{
				float PreSecondFrame = 1.0f / FrameDeltaTime;
				float TotalFrame = TotalDurationConsuming * PreSecondFrame;
				float FrameAttenuationFrameDeltaTime = ForceSize / TotalFrame;

				ForceSizeConsuming -= FrameAttenuationFrameDeltaTime;
			}
		}
	}*/

}

void UAnimNotifyState_AddForce::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	if (ACharacter* InCharacter = Cast<ACharacter>(MeshComp->GetOuter()))
	{
		InCharacter->GetCharacterMovement()->StopMovementImmediately();
	}
}

FVector UAnimNotifyState_AddForce::GetCurrentCharacterDirection(ACharacter* InCharacter)
{
	FVector V = FVector::ZeroVector;

	if (InCharacter)
	{
		if (DirectionForce.X != 0.f)
		{
			V += InCharacter->GetActorForwardVector() * DirectionForce.X;
		}
		if (DirectionForce.Y != 0.f)
		{
			V += InCharacter->GetActorRightVector() * DirectionForce.Y;
		}
		if (DirectionForce.Z != 0.f)
		{
			V += InCharacter->GetActorUpVector() * DirectionForce.Z;
		}
	}

	return V;
}

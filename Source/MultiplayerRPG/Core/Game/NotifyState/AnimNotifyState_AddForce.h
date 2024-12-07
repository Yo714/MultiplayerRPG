// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AnimNotifyState_AddForce.generated.h"

/**
 * 
 */
class ACharacter;
UCLASS(meta = (DisplayName = "AddForce"))
class MULTIPLAYERRPG_API UAnimNotifyState_AddForce : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
	UAnimNotifyState_AddForce();

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration);
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime);
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotifyState_AddForce")
	FVector DirectionForce;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotifyState_AddForce")
	float ForceSize;

private:
	float TotalDurationConsuming;
	float ForceSizeConsuming;

	FVector GetCurrentCharacterDirection(ACharacter* InCharacter);
	
	
};

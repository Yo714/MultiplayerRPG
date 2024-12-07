// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AnimNotifyState_StopRotation.generated.h"

/**
 * 
 */
UCLASS(meta = (DisplayName = "StopRotation"))
class MULTIPLAYERRPG_API UAnimNotifyState_StopRotation : public UAnimNotifyState
{
	GENERATED_BODY()
	
	
public:
	UAnimNotifyState_StopRotation();

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration);
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime);
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);
	
};

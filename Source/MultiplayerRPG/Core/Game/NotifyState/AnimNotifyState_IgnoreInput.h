// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AnimNotifyState_IgnoreInput.generated.h"

/**
 * 
 */
UCLASS(meta = (DisplayName = "IgnoreInput"))
class MULTIPLAYERRPG_API UAnimNotifyState_IgnoreInput : public UAnimNotifyState
{
	GENERATED_BODY()
	
	
public:
	UAnimNotifyState_IgnoreInput();

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration);
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime);
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);
	
};

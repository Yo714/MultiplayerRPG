// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AnimNotifyState_StopSpeed.generated.h"

/**
 * 
 */
UCLASS(meta = (DisplayName = "StopSpeed"))
class MULTIPLAYERRPG_API UAnimNotifyState_StopSpeed : public UAnimNotifyState
{
	GENERATED_BODY()
	
	
public:
	UAnimNotifyState_StopSpeed();

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration);
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime);
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);

private:
	float MaxWalkSpeed;
};

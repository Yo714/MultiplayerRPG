// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_ResetComboCheck.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERRPG_API UAnimNotify_ResetComboCheck : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	UAnimNotify_ResetComboCheck();

	virtual FString GetNotifyName_Implementation() const override;
	
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	
	
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_Die.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERRPG_API UAnimNotify_Die : public UAnimNotify
{
	GENERATED_BODY()
	
	
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Death")
	TSubclassOf<UUserWidget> DeathWidgetClass;

private:
	UUserWidget* DeathWidgetInstance;
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "GameplayTagContainer.h"
#include "AnimNotify_Attack.generated.h"

class ARPGHitBox;
/**
 * 
 */
UCLASS(meta = (DisplayName = "Attack"))
class MULTIPLAYERRPG_API UAnimNotify_Attack : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	UAnimNotify_Attack();

	virtual FString GetNotifyName_Implementation() const override;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General configuration")
	TArray<FGameplayTag> BuffTags;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General configuration")
	TSubclassOf<ARPGHitBox> HitObjectClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General configuration")
	FVector RelativeOffsetLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General configuration")
	FRotator RotationOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General configuration")
	float LifeTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General configuration")
	FName InSocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General configuration")
	bool bBind;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hit Box")
	FVector BoxExtent;
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "GameplayEffect.h"
#include "AnimNotify_ApplyGameEffect.generated.h"

class ARPGHitBox_ApplyGameEffect;
/**
 * 
 */
UCLASS(meta = (DisplayName = "ApplyGameEffect"))
class MULTIPLAYERRPG_API UAnimNotify_ApplyGameEffect : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	UAnimNotify_ApplyGameEffect();

	virtual FString GetNotifyName_Implementation() const override;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General configuration")
	TSubclassOf<UGameplayEffect> EffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General configuration")
	TSubclassOf<ARPGHitBox_ApplyGameEffect> HitObjectClass;

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

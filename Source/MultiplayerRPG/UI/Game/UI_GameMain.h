// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Core/UI_Base.h"
#include "UI_GameMain.generated.h"

/**
 * 
 */
class UProgressBar;
UCLASS()
class MULTIPLAYERRPG_API UUI_GameMain : public UUI_Base
{
	GENERATED_BODY()
	
	UPROPERTY(meta = (BindWidget))
	UProgressBar* Health;
	UPROPERTY(meta = (BindWidget))
	UProgressBar* Mana;
	UPROPERTY(meta = (BindWidget))
	UProgressBar* Stamina;
	
public:
	UUI_GameMain(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct();
	virtual void NativeDestruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

protected: 
	UFUNCTION()
	void UpdateHealthProgress(float Inpercent);
	UFUNCTION()
	void UpdateManaProgress(float Inpercent);
	UFUNCTION()
	void UpdateStaminaProgress(float Inpercent);

private:
	float TargetHealth;
	float TargetMana;
	float TargetStamina;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Core/UI_Base.h"
#include "Components/Image.h"
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
	UPROPERTY(meta = (BindWidget))
	UImage* CharacterImage;
	
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
	UFUNCTION()
	void UpdateCharacterImage(UImage* ImageWidget, UTexture2D* Texture);

private:
	float TargetHealth;
	float TargetMana;
	float TargetStamina;


};

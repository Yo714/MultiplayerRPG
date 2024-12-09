// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <MultiplayerRPG/Core/Game/Character/Core/RPGCharacterBase.h>
#include "UI_Base.generated.h"

/**
 * 
 */

UCLASS()
class MULTIPLAYERRPG_API UUI_Base : public UUserWidget
{
	GENERATED_BODY()

protected:
	void PlayWidgetAnim(const FString& InAnimName);
	
	UWidgetAnimation* GetNameWidgetAnimation(const FString& InWidgetName);

	ARPGCharacterBase* UI_GetRPGCharacterBase();
};

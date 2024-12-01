// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Core/UI_Base.h"
#include "UI_EnemyHealthyBar.generated.h"

/**
 * 
 */
class UProgressBar;
UCLASS()
class MULTIPLAYERRPG_API UUI_EnemyHealthyBar : public UUI_Base
{
	GENERATED_BODY()
	
	UPROPERTY(meta=(BindWidget))
	UProgressBar* HealthyBar;
	
public:
	void SetHealthPercent(float InPercent);

};

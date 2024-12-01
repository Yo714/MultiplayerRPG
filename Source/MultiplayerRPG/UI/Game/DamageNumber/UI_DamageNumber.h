// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../Core/UI_Base.h"
#include "UI_DamageNumber.generated.h"

/**
 * 
 */
class UTextBlock;
UCLASS()
class MULTIPLAYERRPG_API UUI_DamageNumber : public UUI_Base
{
	GENERATED_BODY()
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* DamageNum;

public:
	virtual void NativeConstruct();

	void UpdateDamage(const FText& InText);
	
};

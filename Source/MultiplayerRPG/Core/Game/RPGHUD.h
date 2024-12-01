// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RPGHUD.generated.h"

/**
 * 
 */
class UUI_GameMain;
UCLASS()
class MULTIPLAYERRPG_API ARPGHUD : public AHUD
{
	GENERATED_BODY()
	
	UPROPERTY()
	TSubclassOf<UUI_GameMain> GameMainClass;

public:
	UPROPERTY()
	TSubclassOf<AActor> DamageNumClass;
 
public:
	ARPGHUD();

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	UUI_GameMain* GameMain;	
};

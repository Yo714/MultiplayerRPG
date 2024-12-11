// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "RPGGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERRPG_API URPGGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
	
public:
	UPROPERTY(BlueprintReadWrite, Category = "Game Data")
	TSubclassOf<APawn> PlayerCharacter;

	FORCEINLINE TSubclassOf<APawn> GetPlayerCharacter() const { return PlayerCharacter; }

};

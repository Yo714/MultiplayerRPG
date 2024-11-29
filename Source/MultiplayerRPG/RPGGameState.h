// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "DataTable/SkillDataTable.h"
#include "Abilities/GameplayAbility.h"
#include "RPGGameState.generated.h"

/**
 * 
 */
class UGameplayAbility;
UCLASS()
class MULTIPLAYERRPG_API ARPGGameState : public AGameStateBase
{
	GENERATED_BODY()
	

public:
	ARPGGameState();

	TArray<UGameplayAbility*> GetCharacterSkills(int32 InCharacterID);
	TArray<FSkillDataTable*>* GetCharacterSkillTables();

protected:
	UPROPERTY()
	UDataTable* SkillTablePtr;

	TArray<FSkillDataTable*> SkillDataTables;
};

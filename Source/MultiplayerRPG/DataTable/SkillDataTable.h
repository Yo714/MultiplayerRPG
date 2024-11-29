// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Engine/DataTable.h>
#include "SkillDataTable.generated.h"


class UGameplayAbility;

/**
 * 
 */
USTRUCT(BlueprintType)
struct FSkillDataTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	
	FSkillDataTable();

	UPROPERTY(EditDefaultsOnly, Category = "CharacterSkill")
	int32 CharacterID;

	UPROPERTY(EditDefaultsOnly, Category = "CharacterSkill")
	UTexture2D* Icon;

	UPROPERTY(EditDefaultsOnly, Category = "CharacterSkill")
	TSubclassOf<UGameplayAbility> GameplayAbility;
};

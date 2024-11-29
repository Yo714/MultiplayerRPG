// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGGameState.h"

ARPGGameState::ARPGGameState()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> SkillDataTable(TEXT("/Game/DataTable/SkillTable"));
	SkillTablePtr = SkillDataTable.Object;
}

TArray<UGameplayAbility*> ARPGGameState::GetCharacterSkills(int32 InCharacterID)
{
	TArray<UGameplayAbility*> Skills;
	TArray<FSkillDataTable*>* SkillTables = GetCharacterSkillTables();
	if (SkillTables && SkillTables->Num() > 0)
	{
		for (auto& Tmp : SkillDataTables) 
		{
			if (Tmp->CharacterID == InCharacterID)
			{
				UGameplayAbility* NewAbility = Cast<UGameplayAbility>(Tmp->GameplayAbility.GetDefaultObject());
				Skills.Add(NewAbility);
			}
		}
	}

	return Skills;
}

TArray<FSkillDataTable*>* ARPGGameState::GetCharacterSkillTables()
{
	if (SkillTablePtr) 
	{
		SkillDataTables.Empty();
		SkillTablePtr->GetAllRows(TEXT("SkillTable"), SkillDataTables);
	}

	return &SkillDataTables;
}

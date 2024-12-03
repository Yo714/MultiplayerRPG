// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGGameState.h"

ARPGGameState::ARPGGameState()
{
	// Load the Skill DataTable at startup. This is a reference to the data table asset.
	static ConstructorHelpers::FObjectFinder<UDataTable> SkillDataTable(TEXT("/Game/DataTable/SkillTable"));
	// Set the SkillTablePtr to the loaded object
	SkillTablePtr = SkillDataTable.Object;
}

// Function to get character skills based on the character's ID
TArray<UGameplayAbility*> ARPGGameState::GetCharacterSkills(int32 InCharacterID)
{
	TArray<UGameplayAbility*> Skills;
	// Get the list of skill data tables for the character
	TArray<FSkillDataTable*>* SkillTables = GetCharacterSkillTables();
	if (SkillTables && SkillTables->Num() > 0)
	{
		// Iterate through all skill data entries
		for (auto& Tmp : SkillDataTables) 
		{
			// If the current entry matches the requested character ID, add the ability to the skills array
			if (Tmp->CharacterID == InCharacterID)
			{
				// Cast the GameplayAbility to UGameplayAbility and add it to the skills list
				UGameplayAbility* NewAbility = Cast<UGameplayAbility>(Tmp->GameplayAbility.GetDefaultObject());
				Skills.Add(NewAbility);
			}
		}
	}

	return Skills;
}

// Function to load and return all skill data tables
TArray<FSkillDataTable*>* ARPGGameState::GetCharacterSkillTables()
{
	// If the SkillTablePtr is valid, load the skill data into the array
	if (SkillTablePtr) 
	{
		SkillDataTables.Empty();
		// Retrieve all rows from the data table and store them in the SkillDataTables array
		SkillTablePtr->GetAllRows(TEXT("SkillTable"), SkillDataTables);
	}

	return &SkillDataTables;
}

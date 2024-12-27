// Fill out your copyright notice in the Description page of Project Settings.


#include "FightComponent.h"
#include "../Character/Core/RPGCharacterBase.h"
#include "../RPGGameState.h"
#include "../Ability/RPGAbilitySystemComponent.h"
#include "../Ability/RPGGameplayAbility.h"
#include "../Character/MultiplayerRPGCharacter.h"

// Sets default values for this component's properties
UFightComponent::UFightComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFightComponent::BeginPlay()
{
	Super::BeginPlay();

	// Get the owner of this component and cast it to ARPGCharacterBase
	RPGCharacterBase = Cast<ARPGCharacterBase>(GetOwner());

	// If the RPGCharacterBase is valid, initialize the AbilitySystemComponent
	if (RPGCharacterBase.IsValid()) 
	{
		AbilitySystemComponent = Cast<URPGAbilitySystemComponent>(RPGCharacterBase->GetAbilitySystemComponent());
	}

	// Register the character's abilities from the game state
	if (ARPGGameState* GameState = GetWorld()->GetGameState<ARPGGameState>())
	{
		// Get a list of abilities for character ID 1 (this could be expanded for multiple characters)
		TArray<UGameplayAbility*> Abilities = GameState->GetCharacterSkills(RPGCharacterBase->GetCharacterID());

		// Register those abilities with the component
		RegisterGameAbility(Abilities);
	}

}

// Registers abilities for the character and binds them to the AbilitySystemComponent
FGameplayAbilitySpecHandle UFightComponent::RegisterGameAbility(TArray<UGameplayAbility*> InAbilities)
{
	// Ensure the server has authority to grant abilities
	if (GetOwner()->GetLocalRole() == ENetRole::ROLE_Authority)
	{
		if (AbilitySystemComponent.IsValid() && InAbilities.Num() > 0)
		{
			// Iterate through the abilities and assign them to the character
			for (auto& Tmp : InAbilities)
			{
				FGameplayAbilitySpecHandle Handle = AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Tmp));
				const FString String = Tmp->AbilityTags.ToStringSimple();
				Skills.Add(FName(String), Handle);

				// Check for combo attack ability and initialize combo-related variables
				if (String.Equals("Character.Skill.ComboAttack"))
				{
					ComboCheck.Character = Cast<AMultiplayerRPGCharacter>(RPGCharacterBase.Get());
					ComboCheck.ComboKey = "Character.Skill.ComboAttack";
					ComboCheck.MaxIndex = Cast<URPGGameplayAbility>(Tmp)->MontageToPlay->CompositeSections.Num();
				}
			}
		}
	}

	return FGameplayAbilitySpecHandle();

}


// Called every frame
void UFightComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

// Activates a skill based on its GameplayTag
void UFightComponent::ActiveSkill(FGameplayTag SkillName)
{
	ActiveSkill(SkillName.ToString());
}

// Activates a skill based on its string name
void UFightComponent::ActiveSkill(FString SkillName)
{
	if (AbilitySystemComponent.IsValid())
	{
		// Look up the skill in the map and try to activate it
		if (const FGameplayAbilitySpecHandle* Handle = Skills.Find(FName(SkillName)))
		{
			AbilitySystemComponent->TryActivateAbility(*Handle);
		}
	}
}

// Plays the "Hit" animation state
void UFightComponent::PlayHit()
{
	ActiveSkill("Character.State.Hit");
}

// Plays the "Die" animation state
void UFightComponent::PlayDie()
{
	ActiveSkill("Character.State.Die");
}

void UFightComponent::ComboAttackOnPressed()
{
	ComboCheck.Press();
}

void UFightComponent::ComboAttackOnReleased()
{
	ComboCheck.Released();
}

void UFightComponent::ResetComboCheck()
{
	ComboCheck.Reset();
}

// FComboCheck constructor to initialize combo states
FComboCheck::FComboCheck()
	:ComboIndex(INDEX_NONE)
	,bLongPress(false)
	,bShortPress(false)
	,Character(NULL)
	,MaxIndex(0)
{
}

// Called when the combo attack button is pressed
void FComboCheck::Press()
{
	if (ComboIndex == INDEX_NONE && Character != NULL)
	{
		ComboIndex++;

		// Ensure the character exists before proceeding
		check(Character);

		if (Character) 
		{
			// Activate the combo attack ability on the character
			Character->GetFightComponent()->ActiveSkill("Character.Skill.ComboAttack");
		}
	}

	bShortPress = true;
	bLongPress = true;
}

void FComboCheck::Released()
{
	bLongPress = false;
}

void FComboCheck::Reset()
{
	ComboIndex = INDEX_NONE;
}

void FComboCheck::UpdateComboIndex()
{
	//check(MaxIndex > 0);
	ComboIndex++;

	if (ComboIndex > MaxIndex-1) 
	{
		ComboIndex = 1;
	}

}

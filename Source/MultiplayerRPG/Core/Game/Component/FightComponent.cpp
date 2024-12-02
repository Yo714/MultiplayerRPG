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

	RPGCharacterBase = Cast<ARPGCharacterBase>(GetOwner());

	if (RPGCharacterBase.IsValid()) 
	{
		AbilitySystemComponent = Cast<URPGAbilitySystemComponent>(RPGCharacterBase->GetAbilitySystemComponent());
	}

	if (ARPGGameState* GameState = GetWorld()->GetGameState<ARPGGameState>())
	{
		TArray<UGameplayAbility*> Abilities = GameState->GetCharacterSkills(1);

		RegisterGameAbility(Abilities);
	}

}

FGameplayAbilitySpecHandle UFightComponent::RegisterGameAbility(TArray<UGameplayAbility*> InAbilities)
{
	if (GetOwner()->GetLocalRole() == ENetRole::ROLE_Authority)
	{
		if (AbilitySystemComponent.IsValid() && InAbilities.Num() > 0)
		{
			for (auto& Tmp : InAbilities)
			{
				FGameplayAbilitySpecHandle Handle = AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Tmp));
				const FString String = Tmp->AbilityTags.ToStringSimple();
				Skills.Add(FName(String), Handle);


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

void UFightComponent::ActiveSkill(FGameplayTag SkillName)
{
	ActiveSkill(SkillName.ToString());
}

void UFightComponent::ActiveSkill(FString SkillName)
{
	if (AbilitySystemComponent.IsValid())
	{
		if (const FGameplayAbilitySpecHandle* Handle = Skills.Find(FName(SkillName)))
		{
			AbilitySystemComponent->TryActivateAbility(*Handle);
		}
	}
}

void UFightComponent::PlayHit()
{
	ActiveSkill("Character.State.Hit");
}

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

FComboCheck::FComboCheck()
	:ComboIndex(INDEX_NONE)
	,bLongPress(false)
	,bShortPress(false)
	,Character(NULL)
	,MaxIndex(0)
{
}

void FComboCheck::Press()
{
	if (ComboIndex == INDEX_NONE && Character != NULL)
	{
		ComboIndex++;

		check(Character);

		if (Character) 
		{
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
	check(MaxIndex > 0);
	ComboIndex++;

	if (ComboIndex > MaxIndex-1) 
	{
		ComboIndex = 1;
	}

}

// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include <AttributeSet.h>
#include "../Character/Core/RPGCharacterBase.h"
#include "GameplayEffectExtension.h"
#include <MultiplayerRPG/Core/Game/Character/MultiplayerRPGCharacter.h>
#include "../../../Common/RPGMethodUntil.h"

// Constructor to initialize the attribute set with default values.
URPGAttributeSet::URPGAttributeSet()
	:Damage(0.f)
	,Level(1)
	,Health(200.f)
	,MaxHealth(200.f)
	,Mana(100.f)
	,MaxMana(100.f)
	,Stamina(50.f)
	,MaxStamina(50.f)
{


}

// Handles changes in attributes caused by gameplay effects.
void URPGAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	// Get the effect context and source component.
	FGameplayEffectContextHandle Context = Data.EffectSpec.GetContext();
	UAbilitySystemComponent* Source = Context.GetOriginalInstigatorAbilitySystemComponent();
	const FGameplayTagContainer& SourceTags = *Data.EffectSpec.CapturedSourceTags.GetAggregatedTags();

	float DeltaValue = 0;
	// Handle additive modifications to the attributes.
	if (Data.EvaluatedData.ModifierOp == EGameplayModOp::Type::Additive) 
	{
		DeltaValue = Data.EvaluatedData.Magnitude;
	}

	// Get the target actor, controller, and character from the ability info.
	AActor* TargetActor = nullptr;
	AController* TargetController = nullptr;
	ARPGCharacterBase* TargetCharacter = nullptr;

	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid()) 
	{
		TargetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		TargetCharacter = Cast<ARPGCharacterBase>(TargetActor);
	}

	if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		if (Source && TargetCharacter)
		{
			const URPGAttributeSet* SourceAttr =  Cast<URPGAttributeSet>(Source->GetAttributeSet(URPGAttributeSet::StaticClass()));
			const URPGAttributeSet* TargetAttr = Cast<URPGAttributeSet>(TargetCharacter->GetAbilitySystemComponent()->GetAttributeSet(URPGAttributeSet::StaticClass()));
		
			float ActualDamage = GetDamage();
			float ActualHealth = FMath::Clamp(GetHealth() - ActualDamage, 0.0f, GetMaxHealth());

			SetHealth(ActualHealth);

			TargetCharacter->HandleHealthChanged(ActualHealth / GetMaxHealth());

			if (AMultiplayerRPGCharacter* Character = Cast<AMultiplayerRPGCharacter>(TargetCharacter))
			{
				Character->UpdateHealth(GetHealth() / GetMaxHealth());
			}

			if (GetHealth() <= 0.f)
			{
				TargetCharacter->PlayDie();
			}

			TargetCharacter->SpawnDamageNum(TargetActor, -ActualDamage, FLinearColor::Red);

			SetDamage(0.f);
		}
	}
	// Handle health changes.
	else if (Data.EvaluatedData.Attribute == GetHealthAttribute()) 
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));

		if (TargetCharacter) 
		{
			TargetCharacter->HandleHealthChanged(GetHealth() / GetMaxHealth());

			if (AMultiplayerRPGCharacter* Character = Cast<AMultiplayerRPGCharacter>(TargetCharacter)) 
			{
				Character->UpdateHealth(GetHealth() / GetMaxHealth());
			}

			if (GetHealth() <= 0.f)
			{
				TargetCharacter->PlayDie();
			}

			if (DeltaValue != 0)
			{
				if (DeltaValue > 0)
				{
					TargetCharacter->SpawnDamageNum(TargetActor, DeltaValue, FLinearColor::Green);
				}
				else
				{
					TargetCharacter->SpawnDamageNum(TargetActor, DeltaValue, FLinearColor::Red);
				}
			}
		}
	}
	// Handle mana changes.
	else if (Data.EvaluatedData.Attribute == GetManaAttribute()) 
	{
		SetMana(FMath::Clamp(GetMana(), 0.0f, GetMaxMana()));

		if (AMultiplayerRPGCharacter* Character = Cast<AMultiplayerRPGCharacter>(TargetCharacter))
		{
			Character->UpdateMana(GetMana() / GetMaxMana());
		}

		if (DeltaValue > 0)
		{
			TargetCharacter->SpawnDamageNum(TargetActor, DeltaValue, FLinearColor::Blue);
		}
	}
	// Handle stamina changes.
	else if (Data.EvaluatedData.Attribute == GetStaminaAttribute())
	{
		SetStamina(FMath::Clamp(GetStamina(), 0.0f, GetMaxStamina()));

		if (AMultiplayerRPGCharacter* Character = Cast<AMultiplayerRPGCharacter>(TargetCharacter))
		{
			Character->UpdateStamina(GetStamina() / GetMaxStamina());
		}

		if (DeltaValue > 0)
		{
			TargetCharacter->SpawnDamageNum(TargetActor, DeltaValue, FLinearColor::Yellow);
		}
	}
}

// Replication notification
void URPGAttributeSet::OnRep_Damage(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, Damage, OldValue);
}

void URPGAttributeSet::OnRep_Level(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, Level, OldValue);
}

void URPGAttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, Health, OldValue);
}

void URPGAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, MaxHealth, OldValue);
}

void URPGAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, Mana, OldValue);
}

void URPGAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, MaxMana, OldValue);
}

void URPGAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, Stamina, OldValue);
}

void URPGAttributeSet::OnRep_MaxStamina(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, MaxStamina, OldValue);
}

// Specifies which properties should be replicated to clients.
void URPGAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(URPGAttributeSet, Damage);
	DOREPLIFETIME(URPGAttributeSet, Level);
	DOREPLIFETIME(URPGAttributeSet, Health);
	DOREPLIFETIME(URPGAttributeSet, MaxHealth);
	DOREPLIFETIME(URPGAttributeSet, Mana);
	DOREPLIFETIME(URPGAttributeSet, MaxMana);
	DOREPLIFETIME(URPGAttributeSet, Stamina);
	DOREPLIFETIME(URPGAttributeSet, MaxStamina);
}

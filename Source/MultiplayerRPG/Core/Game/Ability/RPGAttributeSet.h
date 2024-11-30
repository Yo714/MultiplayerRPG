// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "CoreMinimal.h"
#include "RPGAttributeMacros.h"
#include "RPGAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERRPG_API URPGAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	

public:
	URPGAttributeSet();

	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	PROPERTY_FUNCTION_REGISTRATION(URPGAttributeSet, Health);

	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	PROPERTY_FUNCTION_REGISTRATION(URPGAttributeSet, MaxHealth);

	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_Mana)
	FGameplayAttributeData Mana;
	PROPERTY_FUNCTION_REGISTRATION(URPGAttributeSet, Mana);


	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;


protected:
	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_Mana(const FGameplayAttributeData& OldValue);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};

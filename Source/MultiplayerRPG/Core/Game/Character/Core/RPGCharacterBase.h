// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../../Ability/RPGAbilitySystemComponent.h"
#include "../../Ability/RPGAttributeSet.h"
#include "../../Component/FightComponent.h"
#include "RPGCharacterBase.generated.h"

class URPGAbilitySystemComponent;
class URPGAttributeSet;
class UGameplayAbility;
class UWidgetComponent;
class UFightComponent;

DECLARE_DELEGATE_TwoParams(FUpdateSkillCooldownDelegate, const FName&, float)
UCLASS()
class MULTIPLAYERRPG_API ARPGCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = RPGCharacter, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UFightComponent> FightComponent;

	//GAS
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = RPGCharacter, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<URPGAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = RPGCharacter, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<URPGAttributeSet> RPGAttributeSet;

	UPROPERTY(Category = RPGCharacterBase, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* EnemyHealthyBar;


public:
	// Sets default values for this character's properties
	ARPGCharacterBase();

	UFUNCTION(NetMulticast, Reliable)
	virtual void HandleHealthChanged(float InHealthPercent);

public:
	FORCEINLINE UFightComponent* GetFightComponent() { return FightComponent; }
	FORCEINLINE URPGAbilitySystemComponent* GetAbilitySystemComponent() { return AbilitySystemComponent; }
	FORCEINLINE int32 GetCharacterID() { return CharacterID; }

	UFUNCTION(BlueprintCallable)
	bool IsAlive();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void K2_ActiveSkill(FGameplayTag SkillName);

	UFUNCTION(Server, Reliable)
	void ActiveSkill(FGameplayTag SkillName);

	UFUNCTION(Server, Reliable)
	void ActiveSkillByString(const FString& SkillName);

	UFUNCTION(Client, Reliable)
	void CallUpdateCooldownOnClient(const FName& InTagName, float InCooldownValue);

	UFUNCTION(Server, Reliable)
	void PlayHit();

	UFUNCTION(Server, Reliable)
	void PlayDie();

public:
	FUpdateSkillCooldownDelegate UpdateSkillCooldownDelegate;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = RPGCharacter, meta = (AllowPrivateAccess = "true"))
	int32 CharacterID;

};

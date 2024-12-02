// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayAbilitySpec.h"
#include "FightComponent.generated.h"

class URPGAbilitySystemComponent;
class ARPGCharacterBase;

USTRUCT(BlueprintType)
struct MULTIPLAYERRPG_API FComboCheck
{
	GENERATED_USTRUCT_BODY()

	FComboCheck();

	UPROPERTY(EditDefaultsOnly, Category = ComboAttack)
	int32 ComboIndex;

	UPROPERTY(EditDefaultsOnly, Category = ComboAttack)
	bool bLongPress;

	UPROPERTY(EditDefaultsOnly, Category = ComboAttack)
	bool bShortPress;
	
	class AMultiplayerRPGCharacter* Character;

	UPROPERTY()
	int32 MaxIndex;

	UPROPERTY()
	FName ComboKey;

	void Press();

	void Released();

	void Reset();

	void UpdateComboIndex();

};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MULTIPLAYERRPG_API UFightComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY()
	TWeakObjectPtr<ARPGCharacterBase> RPGCharacterBase;

	UPROPERTY(Category = RPGCharacter, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TWeakObjectPtr<URPGAbilitySystemComponent> AbilitySystemComponent;

public:	
	// Sets default values for this component's properties
	UFightComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	FGameplayAbilitySpecHandle RegisterGameAbility(TArray<UGameplayAbility*> InAbilities);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
public:
	void ActiveSkill(FGameplayTag SkillName);
	void ActiveSkill(FString SkillName);

	void PlayHit();
	void PlayDie();

	void ComboAttackOnPressed();
	void ComboAttackOnReleased();
	void ResetComboCheck();

	FORCEINLINE FComboCheck* GetComboCheck() { return& ComboCheck; }

private:
	TMap<FName, FGameplayAbilitySpecHandle> Skills;

	UPROPERTY()
	FComboCheck ComboCheck;


};

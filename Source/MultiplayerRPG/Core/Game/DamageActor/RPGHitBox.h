// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <GameplayTagContainer.h>
#include "RPGHitBox.generated.h"

class ARPGCharacterBase;
class ACharacter;
UCLASS(BlueprintType, Blueprintable)
class MULTIPLAYERRPG_API ARPGHitBox : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HitCollision", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* HitCollisionRootComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HitCollision", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* HitDamage;

	
public:	
	// Sets default values for this actor's properties
	ARPGHitBox(const FObjectInitializer& ObjectInitializer);

	UFUNCTION()
	virtual void HandleDamage(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	virtual UPrimitiveComponent* GetHitDamage();

	void SetHitDamageRelativePosition(const FVector& InNewPostion);

	void SetBoxExtent(const FVector& InNewBoxExtent);

	void SetBuffs(const TArray<FGameplayTag>& InBuffs) { BuffsTags = InBuffs; };

	bool IsExist(ACharacter* InNewTarget) const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


protected:
	UPROPERTY()
	TArray<FGameplayTag> BuffsTags;

	UPROPERTY()
	TArray<TWeakObjectPtr<ARPGCharacterBase>> AttackedTarget;
	
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <GameplayTagContainer.h>
#include <GameplayEffect.h>
#include "RPGHitBox_ApplyGameEffect.generated.h"

class ARPGCharacterBase;
class UProjectileMovementComponent;

UENUM(BlueprintType)
enum class EHitCollisionType :uint8 
{
	HITCOLLISIONTYPE_SHORT_RANGE_ATTACK UMETA(DisplayName = "Short range attack"),
	HITCOLLISIONTYPE_DIRECT_LINE        UMETA(DisplayName = "Direct Line"),
};

UCLASS(BlueprintType, Blueprintable)
class MULTIPLAYERRPG_API ARPGHitBox_ApplyGameEffect : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HitCollision", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* HitCollisionRootComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttribute", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* HitDamage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HitCollision", meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovement;

public:
	UPROPERTY(EditDefaultsOnly, Category = "HitCollision")
	EHitCollisionType HitCollisionType;

public:
	// Sets default values for this actor's properties
	ARPGHitBox_ApplyGameEffect(const FObjectInitializer& ObjectInitializer);

	virtual void PreInitCollision(AActor* InMyInstigator);

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

	void SetGameplayEffect(const TSubclassOf<UGameplayEffect>& InGE) { EffectClass = InGE; };

	bool IsExist(ACharacter* InNewTarget) const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;


protected:
	UPROPERTY()
	TSubclassOf<UGameplayEffect> EffectClass;

	UPROPERTY()
	TArray<TWeakObjectPtr<ARPGCharacterBase>> AttackedTarget;



	
};

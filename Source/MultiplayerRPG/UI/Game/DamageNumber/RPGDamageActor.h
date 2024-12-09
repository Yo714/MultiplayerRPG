// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RPGDamageActor.generated.h"

class UWidgetComponent;
UCLASS()
class MULTIPLAYERRPG_API ARPGDamageActor : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HitCollision", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DamageNumRootComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* DamageWidget;


public:	
	// Sets default values for this actor's properties
	ARPGDamageActor();

	void UpdateNum(const FText& InText);
	void UpdateNumColor(const FLinearColor& InColor);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};

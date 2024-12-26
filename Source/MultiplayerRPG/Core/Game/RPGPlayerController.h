// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RPGPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERRPG_API ARPGPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    // Function to request pawn change
    UFUNCTION(Server, Reliable, WithValidation)
    void ServerChangePawn(TSubclassOf<APawn> NewPawnClass);

protected:
    virtual void BeginPlay() override;
};
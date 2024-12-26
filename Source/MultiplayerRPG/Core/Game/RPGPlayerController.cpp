// Fill out your copyright notice in the Description page of Project Settings.

#include "RPGPlayerController.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "RPGGameInstance.h"
#include <Kismet/GameplayStatics.h>

void ARPGPlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (IsLocalPlayerController())
    {
        URPGGameInstance* GameInstance = Cast<URPGGameInstance>(UGameplayStatics::GetGameInstance(this));
        if (GameInstance)
        {
            // Get the character blueprint from GameInstance
            TSubclassOf<APawn> PlayerCharacterClass = GameInstance->GetPlayerCharacter();
            ServerChangePawn(PlayerCharacterClass);
        }
    }
}

void ARPGPlayerController::ServerChangePawn_Implementation(TSubclassOf<APawn> NewPawnClass)
{
    FVector LocalSpawnLocation = FVector::ZeroVector;
    FRotator LocalSpawnRotation = FRotator::ZeroRotator;

    // Get current pawn location if it exists
    if (APawn* CurrentPawn = GetPawn())
    {
        LocalSpawnLocation = CurrentPawn->GetActorLocation();
        LocalSpawnRotation = CurrentPawn->GetActorRotation();
        CurrentPawn->Destroy(); // Destroy the current pawn
    }

    // Spawn the new pawn
    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = this;
    APawn* NewPawn = GetWorld()->SpawnActor<APawn>(NewPawnClass, LocalSpawnLocation, LocalSpawnRotation, SpawnParams);

    if (NewPawn)
    {
        // Possess the new pawn
        Possess(NewPawn);
    }
}


bool ARPGPlayerController::ServerChangePawn_Validate(TSubclassOf<APawn> NewPawnClass)
{
    if (!NewPawnClass || !NewPawnClass->IsChildOf(APawn::StaticClass()))
    {
        UE_LOG(LogTemp, Warning, TEXT("ServerChangePawn: Invalid Pawn class!"));
        return false;
    }
    return true;
}
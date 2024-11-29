// Copyright Epic Games, Inc. All Rights Reserved.

#include "MultiplayerRPGGameMode.h"
#include "MultiplayerRPGCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "RPGGameState.h"

AMultiplayerRPGGameMode::AMultiplayerRPGGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	GameStateClass = ARPGGameState::StaticClass();
}

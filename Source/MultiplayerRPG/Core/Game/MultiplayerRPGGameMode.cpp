// Copyright Epic Games, Inc. All Rights Reserved.

#include "MultiplayerRPGGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "RPGGameState.h"
#include "RPGPlayerState.h"
#include "RPGHUD.h"

AMultiplayerRPGGameMode::AMultiplayerRPGGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Characters/Khaimera/BP_Khaimera"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	GameStateClass = ARPGGameState::StaticClass();
	PlayerStateClass = ARPGPlayerState::StaticClass();
	HUDClass = ARPGHUD::StaticClass();
}

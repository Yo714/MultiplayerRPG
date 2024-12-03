// Copyright Epic Games, Inc. All Rights Reserved.

#include "MultiplayerRPGGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "RPGGameState.h"
#include "RPGPlayerState.h"
#include "RPGHUD.h"

AMultiplayerRPGGameMode::AMultiplayerRPGGameMode()
{
	// Set the default pawn class to our Blueprinted character (Khaimera).
	// This is the character that the player will control.
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Characters/Khaimera/BP_Khaimera"));

	// If the class is found, assign it to DefaultPawnClass
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// Set the GameState, PlayerState, and HUD classes to our custom classes.
	 // These are used for game state management, player-specific state, and UI elements respectively.
	GameStateClass = ARPGGameState::StaticClass();
	PlayerStateClass = ARPGPlayerState::StaticClass();
	HUDClass = ARPGHUD::StaticClass();
}

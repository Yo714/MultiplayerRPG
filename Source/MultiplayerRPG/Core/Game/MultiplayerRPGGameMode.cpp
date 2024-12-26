#include "MultiplayerRPGGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "RPGGameState.h"
#include "RPGPlayerState.h"
#include "RPGHUD.h"
#include "RPGPlayerController.h"
#include "RPGGameInstance.h"
#include "Kismet/GameplayStatics.h"

AMultiplayerRPGGameMode::AMultiplayerRPGGameMode()
{
	// Set the GameState, PlayerState, and HUD classes to our custom classes.
	GameStateClass = ARPGGameState::StaticClass();
	PlayerStateClass = ARPGPlayerState::StaticClass();
	HUDClass = ARPGHUD::StaticClass();
	PlayerControllerClass = ARPGPlayerController::StaticClass();
}
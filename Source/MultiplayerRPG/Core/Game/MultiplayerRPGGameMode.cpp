#include "MultiplayerRPGGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "RPGGameState.h"
#include "RPGPlayerState.h"
#include "RPGHUD.h"
#include "RPGGameInstance.h"
#include "Kismet/GameplayStatics.h"

AMultiplayerRPGGameMode::AMultiplayerRPGGameMode()
{
	// Get the GameInstance (URPGGameInstance)
	URPGGameInstance* GameInstance = Cast<URPGGameInstance>(UGameplayStatics::GetGameInstance(this));

	if (GameInstance)
	{
		// Get the character blueprint from GameInstance
		TSubclassOf<APawn> PlayerCharacterClass = GameInstance->GetPlayerCharacter();

		// Set the DefaultPawnClass to the selected player character blueprint
		if (PlayerCharacterClass)
		{
			DefaultPawnClass = PlayerCharacterClass;
		}
	}

	// Set the GameState, PlayerState, and HUD classes to our custom classes.
	GameStateClass = ARPGGameState::StaticClass();
	PlayerStateClass = ARPGPlayerState::StaticClass();
	HUDClass = ARPGHUD::StaticClass();
}
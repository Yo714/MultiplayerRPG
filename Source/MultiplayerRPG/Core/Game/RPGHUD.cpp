// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGHUD.h"
#include "../../UI/Game/UI_GameMain.h"

ARPGHUD::ARPGHUD()
{	
	// Load the GameMain widget class (UI for the main game interface)
	static ConstructorHelpers::FClassFinder<UUI_GameMain> GameMain_BPClass(TEXT("/Game/UI/Game/UI_GameMain_BP"));
	GameMainClass = GameMain_BPClass.Class;

	// Load the DamageNum widget class (UI for displaying damage numbers)
	static ConstructorHelpers::FClassFinder<AActor> DamageNum_BPClass(TEXT("/Game/UI/Game/DamageNum/DamageNum_BP"));
	DamageNumClass = DamageNum_BPClass.Class;
}

void ARPGHUD::BeginPlay()
{
	Super::BeginPlay();

	// If the GameMain class is valid, create and add the main game UI to the viewport
	if (GameMainClass)
	{
		// Create the GameMain widget instance
		GameMain = CreateWidget<UUI_GameMain>(GetWorld(), GameMainClass);

		// Add the widget to the player's screen
		GameMain->AddToViewport();
	}
}

// Called when the HUD is removed or the game ends
void ARPGHUD::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

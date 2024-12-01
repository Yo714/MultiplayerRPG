// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGHUD.h"
#include "../../UI/Game/UI_GameMain.h"

ARPGHUD::ARPGHUD()
{	
	static ConstructorHelpers::FClassFinder<UUI_GameMain> GameMain_BPClass(TEXT("/Game/UI/Game/UI_GameMain_BP"));
	GameMainClass = GameMain_BPClass.Class;

	static ConstructorHelpers::FClassFinder<AActor> DamageNum_BPClass(TEXT("/Game/UI/Game/DamageNum/DamageNum_BP"));
	DamageNumClass = DamageNum_BPClass.Class;
}

void ARPGHUD::BeginPlay()
{
	Super::BeginPlay();

	if (GameMainClass)
	{
		GameMain = CreateWidget<UUI_GameMain>(GetWorld(), GameMainClass);

		GameMain->AddToViewport();
	}
}

void ARPGHUD::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

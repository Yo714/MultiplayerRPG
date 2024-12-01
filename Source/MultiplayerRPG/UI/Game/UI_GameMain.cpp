// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_GameMain.h"
#include <Components/ProgressBar.h>
#include <MultiplayerRPG/Core/Game/Character/MultiplayerRPGCharacter.h>


UUI_GameMain::UUI_GameMain(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
	,TargetHealth(1.0f)
	,TargetMana(1.0f)
	,TargetStamina(1.0f)
{
}

void UUI_GameMain::NativeConstruct()
{
	Super::NativeConstruct();

	if (AMultiplayerRPGCharacter* PlayerCharacter = Cast<AMultiplayerRPGCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn()))
	{
		PlayerCharacter->UpdateHealthProgress.BindUObject(this, &UUI_GameMain::UpdateHealthProgress);
		PlayerCharacter->UpdateManaProgress.BindUObject(this, &UUI_GameMain::UpdateManaProgress);
		PlayerCharacter->UpdateStaminaProgress.BindUObject(this, &UUI_GameMain::UpdateStaminaProgress);
	}
}

void UUI_GameMain::NativeDestruct()
{
	Super::NativeDestruct();
}

void UUI_GameMain::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (Health && !FMath::IsNearlyEqual(TargetHealth, Health->Percent)) {
		double fInterpTo_Health = FMath::FInterpTo(Health->Percent, TargetHealth, InDeltaTime, 3.0);

		Health->SetPercent(fInterpTo_Health);
	}

	if (Mana && !FMath::IsNearlyEqual(TargetMana, Mana->Percent)) {
		double fInterpTo_Mana = FMath::FInterpTo(Mana->Percent, TargetMana, InDeltaTime, 3.0);

		Mana->SetPercent(fInterpTo_Mana);
	}

	if (Stamina && !FMath::IsNearlyEqual(TargetStamina, Stamina->Percent)) {
		double fInterpTo_Stamina = FMath::FInterpTo(Stamina->Percent, TargetStamina, InDeltaTime, 3.0);

		Stamina->SetPercent(fInterpTo_Stamina);
	}
}

void UUI_GameMain::UpdateHealthProgress(float Inpercent)
{
	TargetHealth = Inpercent;
}

void UUI_GameMain::UpdateManaProgress(float Inpercent)
{
	TargetMana = Inpercent;
}

void UUI_GameMain::UpdateStaminaProgress(float Inpercent)
{
	TargetStamina = Inpercent;
}

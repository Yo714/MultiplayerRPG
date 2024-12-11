// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_GameMain.h"
#include <Components/ProgressBar.h>
#include <MultiplayerRPG/Core/Game/Character/MultiplayerRPGCharacter.h>
#include <MultiplayerRPG/Core/Game/Character/Core/RPGCharacterBase.h>


// Constructor for the UUI_GameMain class, initializing the progress bar values
UUI_GameMain::UUI_GameMain(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
	,TargetHealth(1.0f)
	,TargetMana(1.0f)
	,TargetStamina(1.0f)
{
}

// Called when the widget is constructed and initialized
void UUI_GameMain::NativeConstruct()
{
	Super::NativeConstruct();

	if (ARPGCharacterBase* PlayerCharacterBase = Cast<ARPGCharacterBase>(UI_GetRPGCharacterBase()))
	{
		if (AMultiplayerRPGCharacter* PlayerCharacter = Cast<AMultiplayerRPGCharacter>(PlayerCharacterBase))
		{
			PlayerCharacter->UpdateHealthProgress.BindUObject(this, &UUI_GameMain::UpdateHealthProgress);
			PlayerCharacter->UpdateManaProgress.BindUObject(this, &UUI_GameMain::UpdateManaProgress);
			PlayerCharacter->UpdateStaminaProgress.BindUObject(this, &UUI_GameMain::UpdateStaminaProgress);
		}


		UpdateCharacterImage(CharacterImage, PlayerCharacterBase->GetCharacterImage());
	}
}

void UUI_GameMain::NativeDestruct()
{
	Super::NativeDestruct();

	if (AMultiplayerRPGCharacter* PlayerCharacter = Cast<AMultiplayerRPGCharacter>(UI_GetRPGCharacterBase()))
	{
		// Bind functions to update health, mana, and stamina progress bars
		PlayerCharacter->UpdateHealthProgress.Unbind();
		PlayerCharacter->UpdateManaProgress.Unbind();
		PlayerCharacter->UpdateStaminaProgress.Unbind();
	}
}

// Called every frame to update the progress bars smoothly
void UUI_GameMain::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	// Smoothly interpolate the health progress bar towards the target health value
	if (Health && !FMath::IsNearlyEqual(TargetHealth, Health->Percent)) {
		double fInterpTo_Health = FMath::FInterpTo(Health->Percent, TargetHealth, InDeltaTime, 3.0);

		Health->SetPercent(fInterpTo_Health);
	}

	// Smoothly interpolate the mana progress bar towards the target mana value
	if (Mana && !FMath::IsNearlyEqual(TargetMana, Mana->Percent)) {
		double fInterpTo_Mana = FMath::FInterpTo(Mana->Percent, TargetMana, InDeltaTime, 3.0);

		Mana->SetPercent(fInterpTo_Mana);
	}

	// Smoothly interpolate the stamina progress bar towards the target stamina 
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

void UUI_GameMain::UpdateCharacterImage(UImage* ImageWidget, UTexture2D* Texture)
{
	if (ImageWidget && Texture)
	{
		ImageWidget->SetBrushFromTexture(Texture);
		ImageWidget->SetBrushSize(FVector2D(100, 100));
	}
}
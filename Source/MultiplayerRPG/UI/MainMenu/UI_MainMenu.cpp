#include "UI_MainMenu.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include <MultiplayerRPG/Core/Game/RPGGameInstance.h>
#include <Kismet/GameplayStatics.h>
#include <MultiplayerRPG/Core/Game/RPGPlayerController.h>

void UUI_MainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	GameInstance = Cast<URPGGameInstance>(UGameplayStatics::GetGameInstance(this));
	if (!GameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get RPGGameInstance in UUI_MainMenu."));
		return;
	}

	if (CharacterInfoArray.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("CharacterInfoArray is empty. Please check blueprint settings."));
		return;
	}

	if (Button_L)
	{
		Button_L->OnClicked.AddDynamic(this, &UUI_MainMenu::OnButtonLClicked);
	}

	if (Button_R)
	{
		Button_R->OnClicked.AddDynamic(this, &UUI_MainMenu::OnButtonRClicked);
	}

	if (Button_PlayGame)
	{
		Button_PlayGame->OnClicked.AddDynamic(this, &UUI_MainMenu::OnButtonPlayGameClicked);
	}

	UpdateCharacterImage();
}

void UUI_MainMenu::OnButtonLClicked()
{
	if (CharacterInfoArray.Num() > 0)
	{
		CurrentCharacterIndex = (CurrentCharacterIndex - 1 + CharacterInfoArray.Num()) % CharacterInfoArray.Num();
		UpdateCharacterImage();
	}
}

void UUI_MainMenu::OnButtonRClicked()
{
	if (CharacterInfoArray.Num() > 0)
	{
		CurrentCharacterIndex = (CurrentCharacterIndex + 1) % CharacterInfoArray.Num();
		UpdateCharacterImage();
	}
}

void UUI_MainMenu::OnButtonPlayGameClicked()
{
	if (GetWorld()->GetFirstPlayerController())
	{
		GameInstance->PlayerCharacter = PlayerCharacter;
	}
}

void UUI_MainMenu::UpdateCharacterImage()
{
	if (CharacterImage && CharacterInfoArray.IsValidIndex(CurrentCharacterIndex))
	{
		const FCharacterInfo& CurrentInfo = CharacterInfoArray[CurrentCharacterIndex];
		PlayerCharacter = CurrentInfo.CharacterBlueprint;
		CharacterImage->SetBrushFromTexture(CurrentInfo.CharacterImage);
		CharacterImage->SetBrushSize(FVector2D(280, 280));
	}
}

#pragma once

#include "CoreMinimal.h"
#include "../Core/UI_Base.h"
#include "UI_MainMenu.generated.h"

class UImage;
class UButton;
class URPGGameInstance;

USTRUCT(BlueprintType)
struct FCharacterInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* CharacterImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> CharacterBlueprint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText CharacterDescription;
};

UCLASS()
class MULTIPLAYERRPG_API UUI_MainMenu : public UUI_Base
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Character Selection")
	int32 CurrentCharacterIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Selection")
	TArray<FCharacterInfo> CharacterInfoArray;

private:
	UPROPERTY(meta = (BindWidget))
	UImage* CharacterImage;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_L;

	UPROPERTY(meta = (BindWidget))
	UButton* Button_R;

	URPGGameInstance* GameInstance;

	UFUNCTION()
	void OnButtonLClicked();

	UFUNCTION()
	void OnButtonRClicked();

	void UpdateCharacterImage();
};

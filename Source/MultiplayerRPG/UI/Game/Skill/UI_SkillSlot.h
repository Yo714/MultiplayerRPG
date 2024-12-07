// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Core/UI_SlotBase.h"
#include <MultiplayerRPG/DataTable/SkillDataTable.h>
#include <Components/TextBlock.h>
#include <Components/Image.h>
#include "UI_SkillSlot.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERRPG_API UUI_SkillSlot : public UUI_SlotBase
{
	GENERATED_BODY()
	
	
	UPROPERTY(meta = (BindWidget))
	UImage* SlotIcon;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SlotCDValue;
	
	UPROPERTY(meta = (BindWidget))
	UImage* SlotCD;

	UPROPERTY()
	class UMaterialInstanceDynamic* CDMaterialDynamic;

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual void OnClickedWidget();

	void Update(const FSkillDataTable& InSkillDataTable);

	void StartUpdateCD(float InCDValue);

	void SetMaxCD(float InCDValue);

	void DrawSlotCDMat(float InSlotCD);

	FName Tags;

protected:
	int32 KeyNumber;
	FString KeyString;

	static int32 PlayerSkillNumber;

	UPROPERTY()
	float Cooldown;

	UPROPERTY()
	float MaxCooldown;
};

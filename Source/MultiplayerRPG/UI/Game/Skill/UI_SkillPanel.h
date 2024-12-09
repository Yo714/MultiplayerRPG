// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../Core/UI_Base.h"
#include <Components/HorizontalBox.h>
#include "UI_SkillSlot.h"
#include "UI_SkillPanel.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERRPG_API UUI_SkillPanel : public UUI_Base
{
	GENERATED_BODY()
	
	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* SlotArray;

	UPROPERTY(EditDefaultsOnly, Category = UI)
	TSubclassOf<UUI_SkillSlot> SkillSlotClass;
	
public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void LayoutSlot();
	
	UFUNCTION()
	void UpdateSkillCD(const FName& InTagname, float InCDValue);

};

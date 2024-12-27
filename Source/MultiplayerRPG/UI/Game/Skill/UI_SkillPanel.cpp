// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_SkillPanel.h"
#include <MultiplayerRPG/Core/Game/Character/Core/RPGCharacterBase.h>
#include <MultiplayerRPG/Core/Game/RPGGameState.h>
#include "../../../Core/Game/Character/Core/RPGCharacterBase.h"

void UUI_SkillPanel::NativeConstruct()
{
	Super::NativeConstruct();
	LayoutSlot();

	UI_GetRPGCharacterBaseAsync([this](ARPGCharacterBase* InCharacter) {
		if (InCharacter)
		{
			InCharacter->UpdateSkillCooldownDelegate.BindUObject(this, &UUI_SkillPanel::UpdateSkillCD);
		}
		});
}

void UUI_SkillPanel::NativeDestruct()
{
	Super::NativeDestruct();

	UI_GetRPGCharacterBaseAsync([this](ARPGCharacterBase* InCharacter) {
		if (InCharacter)
		{
			InCharacter->UpdateSkillCooldownDelegate.Unbind();
		}
		});
}

void UUI_SkillPanel::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UUI_SkillPanel::LayoutSlot()
{
    if (!SkillSlotClass)
    {
        return;
    }

    UI_GetRPGCharacterBaseAsync([this](ARPGCharacterBase* InCharacterBase) {
        if (!InCharacterBase)
        {
            return;
        }

        if (ARPGGameState* InGameState = GetWorld()->GetGameState<ARPGGameState>())
        {
            int32 CharacterID = InCharacterBase->GetCharacterID();
            TArray<FSkillDataTable*> SkillTables = InGameState->GetCharacterSkillTables(CharacterID);

            int32 j = 0;

            for (size_t i = 0; i < 6; i++)
            {
                if (UUI_SkillSlot* SlotWidget = CreateWidget<UUI_SkillSlot>(GetWorld(), SkillSlotClass))
                {
                    if (UHorizontalBoxSlot* GridSlot = SlotArray->AddChildToHorizontalBox(SlotWidget))
                    {
                        if (SkillTables.Num() > 0)
                        {
                            for (; j < SkillTables.Num(); j++)
                            {
                                if (UGameplayAbility* GA = Cast<UGameplayAbility>(SkillTables[j]->GameplayAbility->GetDefaultObject()))
                                {
                                    FString GATag = GA->AbilityTags.ToStringSimple();
                                    if (GATag == "Character.State.Die" || GATag == "Character.State.Hit" || GATag == "Character.Skill.ComboAttack")
                                    {
                                        continue;
                                    }
                                }

                                SlotWidget->Update(*SkillTables[j]);
                                j++;
                                break;
                            }
                        }
                    }
                }
            }
        }
        });
}

void UUI_SkillPanel::UpdateSkillCD(const FName& InTagName, float InCDValue)
{
	auto Tmp = [&](UUI_SkillSlot* InSkillSlot) {
		if (InSkillSlot)
		{
			if (InSkillSlot->Tags == InTagName)
			{
				InSkillSlot->StartUpdateCD(InCDValue);
				InSkillSlot->SetMaxCD(InCDValue);
				return true;
			}
		}
		return false;
	};

	if (SlotArray)
	{
		for (int32 i = 0; i < SlotArray->GetChildrenCount(); i++)
		{
			if (Tmp(Cast<UUI_SkillSlot>(SlotArray->GetChildAt(i))))
			{
				break;
			}
		}
	}

}

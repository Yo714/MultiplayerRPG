// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_SkillSlot.h"
#include <MultiplayerRPG/Core/Game/Character/Core/RPGCharacterBase.h>

int32 UUI_SkillSlot::PlayerSkillNumber = 0;
void UUI_SkillSlot::NativeConstruct()
{
	Super::NativeConstruct();

	if (PlayerSkillNumber == 6)
	{
		PlayerSkillNumber = 0;
	}

	KeyNumber = ++PlayerSkillNumber;
	KeyString = FString::FromInt(KeyNumber);
	FString InPlayerSkillName = FString::Printf(TEXT("PlayerSkill_%i"), PlayerSkillNumber);
	GetWorld()->GetFirstPlayerController()->InputComponent->BindAction(*InPlayerSkillName, IE_Pressed, this, &UUI_SkillSlot::OnClickedWidget);

	CDMaterialDynamic = SlotCD->GetDynamicMaterial();


}

void UUI_SkillSlot::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (Cooldown > 0.f)
	{
		SlotCDValue->SetVisibility(ESlateVisibility::HitTestInvisible);
		Cooldown -= InDeltaTime;
		DrawSlotCDMat(1 - Cooldown / MaxCooldown);
		SlotCDValue->SetText(FText::FromString(FString::Printf(TEXT("%.1f"), Cooldown)));
	}
	else
	{
		SlotCDValue->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UUI_SkillSlot::OnClickedWidget()
{
	if (ARPGCharacterBase* InCharacter = GetWorld()->GetFirstPlayerController()->GetPawn<ARPGCharacterBase>())
	{
		InCharacter->ActiveSkillByString(Tags.ToString());
	}
}

void UUI_SkillSlot::Update(const FSkillDataTable& InSkillDataTable)
{
	SlotIcon->SetBrushFromTexture(InSkillDataTable.Icon);

	if (UGameplayAbility* GA = Cast<UGameplayAbility>(InSkillDataTable.GameplayAbility->GetDefaultObject()))
	{
		FString GATag = GA->AbilityTags.ToStringSimple();
		Tags = FName(GATag);
	}
}

void UUI_SkillSlot::StartUpdateCD(float InCDValue)
{
	Cooldown = InCDValue;
}

void UUI_SkillSlot::SetMaxCD(float InCDValue)
{
	MaxCooldown = InCDValue;
}

void UUI_SkillSlot::DrawSlotCDMat(float InSlotCD)
{
	if (CDMaterialDynamic)
	{
		if (InSlotCD > 0.0f && InSlotCD < 1.0f)
		{
			CDMaterialDynamic->SetScalarParameterValue(FName("Param"), true);
			SlotCD->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		}
		else
		{
			CDMaterialDynamic->SetScalarParameterValue(FName("Param"), false);
			SlotCD->SetVisibility(ESlateVisibility::Hidden);
		}

		CDMaterialDynamic->SetScalarParameterValue(FName("Param"), InSlotCD);
	}
}

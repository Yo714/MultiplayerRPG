// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_DamageNumber.h"
#include "Components/TextBlock.h"

void UUI_DamageNumber::NativeConstruct() 
{
	PlayWidgetAnim(TEXT("FadeAnimation"));
}

void UUI_DamageNumber::UpdateDamage(const FText& InText)
{
	DamageNum->SetText(InText);
}





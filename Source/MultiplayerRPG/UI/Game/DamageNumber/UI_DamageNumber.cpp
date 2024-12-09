// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_DamageNumber.h"
#include "Components/TextBlock.h"

void UUI_DamageNumber::NativeConstruct() 
{
	// Play the fade animation when the widget is constructed (this could be an animation for fading the damage number)
	PlayWidgetAnim(TEXT("FadeAnimation"));
}

// Updates the displayed damage text in the UI
void UUI_DamageNumber::UpdateNum(const FText& InText)
{
	if (NumText) 
	{
		// Set the TextBlock's text to the new damage value
		NumText->SetText(InText);
	}
}

void UUI_DamageNumber::UpdateNumColor(const FLinearColor& InColor)
{
	if (NumText)
	{
		// Set the TextBlock's text to the new damage value
		NumText->SetColorAndOpacity(FSlateColor(InColor));
	}
}





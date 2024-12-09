// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_Base.h"
#include "Animation/WidgetAnimation.h"
#include "Blueprint/WidgetBlueprintGeneratedClass.h"

// Plays the widget animation with the given name.
void UUI_Base::PlayWidgetAnim(const FString& InAnimName)
{
	// Get the widget animation by name
	if (UWidgetAnimation* TempAnimation = GetNameWidgetAnimation(InAnimName))
	{
		// If the animation is found, play it
		PlayAnimation(TempAnimation);
	}
}

// Retrieves a widget animation by its name
UWidgetAnimation* UUI_Base::GetNameWidgetAnimation(const FString& InWidgetName)
{
	// Get the generated class of the widget blueprint
	if (UWidgetBlueprintGeneratedClass* WidgetBlueprintGenerated = Cast<UWidgetBlueprintGeneratedClass>(GetClass())) 
	{
		// Get all animations defined in the widget blueprint
		TArray<UWidgetAnimation*> TArrayAnimations = WidgetBlueprintGenerated->Animations;

		// Find the animation whose name matches the given name with "_INST" appended
		UWidgetAnimation** MyTempAnimation = TArrayAnimations.FindByPredicate(
			[&](const UWidgetAnimation* OurAnimation)
			{
				return OurAnimation->GetFName().ToString() == (InWidgetName + FString("_INST"));
			}
		);
		return *MyTempAnimation;
	}
	return NULL;
}

ARPGCharacterBase* UUI_Base::UI_GetRPGCharacterBase()
{
	if (GetWorld())
	{
		if (APlayerController* InPlayerController = GetWorld()->GetFirstPlayerController<APlayerController>())
		{
			if (ARPGCharacterBase* InCharacter = InPlayerController->GetPawn<ARPGCharacterBase>())
			{
				return InCharacter;
			}
		}
	}

	return nullptr;
}


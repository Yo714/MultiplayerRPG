// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGDamageActor.h"
#include "UI_DamageNumber.h"
#include "Components/WidgetComponent.h"


// Sets default values
ARPGDamageActor::ARPGDamageActor()
{
	// Create the root component for the damage number actor
	DamageNumRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DamageNumRootComponent"));
	RootComponent = DamageNumRootComponent;

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the WidgetComponent which will hold the damage number widget
	DamageWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("DamageWidget"));
	DamageWidget->SetupAttachment(RootComponent);
	DamageWidget->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	DamageWidget->SetHiddenInGame(true);
}

// Updates the damage number displayed by the widget
void ARPGDamageActor::UpdateNum(const FText& InText)
{
	// Check if the widget component is valid
	if (DamageWidget)
	{
		// Attempt to cast the widget object to UUI_DamageNumber, which is the custom widget for displaying damage
		if (UUI_DamageNumber* DamageNum = Cast<UUI_DamageNumber>(DamageWidget->GetUserWidgetObject())) 
		{
			// Make the widget visible in the game
			DamageWidget->SetHiddenInGame(false);
			// Update the damage text on the widget
			DamageNum->UpdateNum(InText);
		}
	}	
}

void ARPGDamageActor::UpdateNumColor(const FLinearColor& InColor)
{
	if (DamageWidget)
	{
		if (UUI_DamageNumber* DamageNum = Cast<UUI_DamageNumber>(DamageWidget->GetUserWidgetObject()))
		{
			// Make the widget visible in the game
			DamageWidget->SetHiddenInGame(false);
			// Update the damage text on the widget
			DamageNum->UpdateNumColor(InColor);
		}
	}
}

// Called when the game starts or when spawned
void ARPGDamageActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARPGDamageActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGDamageActor.h"
#include "UI_DamageNumber.h"
#include "Components/WidgetComponent.h"


// Sets default values
ARPGDamageActor::ARPGDamageActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DamageWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("DamageWidget"));
	DamageWidget->SetupAttachment(RootComponent);
	DamageWidget->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ARPGDamageActor::UpdateDamageNum(const FText& InText)
{
	if (DamageWidget)
	{
		if (UUI_DamageNumber* DamageNum = Cast<UUI_DamageNumber>(DamageWidget->GetUserWidgetObject())) 
		{
			DamageNum->UpdateDamage(InText);
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


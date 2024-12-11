// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_Die.h"
#include "../Character/Core/RPGCharacterBase.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"
#include "Components/CapsuleComponent.h"


void UAnimNotify_Die::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	ARPGCharacterBase* Character = Cast<ARPGCharacterBase>(MeshComp->GetOwner());
	if (!Character)
	{
		return;
	}

	if (Character->IsLocallyControlled())
	{
		if (DeathWidgetClass)
		{
			APlayerController* PlayerController = Character->GetController<APlayerController>();
			if (PlayerController)
			{
				DeathWidgetInstance = CreateWidget<UUserWidget>(PlayerController, DeathWidgetClass);
				if (DeathWidgetInstance)
				{
					DeathWidgetInstance->AddToViewport();
					PlayerController->SetInputMode(FInputModeUIOnly());
					PlayerController->bShowMouseCursor = true;

					UE_LOG(LogTemp, Log, TEXT("Death screen displayed on client."));
				}
			}
		}
	}

	if (Character->HasAuthority())
	{
		Character->GetCapsuleComponent()->DestroyComponent();
		Character->SetActorHiddenInGame(true);
	}
}
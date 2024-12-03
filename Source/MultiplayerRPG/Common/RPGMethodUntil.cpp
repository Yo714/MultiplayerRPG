#include "RPGMethodUntil.h"
#include "../Core/Game/RPGHUD.h"
#include "../UI/Game/DamageNumber/UI_DamageNumber.h"
#include <MultiplayerRPG/UI/Game/DamageNumber/RPGDamageActor.h>

namespace RPGMethodUntil
{
	void SpawnDamageNum(AActor* InActor, float DamageNum)
	{
		if (InActor)
		{
			// Ensure the code runs only on the client (not the server).
			if (InActor->GetLocalRole() != ENetRole::ROLE_Authority)
			{
				// Get the HUD from the player's controller.
				if (ARPGHUD* InHud = Cast<ARPGHUD>(InActor->GetWorld()->GetFirstPlayerController()->GetHUD()))
				{
					// Spawn the damage number actor at the actor's location.
					AActor* SpawnActor = InActor->GetWorld()->SpawnActor<AActor>(InHud->DamageNumClass, InActor->GetActorLocation(), FRotator::ZeroRotator);
				
					// Update the damage number displayed by the spawned actor.
					Cast<ARPGDamageActor>(SpawnActor)->UpdateDamageNum(FText::FromString(FString::SanitizeFloat(DamageNum)));
				}
			}
		}
	}
}
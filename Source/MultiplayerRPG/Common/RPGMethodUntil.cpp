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
			if (InActor->GetLocalRole() != ENetRole::ROLE_Authority)
			{
				if (ARPGHUD* InHud = Cast<ARPGHUD>(InActor->GetWorld()->GetFirstPlayerController()->GetHUD()))
				{
					AActor* SpawnActor = InActor->GetWorld()->SpawnActor<AActor>(InHud->DamageNumClass, InActor->GetActorLocation(), FRotator::ZeroRotator);
				
					Cast<ARPGDamageActor>(SpawnActor)->UpdateDamageNum(FText::FromString(FString::SanitizeFloat(DamageNum)));
				}
			}
		}
	}
}
#pragma once

#include "CoreMinimal.h"

class AActor;
namespace RPGMethodUntil
{
	//Spawns a damage number UI element at the location of the specified actor.
	void SpawnDamageNum(AActor* InActor, float DamageNum);
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_ApplyGameEffect.h"
#include "../DamageActor/RPGHitBox_ApplyGameEffect.h"

UAnimNotify_ApplyGameEffect::UAnimNotify_ApplyGameEffect()
	:Super()
{
	// Set default values for this notify's properties
	HitObjectClass = ARPGHitBox_ApplyGameEffect::StaticClass();
	BoxExtent = FVector(150.f);
	LifeTime = 0.2f;
	InSocketName = TEXT("Attack");
}

FString UAnimNotify_ApplyGameEffect::GetNotifyName_Implementation() const
{
	return Super::GetNotifyName_Implementation();
}

void UAnimNotify_ApplyGameEffect::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	// Ensure the MeshComp has an associated actor (this is the character or entity)
	if (AActor* InCharacter = Cast<AActor>(MeshComp->GetOuter()))
	{
		// Get the location and rotation of the socket on the mesh
		FVector ComponentLocation = MeshComp->GetSocketLocation(InSocketName);
		FRotator ComponentRotation = MeshComp->GetSocketRotation(InSocketName);

		// Ensure the logic only runs on the server (if in a networked game)
		//if (InCharacter->GetWorld()->IsNetMode(NM_DedicatedServer))
		{
			// Create a transform for spawning the hitbox at the socket location with the rotation offset
			FTransform Transform((ComponentRotation + RotationOffset).Quaternion(), ComponentLocation);

			// Spawn the hitbox actor using the defined class and transform
			if (ARPGHitBox_ApplyGameEffect* HitCollision = InCharacter->GetWorld()->SpawnActorDeferred<ARPGHitBox_ApplyGameEffect>(
				HitObjectClass,
				Transform,
				NULL,
				Cast<APawn>(InCharacter),
				ESpawnActorCollisionHandlingMethod::AlwaysSpawn))
			{
				HitCollision->PreInitCollision(InCharacter);
				// Set the buffs on the hitbox, if any are defined
				HitCollision->SetGameplayEffect(EffectClass);
				// Set the hitbox's size using BoxExtent
				HitCollision->SetBoxExtent(BoxExtent);

				// Adjust the relative position of the hitbox damage area
				FVector RelativeLocation = HitCollision->GetHitDamage()->GetRelativeLocation();
				HitCollision->SetHitDamageRelativePosition(RelativeLocation + RelativeOffsetLocation);
				// Set the lifespan of the hitbox to determine how long it stays in the world
				HitCollision->SetLifeSpan(LifeTime);

				// Finish spawning the actor (apply any deferred properties)
				HitCollision->FinishSpawning(Transform);

				// Attach the hitbox to the character's mesh at the specified socket, if required
				if (bBind)
				{
					HitCollision->AttachToComponent(MeshComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale, InSocketName);
				}
			}
		}
	}
}

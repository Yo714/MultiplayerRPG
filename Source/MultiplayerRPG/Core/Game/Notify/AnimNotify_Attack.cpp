// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_Attack.h"
#include "../DamageActor/RPGHitBox.h"

UAnimNotify_Attack::UAnimNotify_Attack()
	:Super()// Call the parent class constructor
{
	// Set default values for this notify's properties
	HitObjectClass = ARPGHitBox::StaticClass();
	BoxExtent = FVector(150.f);
	LifeTime = 0.2f;
	InSocketName = TEXT("Attack");
}

// Returns the name of this animation notify, typically shown in the animation editor
FString UAnimNotify_Attack::GetNotifyName_Implementation() const
{
	return Super::GetNotifyName_Implementation();
}

// This method is called when the animation notify is triggered during the animation
void UAnimNotify_Attack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	// Ensure the MeshComp has an associated actor (this is the character or entity)
	if (AActor* InCharacter = Cast<AActor>(MeshComp->GetOuter())) 
	{
		// Get the location and rotation of the socket on the mesh
		FVector ComponentLocation = MeshComp->GetSocketLocation(InSocketName);
		FRotator ComponentRotation = MeshComp->GetSocketRotation(InSocketName);

		// Ensure the logic only runs on the server (if in a networked game)
		if (InCharacter->GetWorld()->IsNetMode(NM_DedicatedServer))
		{
			// Create a transform for spawning the hitbox at the socket location with the rotation offset
			FTransform Transform((ComponentRotation + RotationOffset).Quaternion(), ComponentLocation);

			// Spawn the hitbox actor using the defined class and transform
			if (ARPGHitBox* HitCollision = InCharacter->GetWorld()->SpawnActorDeferred<ARPGHitBox>(
				HitObjectClass,
				Transform,
				NULL,
				Cast<APawn>(InCharacter),
				ESpawnActorCollisionHandlingMethod::AlwaysSpawn))
			{
				// Set the buffs on the hitbox, if any are defined
				HitCollision->SetBuffs(BuffTags);
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

// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_Attack.h"
#include "../DamageActor/RPGHitBox.h"

UAnimNotify_Attack::UAnimNotify_Attack()
	:Super()
{
	HitObjectClass = ARPGHitBox::StaticClass();
	BoxExtent = FVector(32.f);
	LifeTime = 4.0f;
	InSocketName = TEXT("OpenFire");
}

FString UAnimNotify_Attack::GetNotifyName_Implementation() const
{
	return Super::GetNotifyName_Implementation();
}

void UAnimNotify_Attack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if (AActor* InCharacter = Cast<AActor>(MeshComp->GetOuter())) 
	{
		FVector ComponentLocation = MeshComp->GetSocketLocation(InSocketName);
		FRotator ComponentRotation = MeshComp->GetSocketRotation(InSocketName);

		if (InCharacter->GetWorld()->IsNetMode(NM_DedicatedServer))
		{
			FTransform Transform((ComponentRotation + RotationOffset).Quaternion(), ComponentLocation);

			if (ARPGHitBox* HitCollision = InCharacter->GetWorld()->SpawnActorDeferred<ARPGHitBox>(
				HitObjectClass,
				Transform,
				NULL,
				Cast<APawn>(InCharacter),
				ESpawnActorCollisionHandlingMethod::AlwaysSpawn))
			{
				HitCollision->SetBuffs(BuffTags);
				HitCollision->SetBoxExtent(BoxExtent);

				FVector RelativeLocation = HitCollision->GetHitDamage()->GetRelativeLocation();
				HitCollision->SetHitDamageRelativePosition(RelativeLocation + RelativeOffsetLocation);
				HitCollision->SetLifeSpan(LifeTime);

				HitCollision->FinishSpawning(Transform);

				if (bBind) 
				{
					HitCollision->AttachToComponent(MeshComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale, InSocketName);
				}
			}
		}
	}

}

// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGHitBox.h"
#include "Components/BoxComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "../Character/MultiplayerRPGCharacter.h"
#include <Abilities/GameplayAbilityTypes.h>

ARPGHitBox::ARPGHitBox(const FObjectInitializer& ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	HitCollisionRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("CollisionRootComponent"));
	RootComponent = HitCollisionRootComponent;

	HitDamage = CreateDefaultSubobject<UBoxComponent>(TEXT("HitDamage"));
	HitDamage->SetupAttachment(RootComponent);

	InitialLifeSpan = 4.f;
	bNetLoadOnClient = false;
	bReplicates = false;
}

void ARPGHitBox::HandleDamage(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (GetInstigator() != OtherActor) 
	{
		if (ARPGCharacterBase* InPawn = Cast<ARPGCharacterBase>(GetInstigator()))
		{
			if (ARPGCharacterBase* InTarget = Cast<ARPGCharacterBase>(OtherActor))
			{
				if (InPawn->GetWorld()->IsNetMode(NM_DedicatedServer))
				{
					FGameplayEventData EventData;
					EventData.Instigator = GetInstigator();
					EventData.Target = InTarget;

					if (IsExist(InTarget))
					{
						return;
					}

					if (!BuffsTags.IsEmpty())
					{
						for (auto& Tmp : BuffsTags)
						{
							UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetInstigator(), Tmp, EventData);
						}
					}

					InTarget->PlayHit();

					AttackedTarget.AddUnique(InTarget);

				}
				else 
				{

				}
			}
		}
	}
}

UPrimitiveComponent* ARPGHitBox::GetHitDamage()
{
	return HitDamage;
}

void ARPGHitBox::SetHitDamageRelativePosition(const FVector& InNewPostion)
{
	if (UPrimitiveComponent* InHitComponent = GetHitDamage())
	{
		InHitComponent->SetRelativeLocation(InNewPostion);
	}
}

void ARPGHitBox::SetBoxExtent(const FVector& InNewBoxExtent)
{
	HitDamage->SetBoxExtent(InNewBoxExtent);
}

// Called when the game starts or when spawned
void ARPGHitBox::BeginPlay()
{	
	if (UPrimitiveComponent* InHitComponent = GetHitDamage())
	{
		InHitComponent->SetHiddenInGame(false);
		InHitComponent->OnComponentBeginOverlap.AddDynamic(this, &ARPGHitBox::HandleDamage);
	}

}

// Called every frame
void ARPGHitBox::Tick(float DeltaTime)
{
}

bool ARPGHitBox::IsExist(ACharacter* InNewTarget) const
{
	for (auto& Tmp : AttackedTarget)
	{
		if (Tmp.IsValid())
		{
			return true;
		}
	}

	return false;
}
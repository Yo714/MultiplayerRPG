// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGHitBox.h"
#include "Components/BoxComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "../Character/MultiplayerRPGCharacter.h"
#include <Abilities/GameplayAbilityTypes.h>

ARPGHitBox::ARPGHitBox(const FObjectInitializer& ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	// Initialize the collision root component
	HitCollisionRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("CollisionRootComponent"));
	RootComponent = HitCollisionRootComponent;

	// Initialize the box component that will represent the damage hitbox
	HitDamage = CreateDefaultSubobject<UBoxComponent>(TEXT("HitDamage"));
	HitDamage->SetupAttachment(RootComponent);

	// Set the initial lifespan of the hitbox actor to 0.2 seconds
	InitialLifeSpan = 0.2f;
	bNetLoadOnClient = false;
	bReplicates = false;
}

// Handles damage when another actor overlaps the hitbox
void ARPGHitBox::HandleDamage(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Ensure the hitbox doesn't affect the instigator itself
	if (GetInstigator() != OtherActor) 
	{
		if (ARPGCharacterBase* InPawn = Cast<ARPGCharacterBase>(GetInstigator()))
		{
			if (ARPGCharacterBase* InTarget = Cast<ARPGCharacterBase>(OtherActor))
			{
				// Only process this on the server
				if (InPawn->GetWorld()->IsNetMode(NM_DedicatedServer))
				{
					FGameplayEventData EventData;
					EventData.Instigator = GetInstigator(); // Set the instigator of the damage event
					EventData.Target = InTarget; // Set the target of the damage event

					// Avoid re-processing if the target has already been attacked by this hitbox
					if (IsExist(InTarget))
					{
						return;
					}

					// If there are buffs associated with the hit, send a gameplay event for each
					if (!BuffsTags.IsEmpty())
					{
						for (auto& Tmp : BuffsTags)
						{
							UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetInstigator(), Tmp, EventData);
						}
					}

					// Play the hit animation or effect on the target character
					InTarget->PlayHit();

					// Keep track of targets that have already been attacked by this hitbox to avoid double processing
					AttackedTarget.AddUnique(InTarget);

				}
				else 
				{

				}
			}
		}
	}
}

// Returns the UPrimitiveComponent representing the hit damage area (the box component)
UPrimitiveComponent* ARPGHitBox::GetHitDamage()
{
	return HitDamage;
}

// Sets the relative position of the hit damage box 
void ARPGHitBox::SetHitDamageRelativePosition(const FVector& InNewPostion)
{
	if (UPrimitiveComponent* InHitComponent = GetHitDamage())
	{
		InHitComponent->SetRelativeLocation(InNewPostion);// Set the position of the damage box
	}
}

// Sets the extent (size) of the hit damage box component
void ARPGHitBox::SetBoxExtent(const FVector& InNewBoxExtent)
{
	HitDamage->SetBoxExtent(InNewBoxExtent);// Adjust the hitbox size
}

// Called when the game starts or when spawned
void ARPGHitBox::BeginPlay()
{	
	// If the hit damage component is valid, make it visible and bind the damage handler function
	if (UPrimitiveComponent* InHitComponent = GetHitDamage())
	{
		InHitComponent->SetHiddenInGame(true);
		InHitComponent->OnComponentBeginOverlap.AddDynamic(this, &ARPGHitBox::HandleDamage);// Bind the overlap event to the damage handler
	}

}

// Called every frame
void ARPGHitBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Checks if the target has already been attacked by this hitbox
bool ARPGHitBox::IsExist(ACharacter* InNewTarget) const
{
	// Iterate through the attacked targets to see if the current one is already in the list
	for (auto& Tmp : AttackedTarget)
	{
		if (Tmp.IsValid())
		{
			if (Tmp == InNewTarget)
			{
				return true;
			}
		}
	}

	return false;
}
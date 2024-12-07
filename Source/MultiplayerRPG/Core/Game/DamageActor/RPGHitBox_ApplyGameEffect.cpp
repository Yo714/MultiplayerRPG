// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGHitBox_ApplyGameEffect.h"
#include "Components/BoxComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "../Character/MultiplayerRPGCharacter.h"
#include <Abilities/GameplayAbilityTypes.h>
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
ARPGHitBox_ApplyGameEffect::ARPGHitBox_ApplyGameEffect(const FObjectInitializer& ObjectInitializer)
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

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->MaxSpeed = 2000.f;
	ProjectileMovement->InitialSpeed = 1600.f;
	ProjectileMovement->ProjectileGravityScale = 0.f;
	ProjectileMovement->SetUpdatedComponent(RootComponent);

	HitCollisionType = EHitCollisionType::HITCOLLISIONTYPE_SHORT_RANGE_ATTACK;
}

void ARPGHitBox_ApplyGameEffect::PreInitCollision(AActor* InMyInstigator)
{
	if (!InMyInstigator)
	{
		return;
	}

	FVector ShootDirection = InMyInstigator->GetActorForwardVector();

	switch (HitCollisionType)
	{
	case EHitCollisionType::HITCOLLISIONTYPE_SHORT_RANGE_ATTACK:
		ProjectileMovement->MaxSpeed = 0.f;
		ProjectileMovement->InitialSpeed = 0.f;
		ProjectileMovement->ProjectileGravityScale = 0.f;
		break;
	case EHitCollisionType::HITCOLLISIONTYPE_DIRECT_LINE:
		RootComponent->SetWorldRotation(FRotator::ZeroRotator);
		ProjectileMovement->Velocity = ShootDirection * ProjectileMovement->InitialSpeed;

		break;
	}
}

void ARPGHitBox_ApplyGameEffect::HandleDamage(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Ensure the hitbox doesn't affect the instigator itself
	if (GetInstigator() != OtherActor)
	{
		if (ARPGCharacterBase* InPawn = Cast<ARPGCharacterBase>(GetInstigator()))
		{
			if (ARPGCharacterBase* InTarget = Cast<ARPGCharacterBase>(OtherActor))
			{
				//if (InTarget->GetLocalRole() == ROLE_Authority)
				{
					if (IsExist(InTarget))
					{
						return;
					}

					if (UAbilitySystemComponent* InAbilitySystemComponent = InTarget->GetAbilitySystemComponent())
					{
						FGameplayEffectContextHandle EffectContext = InAbilitySystemComponent->MakeEffectContext();

						EffectContext.AddSourceObject(InTarget);

						FGameplayEffectSpecHandle EffectSpecHandle = InAbilitySystemComponent->MakeOutgoingSpec(EffectClass, 1, EffectContext);

						if (EffectSpecHandle.IsValid())
						{
							InAbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data.Get(), InAbilitySystemComponent);
						}
					}

					InTarget->PlayHit();

					AttackedTarget.AddUnique(InTarget);
				}
			}
		}
	}
}

UPrimitiveComponent* ARPGHitBox_ApplyGameEffect::GetHitDamage()
{
	return HitDamage;
}

void ARPGHitBox_ApplyGameEffect::SetHitDamageRelativePosition(const FVector& InNewPostion)
{
	if (UPrimitiveComponent* InHitComponent = GetHitDamage())
	{
		InHitComponent->SetRelativeLocation(InNewPostion);// Set the position of the damage box
	}
}

void ARPGHitBox_ApplyGameEffect::SetBoxExtent(const FVector& InNewBoxExtent)
{
	HitDamage->SetBoxExtent(InNewBoxExtent);// Adjust the hitbox size
}

bool ARPGHitBox_ApplyGameEffect::IsExist(ACharacter* InNewTarget) const
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

// Called when the game starts or when spawned
void ARPGHitBox_ApplyGameEffect::BeginPlay()
{
	Super::BeginPlay();
	
	// If the hit damage component is valid, make it visible and bind the damage handler function
	if (UPrimitiveComponent* InHitComponent = GetHitDamage())
	{
		InHitComponent->SetHiddenInGame(true);
		InHitComponent->OnComponentBeginOverlap.AddDynamic(this, &ARPGHitBox_ApplyGameEffect::HandleDamage);// Bind the overlap event to the damage handler
	}
}

// Called every frame
void ARPGHitBox_ApplyGameEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


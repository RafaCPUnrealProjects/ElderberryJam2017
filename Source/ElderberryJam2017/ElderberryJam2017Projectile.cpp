// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "ElderberryJam2017Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/World.h"
#include "TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "NPC.h"


AElderberryJam2017Projectile::AElderberryJam2017Projectile()
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AElderberryJam2017Projectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void AElderberryJam2017Projectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		if (!ensure(NPCToSpawn)) { return; }
		if (OtherActor->ActorHasTag(FName("Enemy")))
		{
			TSubclassOf<UDamageType> const ValidDamageTypeClass = TSubclassOf<UDamageType>(UDamageType::StaticClass());
			FDamageEvent DamageEvent(ValidDamageTypeClass);
			if (UGameplayStatics::ApplyDamage(OtherActor, DamageAmount, UGameplayStatics::GetPlayerController(GetWorld(), 0), this, ValidDamageTypeClass) <= 0)
			{
				auto Location = this->GetActorLocation();
				auto Rotation = this->GetActorRotation();
				FActorSpawnParameters SpawnInfo;
				APawn* Ally = GetWorld()->SpawnActor<ANPC>(NPCToSpawn, Location, Rotation);
				OtherActor->Destroy();
			}
			Destroy();
		}
		else if (OtherComp->IsSimulatingPhysics())
		{
			OtherComp->AddImpulseAtLocation(GetVelocity() * 100.f, GetActorLocation());
			Destroy();
		}
	}
}
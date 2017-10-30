// Fill out your copyright notice in the Description page of Project Settings.

#include "NPC.h"


// Sets default values
ANPC::ANPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
}

float ANPC::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	float DamageTaken = FMath::Clamp<float>(Damage, 0, CurrentHealth);
	UE_LOG(LogTemp, Warning, TEXT("Took %f damage"), DamageTaken);
	CurrentHealth -= DamageTaken;
	if (CurrentHealth <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Dead"), *(this->GetName()));
	}
	return (float)DamageTaken;
}

// Called every frame
void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay()
{
	Super::BeginPlay(); // Calls BP  BeginPlay()
}

void ATank::AimAt(FVector HitLocation)
{

	if (!TankAimingComponent) return;

	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
} 

void ATank::Fire()
{
	bool isReloaded = (FPlatformTime::Seconds() - LastFiredTime) > ReloadTimeInSeconds;

	if (!Barrel || !isReloaded) return;

	auto Projectile = GetWorld()->SpawnActor<AProjectile>(
		ProjectileBluePrint,
		Barrel->GetSocketLocation(FName("FiringPoint")),
		Barrel->GetSocketRotation(FName("FiringPoint"))
	);

	Projectile->LaunchProjectile(LaunchSpeed);
	LastFiredTime = FPlatformTime::Seconds();
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	LastFiredTime = FPlatformTime::Seconds();
	// ...
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	LastFiredTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector Target)
{
	if (!ensure(Barrel)) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("FiringPoint"));

	bool HasAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		Target,
		LaunchSpeed,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	FVector AimDirection = OutLaunchVelocity.GetSafeNormal();
	/*if (!AimDirection.X && !AimDirection.Y && !AimDirection.Z) { return; }
	UE_LOG(LogTemp, Warning, TEXT("%s"), *(AimDirection.ToString()))*/
	MoveTurretSystem(AimDirection);
}


void UTankAimingComponent::MoveTurretSystem(const FVector& AimDirection)
{
	if (!ensure(Barrel && Turret)) { return; }

	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if ((FPlatformTime::Seconds() - LastFiredTime) > ReloadTimeInSeconds)
		FiringState = EFiringState::Reloading;
}

void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel && ProjectileBluePrint)) return;

	if (FiringState != EFiringState::Reloading) {
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBluePrint,
			Barrel->GetSocketLocation(FName("FiringPoint")),
			Barrel->GetSocketRotation(FName("FiringPoint"))
			);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFiredTime = FPlatformTime::Seconds();
	}
}
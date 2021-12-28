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

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }

	auto BarrelForward = Barrel->GetForwardVector();

	return (!BarrelForward.Equals(AimDirection, 0.01));
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
	AimDirection = OutLaunchVelocity.GetSafeNormal();
	UE_LOG(LogTemp, Warning, TEXT("AimDirection = %s"), *AimDirection.ToString());
	MoveTurretSystem(AimDirection);
}


void UTankAimingComponent::MoveTurretSystem(const FVector& Target)
{
	if (!ensure(Barrel && Turret)) { return; }

	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = Target.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);
	if (FMath::Abs(DeltaRotator.Yaw) > 180)
		DeltaRotator.Yaw = -(DeltaRotator.Yaw);
	Turret->Rotate(DeltaRotator.Yaw);
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if ((FPlatformTime::Seconds() - LastFiredTime) < ReloadTimeInSeconds)
		FiringState = EFiringState::Reloading;
	else if (IsBarrelMoving())
		FiringState = EFiringState::Aiming;
	else
		FiringState = EFiringState::Locked;
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
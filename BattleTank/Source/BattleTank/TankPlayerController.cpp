// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"

void ATankPlayerController::AimTowardsCrosshair()
{
	auto Tank = GetControlledTank();

	if (!ensure(Tank)) { return; }

	FVector HitLocation;

	if (GetSightRayHitLocation(HitLocation)) {
		Tank->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetAimDirection(FVector &AimDirection) const
{
	FVector CameraWorldLocation;

	int32 ViewportWidth, ViewportHeight = 0;
	GetViewportSize(ViewportWidth, ViewportHeight);

	FVector AimPoint = { ViewportWidth * CrosshairXLocation,
						ViewportHeight * CrosshairYLocation,
						0.f };

	return DeprojectScreenPositionToWorld(AimPoint.X, AimPoint.Y,
		CameraWorldLocation, AimDirection);
}

bool ATankPlayerController::GetAimVectorHitLocation(FVector& HitLocation, FVector AimDirection) const
{
	FHitResult OutHit;
	FVector Start = PlayerCameraManager->GetCameraLocation();
	FVector End = Start + (AimDirection * ShootingRange);

	if (GetWorld()->LineTraceSingleByChannel(OutHit,
		Start,
		End,
		ECC_Visibility)) {
		HitLocation = OutHit.Location;
		return true;
	}

	HitLocation = FVector(0.f);
	return false;
}

bool ATankPlayerController::GetSightRayHitLocation(FVector &HitLocation) const
{
	FVector AimDirection;

	GetAimDirection(AimDirection);
	return (GetAimVectorHitLocation(HitLocation, AimDirection));
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	auto AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(AimingComponent)) { FoundAimingComponent(AimingComponent); }
	else { UE_LOG(LogTemp, Warning, TEXT("Player controller can't find aiming component at Begin Play")) }
}

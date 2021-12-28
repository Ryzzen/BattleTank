// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPawn()) { return;  }

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	FoundAimingComponent(AimingComponent);

	FVector HitLocation;

	bool bGotHitLocation = GetSightRayHitLocation(HitLocation);
	UE_LOG(LogTemp, Warning, TEXT("Result %i"), bGotHitLocation)

	if (bGotHitLocation) {
		AimingComponent->AimAt(HitLocation);
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

	if (GetAimDirection(AimDirection))
		return (GetAimVectorHitLocation(HitLocation, AimDirection));
	return false;
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (!GetPawn()) { return;  }

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(AimingComponent)) { FoundAimingComponent(AimingComponent); }
}

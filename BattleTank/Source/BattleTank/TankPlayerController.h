// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	float CrosshairXLocation = 0.5;

	UPROPERTY(EditAnywhere)
	float CrosshairYLocation = 0.5;

	UPROPERTY(EditAnywhere)
	float ShootingRange = 100000;

private:
	void AimTowardsCrosshair();
	ATank* GetControlledTank() const;
	bool GetSightRayHitLocation(FVector& HitLocation) const;
	bool GetAimDirection(FVector& AimDirection) const;
	bool GetAimVectorHitLocation(FVector& HitLocation, FVector AimDirection) const;
};

// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	float ElevationChange = RelativeSpeed *
		MaxDegreesPerSeconds *
		GetWorld()->DeltaTimeSeconds;
	float Rotation = GetRelativeRotation().Yaw + ElevationChange;

	SetRelativeRotation(FRotator(0, Rotation, 0));
}
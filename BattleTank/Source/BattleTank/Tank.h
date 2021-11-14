// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "BattleTank/TankMovementComponent.h"
#include "BattleTank/TankBarrel.h"
#include "BattleTank/TankTurret.h"
#include "BattleTank/Projectile.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankMovementComponent;
class UTankBarrel;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	void BeginPlay();	

	UFUNCTION(BlueprintCallable, Category = Action)
	void Fire();


private:

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBluePrint;

	UTankBarrel* Barrel = nullptr;

	float ReloadTimeInSeconds = 3.f;
	double LastFiredTime = 0;
};
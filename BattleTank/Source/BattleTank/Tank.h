// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "BattleTank/TankBarrel.h"
#include "BattleTank/TankTurret.h"
#include <BattleTank/TankAimingComponent.h>
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankAimingComponent;
class UTankBarrel;
class UTankTurret;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	UFUNCTION(BlueprintCallable, Category=Setup)
	void SetTurretSystemReference(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	void AimAt(FVector HitLocation);
	UTankAimingComponent* TankAimingComponent = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 4000; // TODO: Playtest default value
};
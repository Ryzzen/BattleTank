// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BattleTank/TankBarrel.h"
#include "BattleTank/TankTurret.h"
#include "Kismet/GameplayStatics.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class ATank;
class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;

UENUM()
enum class EFiringState : uint8 {
	Locked,
	Aiming,
	Reloading
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTankAimingComponent();

	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	void AimAt(FVector& Target, float LaunchSpeed);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = State)
	EFiringState FiringState = EFiringState::Aiming;


private:
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	void MoveTurretSystem(const FVector& AimDirection);
};
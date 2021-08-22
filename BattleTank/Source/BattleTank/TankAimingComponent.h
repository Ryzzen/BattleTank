// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BattleTank/TankBarrel.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class ATank;
class UTankBarrel;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void SetBarrelReference(UTankBarrel* BarrelToSet);

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void AimAt(FVector& Target, float LaunchSpeed);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	

private:
	UTankBarrel* Barrel = nullptr;
	void MoveBarrel(const FVector& AimDirection);
};

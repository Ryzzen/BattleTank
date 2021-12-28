// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TankAimingComponent.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:

protected:
	UPROPERTY(EditAnywhere, Category="Setup")
	float AcceptanceRadius = 80000.0;

private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};



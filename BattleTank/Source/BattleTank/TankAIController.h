// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ATank* GetControlledTank() const;

private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	ATank* GetPlayerTank() const;

	float AcceptanceRadius = 3000;
};



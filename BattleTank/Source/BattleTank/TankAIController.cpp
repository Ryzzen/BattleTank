// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto Player = GetWorld()->GetFirstPlayerController();

	if (Player)
		return Cast<ATank>(Player->GetPawn());
	return nullptr;
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto Tank = GetControlledTank();
	auto Player = GetPlayerTank();

	if (Player)
		UE_LOG(LogTemp, Warning, TEXT("Player is possessin %s"), *(Player->GetName()));
	if (Tank)
		UE_LOG(LogTemp, Warning, TEXT("AI possessing %s"), *(Tank->GetName()));
}
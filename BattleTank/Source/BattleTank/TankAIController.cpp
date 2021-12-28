// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto Tank = GetPawn();
	if (!ensure(Tank)) return;
	auto AimingComponent = Tank->FindComponentByClass<UTankAimingComponent>();

	if (!ensure(AimingComponent && PlayerTank)) return;
	FVector HitLocation;

	// moving part
	MoveToActor(PlayerTank, AcceptanceRadius);

	// Aiming part
	AimingComponent->AimAt(PlayerTank->GetActorLocation());
	if (AimingComponent->GetFiringState() == EFiringState::Locked)
		AimingComponent->Fire();

//	UE_LOG(LogTemp, Warning, TEXT("fires at %s"), *(PlayerTank->GetActorLocation().ToString()));
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}
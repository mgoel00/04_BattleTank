// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankAIController.h"
#include "WorldInfoProvider.h"
#include "Tank.h" // So we can impliment OnDeath

// Depends on movement component via pathfinding system

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	ControlledTank = GetPawn();
	AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), "InfoAgent", WorldInfoProviders);
	WorldInfoProvider = Cast<AWorldInfoProvider>(WorldInfoProviders[0]);
	GetEnemyTank();
}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!(ensure(TankToAim && ControlledTank))) { return; }

	if (bFollowOverlapLogic)
	{
		UE_LOG(LogTemp, Warning, TEXT("Follow the other path"));
	}
	else
	{
		// Move towards the player
		MoveToActor(TankToAim, AcceptanceRadius);
	}

	// Aim towards the player

	AimingComponent->AimAt(TankToAim->GetActorLocation());
	AimingComponent->Fire(); // TODO limit firing rate
}

void ATankAIController::GetEnemyTank()
{
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), "MyTank", EnemyTanks);
	TankToAim = EnemyTanks[0];
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!PossessedTank) { return; }

		// Subscribe our local method to the tank's death event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossedTankDeath);
		PossessedTank->OverlapOccured.AddUniqueDynamic(this, &ATankAIController::AvoidObstacles);
	}
}

void ATankAIController::OnPossedTankDeath()
{
	if (!ensure(GetPawn())) { return; } // TODO remove if ok
	GetPawn()->DetachFromControllerPendingDestroy();
}

void ATankAIController::AvoidObstacles()
{
	bFollowOverlapLogic = true;
}
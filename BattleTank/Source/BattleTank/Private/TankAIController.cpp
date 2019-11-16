// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankAIController.h"
#include "WorldInfoProvider.h"
#include "DrawDebugHelpers.h"
#include "Tank.h" // So we can impliment OnDeath

// Depends on movement component via pathfinding system

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	ControlledTank = GetPawn();
	CastedControlledTank = Cast<ATank>(ControlledTank);
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
	UE_LOG(LogTemp, Warning, TEXT("%i"), bFollowOverlapLogic);
	if (bFollowOverlapLogic)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Follow the other path"));
		MoveToLocation(PositionToAvoidObstacles, 500.0f);
	}
	else
	{
		// Move towards the player
		DistanceFromCurrentTarget = FVector::Dist(TankToAim->GetActorLocation(), ControlledTank->GetActorLocation());
		if (DistanceFromCurrentTarget >= SafeDistance)
		{
			//UE_LOG(LogTemp, Warning, TEXT("Following target"));
			MoveToActor(TankToAim, AcceptanceRadius);
		}
		else
			StopMovement();
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
	FindPositionToAvoidCollision();
	bFollowOverlapLogic = true;
}

void ATankAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	//UE_LOG(LogTemp, Warning, TEXT("Move Completed"));
	//bFollowOverlapLogic = false;
}

void ATankAIController::FindPositionToAvoidCollision()
{
	USceneComponent* SceneComponentOfControlledTank = ControlledTank->FindComponentByClass<USceneComponent>();
	USceneComponent* SceneComponentOfOverlapedTank = CastedControlledTank->GetOverlapedActor()->FindComponentByClass<USceneComponent>();
	FHitResult HitResult;
	FVector Start = ControlledTank->GetActorLocation() + FVector(0.0f,0.0f,100.0f);
	FVector End = Start + (SceneComponentOfOverlapedTank->GetForwardVector().GetSafeNormal() - SceneComponentOfControlledTank->GetForwardVector().GetSafeNormal()).GetSafeNormal()*1000.0f;
	GetWorld()->LineTraceSingleByChannel(HitResult,Start,End,ECollisionChannel::ECC_Visibility);
	DrawDebugLine(GetWorld(),Start,End,FColor::Blue,false,2.0f);
}

void ATankAIController::SetBoolenForPathFollowingWhenOverlapEnds(bool bFollowOrNot)
{
	bFollowOverlapLogic = bFollowOrNot;
	UE_LOG(LogTemp, Warning, TEXT("Overlap ended: %i"),bFollowOrNot);
}
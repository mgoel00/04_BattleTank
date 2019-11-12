// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
class UTankAimingComponent;
class ATank;
class AWorldInfoProvider;

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:
	void OnMoveCompleted( FAIRequestID RequestID, const FPathFollowingResult& Result);

protected:
	// How close can the AI tank get
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float AcceptanceRadius = 1000.0f;

	FVector PositionToAvoidObstacles;

	float SafeDistance = 3000.0f;

	float DistanceFromCurrentTarget;

private:
	virtual void BeginPlay() override;

	virtual void SetPawn(APawn* InPawn) override;

	virtual void Tick(float DeltaSeconds) override;

	void GetEnemyTank();

	UFUNCTION()
	void OnPossedTankDeath();

	UFUNCTION()
	void AvoidObstacles();

	void FindPositionToAvoidCollision();

private:

	UTankAimingComponent* AimingComponent = nullptr;

	APawn* ControlledTank = nullptr;

	ATank* CastedControlledTank = nullptr;

	AActor* TankToAim = nullptr;

	TArray<AActor*> EnemyTanks;

	TArray<AActor*> WorldInfoProviders;

	AWorldInfoProvider* WorldInfoProvider = nullptr;

	bool bFollowOverlapLogic = false;
};
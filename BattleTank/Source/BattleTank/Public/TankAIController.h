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

protected:
	// How close can the AI tank get
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float AcceptanceRadius = 8000.0f;

private:
	virtual void BeginPlay() override;

	virtual void SetPawn(APawn* InPawn) override;

	virtual void Tick(float DeltaSeconds) override;

	void GetEnemyTank();

	UFUNCTION()
	void OnPossedTankDeath();

	UFUNCTION()
	void AvoidObstacles();

	UTankAimingComponent* AimingComponent = nullptr;

	APawn* ControlledTank = nullptr;

	AActor* TankToAim = nullptr;

	TArray<AActor*> EnemyTanks;

	TArray<AActor*> WorldInfoProviders;

	AWorldInfoProvider* WorldInfoProvider = nullptr;

	bool bFollowOverlapLogic = false;
};
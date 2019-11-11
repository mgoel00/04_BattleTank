// Copyright EmbraceIT Ltd.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyAIController.generated.h"

/**
 * 
 */

class UTankAimingComponent;
class ATank;
class AWorldInfoProvider;

UCLASS()
class BATTLETANK_API AMyAIController : public AAIController
{
	GENERATED_BODY()

private:
	virtual void BeginPlay() override;

	virtual void SetPawn(APawn* InPawn) override;

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
	void OnPossessedTankDeath();

	UFUNCTION()
	void GetEnemyTanks();

	AActor* GetNearestTank();
	
public:

private:
	UTankAimingComponent* AimingComponent = nullptr;

	APawn* ControlledTank = nullptr;
	ATank* CastedControlledTank = nullptr;

	TArray<AActor*> EnemyTanks;

	AActor* TankToAim = nullptr;

	float ClosestTankDistanceComparisonDefaultValue = 200000.0f;

	float MaxRangeToAttack = 20000.0f;

	bool bInRange = true;

	float DistanceFromCurrentEnemy;

	TArray<AActor*> WorldInfoProviders;

	AWorldInfoProvider* WorldInfoProvider = nullptr;
};

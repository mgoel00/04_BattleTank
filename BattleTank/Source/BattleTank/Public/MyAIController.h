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

UCLASS()
class BATTLETANK_API AMyAIController : public AAIController
{
	GENERATED_BODY()

private:
	virtual void BeginPlay() override;

	virtual void SetPawn(APawn* InPawn) override;

	virtual void Tick(float DeltaSeconds) override;

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
};

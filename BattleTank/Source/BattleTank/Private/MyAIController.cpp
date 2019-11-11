// Copyright EmbraceIT Ltd.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "MyAIController.h"


void AMyAIController::BeginPlay()
{
	Super::BeginPlay();

	ControlledTank = GetPawn();
	CastedControlledTank = Cast<ATank>(ControlledTank);
	AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	GetEnemyTanks();
}

void AMyAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (CastedControlledTank && AimingComponent)
	{

		MoveToLocation(CastedControlledTank->GetLocationPointedByMouse(), 500.0f);

		//Aiming and Fire
		if (TankToAim)
		{
			AimingComponent->AimAt(TankToAim->GetActorLocation());
			AimingComponent->Fire();
		}
		else
		{
			//Get the nearest tank
			ClosestTankDistanceComparisonDefaultValue = 200000.0f;
			TankToAim = GetNearestTank();
		}
	}

	
}

void AMyAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

}

void AMyAIController::GetEnemyTanks()
{
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), "EnemyTank", EnemyTanks);
}

AActor* AMyAIController::GetNearestTank()
{
	if (EnemyTanks.Num())
	{
		//Return the nearest tank
		AActor* RequiredActor = nullptr;
		for (AActor* Tank : EnemyTanks)
		{
			float DistanceBetweenTanks = FVector::Dist(Tank->GetActorLocation(), ControlledTank->GetActorLocation());
			if (DistanceBetweenTanks <= ClosestTankDistanceComparisonDefaultValue)
			{
				ClosestTankDistanceComparisonDefaultValue = DistanceBetweenTanks;
				RequiredActor = Tank;
			}
		}
		return RequiredActor;
	}
	else
		return nullptr;
}
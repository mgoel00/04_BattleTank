// Copyright EmbraceIT Ltd.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "WorldInfoProvider.h"
#include "MyAIController.h"


void AMyAIController::BeginPlay()
{
	Super::BeginPlay();

	ControlledTank = GetPawn();
	CastedControlledTank = Cast<ATank>(ControlledTank);
	AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), "InfoAgent", WorldInfoProviders);
	WorldInfoProvider = Cast<AWorldInfoProvider>(WorldInfoProviders[0]);
	WorldInfoProvider->EnemyTankDiedSignal.AddUniqueDynamic(this, &AMyAIController::GetEnemyTanks);
	GetEnemyTanks();
}

void AMyAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (CastedControlledTank && AimingComponent)
	{

		MoveToLocation(CastedControlledTank->GetLocationPointedByMouse(), 500.0f);

		//Aiming and Fire
		if (ensure(TankToAim) && bInRange)
		{
			AimingComponent->AimAt(TankToAim->GetActorLocation());
			AimingComponent->Fire();
			DistanceFromCurrentEnemy = FVector::Dist(TankToAim->GetActorLocation(), ControlledTank->GetActorLocation());
			if (DistanceFromCurrentEnemy > MaxRangeToAttack)
				bInRange = false;
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
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!PossessedTank) { return; }

		// Subscribe our local method to the tank's death event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &AMyAIController::OnPossessedTankDeath);
	}
}

void AMyAIController::GetEnemyTanks()
{
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), "EnemyTank", EnemyTanks);
	bInRange = false;
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
		bInRange = true;
		return RequiredActor;
	}
	else
		return nullptr;
}

void AMyAIController::OnPossessedTankDeath()
{
	if (!ensure(GetPawn())) { return; }
	GetPawn()->DetachFromControllerPendingDestroy();
}

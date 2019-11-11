// Copyright EmbraceIT Ltd.

#include "BattleTank.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "StrategyController.h"

void AStrategyController::SetSelectedTank(AActor* PointedActor)
{
	SelectedTank = Cast<ATank>(PointedActor);
}

void AStrategyController::SetLocation(FVector Location)
{
	if (SelectedTank)
	{
		SelectedTank->SetPointedLocation(Location);
	}
	SelectedTank = nullptr;
}
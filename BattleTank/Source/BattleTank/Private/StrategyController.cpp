// Copyright EmbraceIT Ltd.

#include "BattleTank.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "StrategyController.h"

void AStrategyController::SetSelectedTank(AActor* PointedActor)
{
	UE_LOG(LogTemp, Warning, TEXT("Tank Selected"));
	SelectedTank = Cast<ATank>(PointedActor);
}

void AStrategyController::SetLocation(FVector Location)
{
	if (SelectedTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Setting location on tank"));
		SelectedTank->SetPointedLocation(Location);
	}
	SelectedTank = nullptr;
}
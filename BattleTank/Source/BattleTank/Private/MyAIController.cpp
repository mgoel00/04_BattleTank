// Copyright EmbraceIT Ltd.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "MyAIController.h"


void AMyAIController::BeginPlay()
{
	Super::BeginPlay();

	ControlledTank = GetPawn();
	AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();

}

void AMyAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AMyAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

}
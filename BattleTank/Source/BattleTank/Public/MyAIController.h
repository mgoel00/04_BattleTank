// Copyright EmbraceIT Ltd.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyAIController.generated.h"

/**
 * 
 */

class UTankAimingComponent;

UCLASS()
class BATTLETANK_API AMyAIController : public AAIController
{
	GENERATED_BODY()

private:
	virtual void BeginPlay() override;

	virtual void SetPawn(APawn* InPawn) override;

	virtual void Tick(float DeltaSeconds) override;
	
public:

private:
	UTankAimingComponent* AimingComponent = nullptr;

	APawn* ControlledTank = nullptr;
};

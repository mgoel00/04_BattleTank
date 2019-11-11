// Copyright EmbraceIT Ltd.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "StrategyController.generated.h"

/**
 * 
 */

class ATank;

UCLASS()
class BATTLETANK_API AStrategyController : public APlayerController
{
	GENERATED_BODY()
	
public:


private:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetSelectedTank(AActor* PointedActor);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetLocation(FVector Location);
	
private:

	ATank* SelectedTank;
};

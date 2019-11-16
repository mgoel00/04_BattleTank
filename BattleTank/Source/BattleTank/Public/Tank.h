// Copyright EmbraceIT Ltd.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h" // Put new includes above

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankOverlapInfo);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Called by the engine when actor damage is dealt
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

	// Return current health as a percentage of starting health, between 0 and 1
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const;

	FTankDelegate OnDeath;

	FTankOverlapInfo OverlapOccured;
	

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetPointedLocation(FVector Location);

	//Gets the location pointed by mouse
	FVector GetLocationPointedByMouse() const;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SendOverlapSingal();

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetOverlapedActor(AActor* Actor);

	AActor* GetOverlapedActor() const;


private:
	// Sets default values for this pawn's properties
	ATank();

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 StartingHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth; // Initialised in Begin Play

	FVector LocationPointedByMouse;

	AActor* OverlapedActor = nullptr;

};

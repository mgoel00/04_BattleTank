// Copyright EmbraceIT Ltd.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WorldInfoProvider.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDied);

UCLASS()
class BATTLETANK_API AWorldInfoProvider : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWorldInfoProvider();

	FTankDied EnemyTankDiedSignal;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	void EstablishDelegateSystem();

	void RefreshTheList();

	UFUNCTION()
	void EnemyTankDied();

	UFUNCTION()
	void FriendlyTankDied();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	TArray<AActor*> EnemyTanks;
	TArray<AActor*> MyTanks;
};

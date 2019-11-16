// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"


float ATank::GetHealthPercent() const
{
	return (float)CurrentHealth / (float)StartingHealth;
}

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = StartingHealth;
	LocationPointedByMouse = GetActorLocation();
}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);

	CurrentHealth -= DamageToApply;
	if (CurrentHealth <= 0)
	{
		if (Tags.Num())
		{
			Tags.Pop();
			OnDeath.Broadcast();
		}
	}
	return DamageToApply;
}

void ATank::SetPointedLocation(FVector Location)
{
	LocationPointedByMouse = Location;
}

void ATank::SetOverlapedActor(AActor * Actor)
{
	OverlapedActor = Actor;
}

FVector ATank::GetLocationPointedByMouse() const
{
	return LocationPointedByMouse;
}

void ATank::SendOverlapSingal()
{
	ATank* IsTank = Cast<ATank>(OverlapedActor);
	if (IsTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Overlaped with %s"), *OverlapedActor->GetName());
		OverlapOccured.Broadcast();
	}
}

AActor* ATank::GetOverlapedActor() const
{
	return OverlapedActor;
}
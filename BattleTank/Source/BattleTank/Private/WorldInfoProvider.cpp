// Copyright EmbraceIT Ltd.

#include "BattleTank.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "WorldInfoProvider.h"


// Sets default values
AWorldInfoProvider::AWorldInfoProvider()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWorldInfoProvider::BeginPlay()
{
	Super::BeginPlay();
	RefreshTheList();
	EstablishDelegateSystem();
	TankAssigningList = MyTanks;
}

// Called every frame
void AWorldInfoProvider::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AWorldInfoProvider::RefreshTheList()
{
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), "EnemyTank", EnemyTanks);
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), "MyTank", MyTanks);

}

void AWorldInfoProvider::EnemyTankDied()
{
	EnemyTankDiedSignal.Broadcast();
	RefreshTheList();
}

void AWorldInfoProvider::FriendlyTankDied()
{
	RefreshTheList();
	//Assign new tank to TankAIController
}

void AWorldInfoProvider::EstablishDelegateSystem()
{
	for (AActor* TankActors : EnemyTanks)
	{
		ATank* Tank = Cast<ATank>(TankActors);
		Tank->OverlapOccured.AddUniqueDynamic(this, &AWorldInfoProvider::EnemyTankDied);
	}
	for (AActor* TankActors : MyTanks)
	{
		ATank* Tank = Cast<ATank>(TankActors);
		Tank->OverlapOccured.AddUniqueDynamic(this, &AWorldInfoProvider::FriendlyTankDied);
	}
}


///Buggy! Be Careful!
/*AActor* AWorldInfoProvider::AssignTank()
{
	AActor* TargetTank = nullptr;
	switch(NumberOfTanksToTarget){
	case 3:
		if (MyTanks.Num() == 3 && EnemyTanks.Num() == 3)
		{
			TargetTank = TankAssigningList.Pop();
			break;
		}
		UE_LOG(LogTemp, Warning, TEXT("Going to 2"));
	case 2:
		if ((EnemyTanks.Num() - MyTanks.Num()) >= 1)
		{

			break;
		}
	case 1:
		if (MyTanks.Num())
		{
			TargetTank = MyTanks[0];
			break;
		}
		UE_LOG(LogTemp, Warning, TEXT("Going to 1"));
	default:
		break;
	}
	return TargetTank;
}*/
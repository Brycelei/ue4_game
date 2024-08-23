// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyPawn.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AEnemyPawn::AEnemyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpawArea = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawArea"));
	RootComponent = SpawArea;
	SpawArea->SetBoxExtent(FVector(10000.f, 10000.f, 100.f));
}

void AEnemyPawn::SpawnEnemy()
{
	FVector origin;
	FVector Extends;
	this->GetActorBounds(false, origin, Extends);
	FVector SpawnPoint = UKismetMathLibrary::RandomPointInBoundingBox(origin, Extends);
	GetWorld()->SpawnActor<AEnemy>(EnemyType, SpawnPoint,FRotator::ZeroRotator);
}

// Called when the game starts or when spawned
void AEnemyPawn::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(SpawnHandle, this, &AEnemyPawn::SpawnEnemy, spawnBorn, true);
}

// Called every frame
void AEnemyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


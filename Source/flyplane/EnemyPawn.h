// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Enemy.h"
#include "EnemyPawn.generated.h"
UCLASS()
class FLYPLANE_API AEnemyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemyPawn();
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* SpawArea;


	UPROPERTY(EditAnywhere)
	TSubclassOf<AEnemy> EnemyType;

	UPROPERTY(EditAnywhere) // ���ɼ��
		float spawnBorn = 1.0f;

	UFUNCTION()
	void SpawnEnemy();

private:
	FTimerHandle SpawnHandle;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

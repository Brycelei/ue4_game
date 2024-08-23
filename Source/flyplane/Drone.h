// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Missle.h"
#include "Drone.generated.h"

UCLASS()
class FLYPLANE_API ADrone : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADrone();

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent * OutCollision;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* Paddle1;
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* Paddle2;
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* Paddle3;
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* Paddle4;
	UPROPERTY(VisibleAnywhere)
	class UPhysicsThrusterComponent* UpThruster; // 向上
	UPROPERTY(VisibleAnywhere)
	class UPhysicsThrusterComponent* ForwardThruster; // 向前

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Init")
	float Liftacc = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Init")
	float LiftTHrustMax = 2000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Init")
	float Forwardacc = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Init")
	float ForwardTHrustMax = 2000.0f;

	// 转动角度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Init")
	float TurnStrength = 500000.0f;

	// 转动速度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Init")
	float PaddleRotateSpeed = 500.0f;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AMissle> Bullet;

private:
	UFUNCTION()
	void Lift(float values);
	UFUNCTION()
	void Forward(float values);
	UFUNCTION()
	void Turn(float values);
	UFUNCTION()
	void doFile();

	TArray<UStaticMeshComponent*> Paddles;
	void RotatePaddle(float Delta);

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

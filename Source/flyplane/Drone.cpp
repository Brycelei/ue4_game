// Fill out your copyright notice in the Description page of Project Settings.


#include "Drone.h"
#include "Components/BoxComponent.h"
#include "PhysicsEngine/PhysicsThrusterComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/InputComponent.h"


// Sets default values
ADrone::ADrone()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OutCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("OutCollision"));
	//keep aline

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = OutCollision;
	OutCollision->SetBoxExtent(FVector(100.f, 100.f, 100.f));
	OutCollision->SetSimulatePhysics(true);
	//OutCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	OutCollision->BodyInstance.bLockXRotation = true;
	OutCollision->BodyInstance.bLockYRotation = true;
	// 灰机
	Mesh->SetupAttachment(OutCollision); // 设置灰机可以碰撞

	Paddle1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Paddle1"));
	Paddle2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Paddle2"));
	Paddle3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Paddle3"));
	Paddle4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Paddle4"));

	Paddle1->SetupAttachment(Mesh, TEXT("Paddle1"));
	Paddle2->SetupAttachment(Mesh, TEXT("Paddle2"));
	Paddle3->SetupAttachment(Mesh, TEXT("Paddle3"));
	Paddle4->SetupAttachment(Mesh, TEXT("Paddle4"));

	Paddles.Add(Paddle1);
	Paddles.Add(Paddle2);
	Paddles.Add(Paddle3);
	Paddles.Add(Paddle4);
	
	// 初始化向上的推力
	UpThruster = CreateDefaultSubobject<UPhysicsThrusterComponent>(TEXT("UpThruster"));
	UpThruster->SetupAttachment(RootComponent); // 连接到根组件上

	UpThruster->ThrustStrength = 980.0f;
	UpThruster->SetAutoActivate(true); // 开启向上推
	UpThruster->SetWorldRotation(UKismetMathLibrary::MakeRotFromX(-this->GetActorUpVector())); // 朝下

	ForwardThruster = CreateDefaultSubobject<UPhysicsThrusterComponent>(TEXT("ForwardThruster"));
	ForwardThruster->SetupAttachment(RootComponent);
	ForwardThruster->ThrustStrength = 0.0f;
	ForwardThruster->SetAutoActivate(true);
	ForwardThruster->SetWorldRotation(UKismetMathLibrary::MakeRotFromX(-this->GetActorForwardVector())); // 朝后

}

void ADrone::Lift(float values)
{
	UpThruster->ThrustStrength += values * Liftacc * GetWorld()->DeltaTimeSeconds;
	UpThruster->ThrustStrength = FMath::Clamp(UpThruster->ThrustStrength, -LiftTHrustMax, LiftTHrustMax);
}

void ADrone::Forward(float values)
{
	ForwardThruster->ThrustStrength += values * Forwardacc * GetWorld()->DeltaTimeSeconds;
	ForwardThruster->ThrustStrength = FMath::Clamp(ForwardThruster->ThrustStrength, -ForwardTHrustMax, ForwardTHrustMax);

	float pitch = Mesh->GetRelativeRotation().Pitch;
	if (FMath::Abs(pitch) < 30.0f) {
		Mesh->AddRelativeRotation(FRotator(-100.0f * GetWorld()->DeltaTimeSeconds * values, 0.0f, 0.0f));
	}
}

void ADrone::Turn(float values)
{
	OutCollision->AddTorqueInDegrees(-this->GetActorUpVector() * values * TurnStrength);
}

void ADrone::doFile()
{
	FTransform firePoint = Mesh->GetSocketTransform(TEXT("FireSocket"));
	GetWorld()->SpawnActor<AMissle>(Bullet, firePoint);
}

void ADrone::RotatePaddle(float Delta)
{
	for (UStaticMeshComponent* paddle : Paddles)
	{
		paddle->AddRelativeRotation(FRotator(0.f, Delta * PaddleRotateSpeed, 0.0f));
	}
}

// Called when the game starts or when spawned
void ADrone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetInputAxisValue(TEXT("Lift")) == 0.0f) {
		UpThruster->ThrustStrength = 980.0f;
	}
	if (GetInputAxisValue(TEXT("Forward")) == 0.0f) {
		ForwardThruster->ThrustStrength = 0.0f;

		if (Mesh->GetRelativeRotation().Pitch != 0.0f) {
			float currentPitch = Mesh->GetRelativeRotation().Pitch;
			Mesh->AddRelativeRotation(FRotator(-currentPitch * DeltaTime * 2.0, 0.0f, 0.0f));

			//if (FMath::Abs(Mesh->GetRelativeRotation().Pitch <= KINDA_SMALL_NUMBER) {
			if (FMath::Abs(Mesh->GetRelativeRotation().Pitch) <= KINDA_SMALL_NUMBER) {
				Mesh->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
			}
		}
	}
	RotatePaddle(DeltaTime);
}

// Called to bind functionality to input
void ADrone::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//PlayerInputComponent->BindAction();// 一般是动作
	PlayerInputComponent->BindAxis(TEXT("Lift"), this, &ADrone::Lift);//持续的动作
	PlayerInputComponent->BindAxis(TEXT("Forward"), this, &ADrone::Forward);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ADrone::Turn);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed,this, &ADrone::doFile);

}


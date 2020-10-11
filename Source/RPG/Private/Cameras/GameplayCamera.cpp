// Fill out your copyright notice in the Description page of Project Settings.

#include "Cameras/GameplayCamera.h"

// Sets default values
AGameplayCamera::AGameplayCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	RootComponent = SceneComponent;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(SceneComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

}

// Called when the game starts or when spawned
void AGameplayCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGameplayCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateGameplayCamera();

	UpdateGameplayCameraRotation();

}

void AGameplayCamera::UpdateGameplayCamera()
{
	if (TargetActor != nullptr)
	{
		SetActorLocation(TargetActor->GetActorLocation());

		
	}
}

void AGameplayCamera::UpdateGameplayCameraRotation()
{
	FRotator NewYawRotation = GetActorRotation();
	NewYawRotation.Yaw += CameraInputVector.X;
	SetActorRotation(NewYawRotation);

	FRotator NewPitchRotation = SpringArmComponent->GetComponentRotation();
	NewPitchRotation.Pitch = FMath::Clamp(NewPitchRotation.Pitch + CameraInputVector.Y, MinPitchRotation, MaxPitchRotation);
	SpringArmComponent->SetWorldRotation(NewPitchRotation);
}


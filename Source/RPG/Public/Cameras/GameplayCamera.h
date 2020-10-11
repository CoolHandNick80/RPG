// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"
#include "GameFramework/SpringArmComponent.h "
#include "Camera/CameraComponent.h"
#include "GameplayCamera.generated.h"

UCLASS()
class RPG_API AGameplayCamera : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameplayCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	
	UPROPERTY()
		USceneComponent* SceneComponent = nullptr;

	UPROPERTY(VisibleAnywhere)
		USpringArmComponent* SpringArmComponent = nullptr;

	UPROPERTY(VisibleAnywhere)
		UCameraComponent* CameraComponent = nullptr;

	UPROPERTY()
		AActor* TargetActor = nullptr;

	UPROPERTY(EditDefaultsOnly)
		float MaxPitchRotation = 15.F;

	UPROPERTY(EditDefaultsOnly)
		float MinPitchRotation = -80.F;


public:

	void SetTargetActor(AActor*InTargetActor) { TargetActor = InTargetActor; }

protected:

	void UpdateGameplayCamera();

	void UpdateGameplayCameraRotation();

public:

	UPROPERTY()
		FVector CameraInputVector = FVector::ZeroVector;


};

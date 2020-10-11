// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "PlayerPawnMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API UPlayerPawnMovementComponent : public UFloatingPawnMovement
{
	GENERATED_BODY()

public:

	UPROPERTY()
		FVector MovementInputVector = FVector::ZeroVector;
	
	UPROPERTY()
		FRotator LastValidRotation = FVector::ForwardVector.Rotation();

	UPROPERTY(EditAnywhere)
		float RotationSpeed = 12.F;
};

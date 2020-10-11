// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerPawnController.generated.h"

class APlayerPawn;
class UPlayerPawnMovementComponent;
class ARPGGameModeBase;
class AGameplayCamera;
class UPlayerFSMComponent;

/**
 * 
 */
UCLASS()
class RPG_API APlayerPawnController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	UPROPERTY()
		APlayerPawn* PlayerPawn = nullptr;

	UPROPERTY()
		UPlayerPawnMovementComponent* PlayerPawnMovementComponent = nullptr;

	UPROPERTY()
		ARPGGameModeBase* GameMode = nullptr;

	UPROPERTY()
		AGameplayCamera* GameplayCamera = nullptr;

	UPROPERTY()
		UPlayerFSMComponent* PlayerFSMComponent = nullptr;

protected:

	virtual void OnPossess(APawn* InPawn) override;

	virtual void SetupInputComponent() override;

	void MoveRight(float AxisValue);

	void MoveForward(float AxisValue);

	void PitchCamera(float AxisValue);

	void YawCamera(float AxisValue);

	void Jump();

	void DropItem();

	UFUNCTION()
		void AssignGamplayCamera();
};

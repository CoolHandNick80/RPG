// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Interfaces/PlayerPawnState.h"
#include "PlayerPawn.h"
#include "Cameras/GameplayCamera.h"
#include "RPGGameModeBase.h"
#include "PPState_FALLING.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API UPPState_FALLING : public UObject, public IPlayerPawnState
{
	GENERATED_BODY()
	
public:

	/* Begin IPlayerPawnState */

	virtual void Init(UPlayerFSMComponent* InPlayerFSMComponent) override;
	virtual void Enter() override;
	virtual void Execute(float DeltaSeconds) override;
	virtual void Exit() override;
	virtual EPlayerPawnState GetStateEnum() { return EPlayerPawnState::FALLING; }
	virtual const FString GetStateString() { return "FALLING"; }

	/* End IPlayerPawnState*/

protected:

	UPROPERTY()
		UPlayerFSMComponent* PlayerFSMComponent = nullptr;

	UPROPERTY()
		APlayerPawn* PlayerPawn = nullptr;

	UPROPERTY()
		UPlayerPawnMovementComponent* PlayerPawnMovementComponent = nullptr;

	UPROPERTY()
		UPlayerAnimInstance* AnimInstance = nullptr;

	UPROPERTY()
		ARPGGameModeBase* GameMode = nullptr;

	UPROPERTY()
		AGameplayCamera* GameplayCamera = nullptr;

protected:

	void SetupData();

	void CheckGround();

protected:

	UFUNCTION()
		void AssignGameplayCamera();
};

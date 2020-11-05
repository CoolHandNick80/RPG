// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Interfaces/PlayerPawnState.h"
#include "Pawns/PlayerPawn.h"
#include "TimerManager.h"
#include "PPState_ROLL.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API UPPState_ROLL : public UObject, public IPlayerPawnState
{
	GENERATED_BODY()
	
public:

	/* Begin IPlayerPawnState */

	virtual void Init(UPlayerFSMComponent* InPlayerFSMComponent) override;
	virtual void Enter() override;
	virtual void Execute(float DeltaSeconds) override;
	virtual void Exit() override;
	virtual EPlayerPawnState GetStateEnum() { return EPlayerPawnState::ROLL; }
	virtual const FString GetStateString() { return "ROLL"; }

	/* End IPlayerPawnState */

protected:

	UPROPERTY()
		UPlayerFSMComponent* PlayerFSMComponent = nullptr;

	UPROPERTY()
		APlayerPawn* PlayerPawn = nullptr;

	UPROPERTY()
		UPlayerPawnMovementComponent* MovementComponent = nullptr;

	UPROPERTY()
		UPlayerAnimInstance* AnimInstance = nullptr;

	UPROPERTY()
		FTimerHandle RollTimerHandle;

	UPROPERTY()
		float Direction = 1.F;

	UPROPERTY()
		float RollAlpha = 0.F;


protected:

	void StartRollTimer();

	UFUNCTION()
		void UpdateRollTimer(FVector InStartVector, FVector InTargetVector);

	void StopRollTimer();

	void CheckGround();


};

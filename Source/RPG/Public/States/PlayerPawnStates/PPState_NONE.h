// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Interfaces/PlayerPawnState.h"
#include "PlayerPawn.h"
#include "PPState_NONE.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API UPPState_NONE : public UObject, public IPlayerPawnState
{
	GENERATED_BODY()

public:

	/* Begin IPlayerPawnState */

	virtual void Init(UPlayerFSMComponent* InPlayerFSMComponent) override;
	virtual void Enter() override;
	virtual void Execute(float DeltaSeconds) override;
	virtual void Exit() override;
	virtual EPlayerPawnState GetStateEnum() { return EPlayerPawnState::NONE; }
	virtual const FString GetStateString() { return "NONE"; }

	/* End IPlayerPawnState*/

protected:

	UPROPERTY()
		UPlayerFSMComponent* PlayerFSMComponent = nullptr;

	UPROPERTY()
		APlayerPawn* PlayerPawn = nullptr;

	UPROPERTY()
		UPlayerPawnMovementComponent* MovementComponent = nullptr;

	UPROPERTY()
		UPlayerAnimInstance* AnimInstance = nullptr;

protected:

	void SetupData();
	
	void CheckGround();
};

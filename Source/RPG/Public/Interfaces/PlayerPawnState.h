// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Globals/GlobalTypes.h"
#include "PlayerFSMComponent.h"
#include "PlayerPawnState.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPlayerPawnState : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RPG_API IPlayerPawnState
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void Init(UPlayerFSMComponent* InPlayerFSMComponent) = 0;
	virtual void Enter() = 0;
	virtual void Execute(float DeltaSeconds) = 0;
	virtual void Exit() = 0;
	virtual EPlayerPawnState GetStateEnum() = 0;
	virtual const FString GetStateString() = 0;
};

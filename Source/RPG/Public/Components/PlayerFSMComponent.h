// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Globals/GlobalTypes.h"
#include "PlayerFSMComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(PlayerFSMLog, Log, All);

class IPlayerPawnState;
class UPPState_NONE;
class UPPState_GROUNDED;
class UPPState_FALLING;
class UPPState_JUMP;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPG_API UPlayerFSMComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerFSMComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:

	UPROPERTY()
		TScriptInterface<IPlayerPawnState> CurrentState = nullptr;

	UPROPERTY()
		TScriptInterface<IPlayerPawnState> NextState = nullptr;

	UPROPERTY()
		EPlayerPawnState PreviousStateEnum = EPlayerPawnState::NONE;

	UPROPERTY()
		TArray<TScriptInterface<IPlayerPawnState>> States;

	/* State Objects */

	UPROPERTY()
		UPPState_NONE* State_NONE = nullptr;

	UPROPERTY()
		UPPState_GROUNDED* State_GROUNDED= nullptr;

	UPROPERTY()
		UPPState_FALLING* State_FALLING = nullptr;

	UPROPERTY()
		UPPState_JUMP* State_JUMP = nullptr;

	UPROPERTY(EditAnywhere)
		bool bShowDebug = false;

public:

	void ChangeState(EPlayerPawnState InNewState);

	EPlayerPawnState GetCurrentStateEnum();

	EPlayerPawnState GetPreviousStateEnum() { return PreviousStateEnum; }

	bool GetIsDebugActive() { return bShowDebug; }

protected:

	void SetupData();

	void CheckStateChange();

	void UpdateCurrentState(float DeltaSeconds);

};

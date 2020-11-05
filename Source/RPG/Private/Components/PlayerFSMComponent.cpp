// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerFSMComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "States/PlayerPawnStates/PPState_NONE.h"
#include "States/PlayerPawnStates/PPState_GROUNDED.h"
#include "States/PlayerPawnStates/PPState_FALLING.h"
#include "States/PlayerPawnStates/PPState_JUMP.h"
#include "States/PlayerPawnStates/PPState_ROLL.h"

DEFINE_LOG_CATEGORY(PlayerFSMLog);

// Sets default values for this component's properties
UPlayerFSMComponent::UPlayerFSMComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerFSMComponent::BeginPlay()
{
	Super::BeginPlay();

	SetupData();
	
}


// Called every frame
void UPlayerFSMComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateCurrentState(DeltaTime);

	if (bShowDebug == true && CurrentState != nullptr)
	{
		UKismetSystemLibrary::DrawDebugString(this, GetOwner()->GetActorLocation(), CurrentState->GetStateString(), nullptr, FColor::White, 0.001F);
	}
}

void UPlayerFSMComponent::ChangeState(EPlayerPawnState InNewState)
{
	switch (InNewState)
	{
	case EPlayerPawnState::NONE:
		NextState = State_NONE;
		break;
	case EPlayerPawnState::GROUNDED:
		NextState = State_GROUNDED;
		break;
	case EPlayerPawnState::FALLING:
		NextState = State_FALLING;
		break;
	case EPlayerPawnState::JUMP:
		NextState = State_JUMP;
		break;
	case EPlayerPawnState::ROLL:
		NextState = State_ROLL;
		break;
	default:
		break;
	}
}

EPlayerPawnState UPlayerFSMComponent::GetCurrentStateEnum()
{
	if (CurrentState != nullptr) return CurrentState->GetStateEnum();
	return EPlayerPawnState::NONE;
}

void UPlayerFSMComponent::SetupData()
{
	// Create State Objects
	State_NONE = NewObject <UPPState_NONE>(this);
	State_GROUNDED = NewObject <UPPState_GROUNDED>(this);
	State_FALLING = NewObject <UPPState_FALLING>(this);
	State_JUMP = NewObject <UPPState_JUMP>(this);
	State_ROLL = NewObject<UPPState_ROLL>(this);

	// Add to States
	States.Add(State_NONE);
	States.Add(State_GROUNDED);
	States.Add(State_FALLING);
	States.Add(State_JUMP);
	States.Add(State_ROLL);

	// Initialize States
	for (auto State : States)
	{
		State->Init(this);
	}

	ChangeState(EPlayerPawnState::NONE);
}

void UPlayerFSMComponent::CheckStateChange()
{
	if (NextState != nullptr && NextState != CurrentState)
	{
		if (CurrentState != nullptr)
		{
			PreviousStateEnum = CurrentState->GetStateEnum();

			CurrentState->Exit();

		}

		CurrentState = NextState;

		CurrentState->Enter();

	}

}

void UPlayerFSMComponent::UpdateCurrentState(float DeltaSeconds)
{
	CheckStateChange();

	if (CurrentState != nullptr)
	{
		CurrentState->Execute(DeltaSeconds);
	}

}



// Fill out your copyright notice in the Description page of Project Settings.

#include "States/PlayerPawnStates/PPState_JUMP.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "Engine/Public/TimerManager.h"

void UPPState_JUMP::Init(UPlayerFSMComponent* InPlayerFSMComponent)
{
	PlayerFSMComponent = InPlayerFSMComponent;

	SetupData();

	if (PlayerFSMComponent->GetIsDebugActive() == true)
	{
		UE_LOG(PlayerFSMLog, Display, TEXT("PPState_JUMP: Init"));
	}
}

void UPPState_JUMP::Enter()
{
	if (PlayerFSMComponent->GetIsDebugActive() == true)
	{
		UE_LOG(PlayerFSMLog, Display, TEXT("PPState_JUMP: Enter"));
	}

	bIsJumping = false;
	
	StartTimer();	
}

void UPPState_JUMP::Execute(float DeltaSeconds)
{
	if (PlayerFSMComponent->GetIsDebugActive() == true)
	{
		UE_LOG(PlayerFSMLog, Display, TEXT("PPState_JUMP: Execute"));
	}
}

void UPPState_JUMP::Exit()
{
	if (PlayerFSMComponent->GetIsDebugActive() == true)
	{
		UE_LOG(PlayerFSMLog, Display, TEXT("PPState_JUMP: Exit"));
	}
}

void UPPState_JUMP::SetupData()
{
	PlayerPawn = Cast<APlayerPawn>(PlayerFSMComponent->GetOwner());
	ensure(PlayerPawn != nullptr);

	PlayerPawnMovementComponent = PlayerPawn->GetPlayerPawnMovementComponent();
	ensure(PlayerPawnMovementComponent != nullptr);

	AnimInstance = PlayerPawn->GetPlayerAnimInstance();
	ensure(AnimInstance != nullptr);

	bIsJumping = false;
}

void UPPState_JUMP::StartTimer()
{
	AnimInstance->Jumping();

	GetWorld()->GetTimerManager().SetTimer(JumpTimerHandle,this, &UPPState_JUMP::SetJumpVelocity, GetWorld()->GetDeltaSeconds(), true, 0.5F);

}




void UPPState_JUMP::StopTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(JumpTimerHandle);
	PlayerFSMComponent->ChangeState(EPlayerPawnState::FALLING);
}

void UPPState_JUMP::SetJumpVelocity()
{
	if (bIsJumping == true)
	{
		PlayerPawnMovementComponent->Velocity.Z -= 8000.F * GetWorld()->GetDeltaSeconds();

		if (PlayerPawnMovementComponent->Velocity.Z <= 0.F)
		{
			StopTimer();
		}
	}
	else
	{
		PlayerPawnMovementComponent->Velocity.Z = 2000.F;
		bIsJumping = true;

	}
	

	
}

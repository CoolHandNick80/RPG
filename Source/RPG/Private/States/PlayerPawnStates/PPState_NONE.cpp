// Fill out your copyright notice in the Description page of Project Settings.

#include "states/PlayerPawnStates/PPState_NONE.h"
#include "Globals/GlobalFunctions.h"


void UPPState_NONE::Init(UPlayerFSMComponent* InPlayerFSMComponent)
{
	PlayerFSMComponent = InPlayerFSMComponent;

	SetupData();

	if (PlayerFSMComponent->GetIsDebugActive() == true)
	{
		UE_LOG(PlayerFSMLog, Display, TEXT("PPState_NONE: Init"));
	}
}

void UPPState_NONE::Enter()
{
	if (PlayerFSMComponent->GetIsDebugActive() == true)
	{
		UE_LOG(PlayerFSMLog, Display, TEXT("PPState_NONE: Enter"));
	}
}

void UPPState_NONE::Execute(float DeltaSeconds)
{
	if (PlayerFSMComponent->GetIsDebugActive() == true)
	{
		UE_LOG(PlayerFSMLog, Display, TEXT("PPState_NONE: Execute"));
	}

	CheckGround();
}

void UPPState_NONE::Exit()
{
	if (PlayerFSMComponent->GetIsDebugActive() == true)
	{
		UE_LOG(PlayerFSMLog, Display, TEXT("PPState_NONE: Exit"));
	}
}

void UPPState_NONE::SetupData()
{
	PlayerPawn = Cast<APlayerPawn>(PlayerFSMComponent->GetOwner());
	ensure(PlayerPawn != nullptr);
}

void UPPState_NONE::CheckGround()
{
	const FVector Start = PlayerPawn->GetActorLocation();
	const FVector End = Start + (-FVector::UpVector * 200.F);

	FHitResult HitResult;

	bool bIsTouchingGround = UGlobalFunctions::SimpleTrace(GetWorld(), PlayerPawn, Start, End, HitResult);

	if (bIsTouchingGround == true)
	{
		const FVector SmoothLocation = FMath::VInterpTo(PlayerPawn->GetActorLocation(), HitResult.Location + FVector::UpVector * PlayerPawn->HLocation, GetWorld()->GetDeltaSeconds(), 12.F);
		PlayerPawn->SetActorLocation(SmoothLocation);

		// We touched ground
		PlayerFSMComponent->ChangeState(EPlayerPawnState::GROUNDED);

	}
	else
	{
		// We're falling
		PlayerFSMComponent->ChangeState(EPlayerPawnState::FALLING);
	}
}

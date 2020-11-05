// Fill out your copyright notice in the Description page of Project Settings.


#include "PPState_ROLL.h"
#include "Globals/GlobalFunctions.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

void UPPState_ROLL::Init(UPlayerFSMComponent* InPlayerFSMComponent)
{
	PlayerFSMComponent = InPlayerFSMComponent;

	PlayerPawn = Cast<APlayerPawn>(PlayerFSMComponent->GetOwner());
	ensure(PlayerPawn != nullptr);

	MovementComponent = PlayerPawn->GetPlayerPawnMovementComponent();
	ensure(MovementComponent != nullptr);

	AnimInstance = PlayerPawn->GetPlayerAnimInstance();
	ensure(AnimInstance != nullptr);

	if (PlayerFSMComponent->GetIsDebugActive() == true)
	{
		UE_LOG(PlayerFSMLog, Display, TEXT("PPState_ROLL:Init"));
	}
}

void UPPState_ROLL::Enter()
{
	// Fix Pawn rotation

	if (!PlayerPawn->GetActorRotation().Equals(MovementComponent->LastValidRotation))
	{
		PlayerPawn->SetActorRotation(MovementComponent->LastValidRotation);
	}


	// Actually play the montage
	AnimInstance->Roll();

	StartRollTimer();

	if (PlayerFSMComponent->GetIsDebugActive() == true)
	{
		UE_LOG(PlayerFSMLog, Display, TEXT("PPState_ROLL:Enter"));
	}
}

void UPPState_ROLL::Execute(float DeltaSeconds)
{
	CheckGround();

	if (PlayerFSMComponent->GetIsDebugActive() == true)
	{
		//UE_LOG(PlayerFSMLog, Display, TEXT("PPState_ROLL:Execute"));
	}
}

void UPPState_ROLL::Exit()
{
	if (PlayerFSMComponent->GetIsDebugActive() == true)
	{
		UE_LOG(PlayerFSMLog, Display, TEXT("PPState_ROLL:Exit"));
	}
}

void UPPState_ROLL::StartRollTimer()
{
	const FVector TargetLocation = PlayerPawn->GetActorLocation() + PlayerPawn->GetActorForwardVector() * Direction * AnimInstance->RollDistance;

	FTimerDelegate Del;
	Del.BindUFunction(this, "UpdateRollTimer", PlayerPawn->GetActorLocation(), TargetLocation);

	GetWorld()->GetTimerManager().SetTimer(RollTimerHandle, Del, GetWorld()->GetDeltaSeconds(), true);
}

void UPPState_ROLL::UpdateRollTimer(FVector InStartVector, FVector InTargetVector)
{
	RollAlpha += GetWorld()->GetDeltaSeconds() / AnimInstance->GetRollMontageDuration();

	float CurrentY = UKismetMathLibrary::Ease(InStartVector.Y, InTargetVector.Y, RollAlpha, EEasingFunc::EaseOut);
	float CurrentX = UKismetMathLibrary::Ease(InStartVector.X, InTargetVector.X, RollAlpha, EEasingFunc::EaseOut);

	const FVector CurrentLocation = FVector(CurrentX, CurrentY, PlayerPawn->GetActorLocation().Z);

	PlayerPawn->SetActorLocation(CurrentLocation, true);

	AnimInstance->UpdateRollAlpha(RollAlpha);

	
	if (RollAlpha >= AnimInstance->RollMontageCompletationRating)
	{
		RollAlpha = 0.F;

		StopRollTimer();
	}
}

void UPPState_ROLL::StopRollTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(RollTimerHandle);

	PlayerFSMComponent->ChangeState(EPlayerPawnState::GROUNDED);
}

void UPPState_ROLL::CheckGround()
{
	const FVector Start = PlayerPawn->GetActorLocation();
	const FVector End = Start + (-FVector::UpVector*200.F);

	UKismetSystemLibrary::DrawDebugPoint(this, Start, 5.F, FColor::Yellow, 0.1F);
	UKismetSystemLibrary::DrawDebugPoint(this, End, 5.F, FColor::Orange, 0.1F);
	UKismetSystemLibrary::DrawDebugLine(this, Start, End, FColor::Yellow, 0.1F, 2.F);

	FHitResult HitResult;

	bool bIsTouchingGround = UGlobalFunctions::SimpleTrace(GetWorld(), PlayerPawn, Start, End, HitResult);

	if (bIsTouchingGround == false)
	{
		// We're falling
		StopRollTimer();
		PlayerFSMComponent->ChangeState(EPlayerPawnState::FALLING);
	}
}

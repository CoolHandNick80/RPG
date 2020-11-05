// Fill out your copyright notice in the Description page of Project Settings.

#include "States/PlayerPawnStates/PPState_GROUNDED.h"
#include "GlobalFunctions.h"
#include "Kismet/GameplayStatics.h"

void UPPState_GROUNDED::Init(UPlayerFSMComponent* InPlayerFSMComponent)
{
	PlayerFSMComponent = InPlayerFSMComponent;

	SetupData();

	if (PlayerFSMComponent->GetIsDebugActive() == true)
	{
		UE_LOG(PlayerFSMLog, Display, TEXT("PPState_GROUNDED: Init"));
	}
}

void UPPState_GROUNDED::Enter()
{
	if (PlayerFSMComponent->GetPreviousStateEnum() == EPlayerPawnState::FALLING)
	{
		bJustLanded = true;

		PlayerPawnMovementComponent->Velocity = FVector::ZeroVector;

		AnimInstance->Landing();
	}
	if (PlayerFSMComponent->GetIsDebugActive() == true)
	{
		UE_LOG(PlayerFSMLog, Display, TEXT("PPState_GROUNDED: Enter"));
	}
}

void UPPState_GROUNDED::Execute(float DeltaSeconds)
{
	
	CheckGround();
	
	if (PlayerFSMComponent->GetIsDebugActive() == true)
	{
		UE_LOG(PlayerFSMLog, Display, TEXT("PPState_GROUNDED: Execute"));
	}
}

void UPPState_GROUNDED::Exit()
{
	if (PlayerFSMComponent->GetIsDebugActive() == true)
	{
		UE_LOG(PlayerFSMLog, Display, TEXT("PPState_GROUNDED: Exit"));
	}
}

void UPPState_GROUNDED::SetupData()
{
	PlayerPawn = Cast<APlayerPawn>(PlayerFSMComponent->GetOwner());
	ensure(PlayerPawn != nullptr);

	PlayerPawnMovementComponent = PlayerPawn->GetPlayerPawnMovementComponent();
	ensure(PlayerPawnMovementComponent != nullptr);

	AnimInstance = PlayerPawn->GetPlayerAnimInstance();
	ensure(AnimInstance != nullptr);

	GameMode = Cast<ARPGGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	verify(GameMode != nullptr);

	GameMode->OnCameraSpawned.AddDynamic(this, &UPPState_GROUNDED::AssignGameplayCamera);

	AnimInstance->OnJumpCompleted.AddDynamic(this, &UPPState_GROUNDED::OnJumpCompleted);
}

void UPPState_GROUNDED::HandleGroundedMovement()
{
	if (PlayerPawn != nullptr && PlayerPawnMovementComponent != nullptr)
	{
		
		PlayerPawn->AddMovementInput(GameplayCamera->GetActorRightVector(), PlayerPawnMovementComponent->MovementInputVector.Y);
		PlayerPawn->AddMovementInput(GameplayCamera->GetActorForwardVector(), PlayerPawnMovementComponent->MovementInputVector.X);
	}
}

void UPPState_GROUNDED::HandleGroundedRotation()
{
	if (!FMath::IsNearlyZero(PlayerPawnMovementComponent->MovementInputVector.Y, 0.3F) || !FMath::IsNearlyZero(PlayerPawnMovementComponent->MovementInputVector.X, 0.3F))
	{
		const FVector HorizontalMovementInput = FVector(PlayerPawnMovementComponent->MovementInputVector.X, PlayerPawnMovementComponent->MovementInputVector.Y, 0.F);

		const FRotator CurrentInputRotation = FRotator(0.F, GameplayCamera->GetActorRotation().Yaw + HorizontalMovementInput.Rotation().Yaw, 0.F);

		const FRotator SmoothRotation = FMath::RInterpTo(PlayerPawn->GetActorRotation(), CurrentInputRotation, GetWorld()->GetDeltaSeconds(), PlayerPawnMovementComponent->RotationSpeed);

		PlayerPawn->SetActorRotation(SmoothRotation);

		PlayerPawnMovementComponent->LastValidRotation = CurrentInputRotation;
	}
	else // If there's no input:
	{
		if (PlayerPawn->GetActorRotation() != PlayerPawnMovementComponent->LastValidRotation)
		{
			const FRotator SmoothRotation = FMath::RInterpTo(PlayerPawn->GetActorRotation(), PlayerPawnMovementComponent->LastValidRotation, GetWorld()->GetDeltaSeconds(), PlayerPawnMovementComponent->RotationSpeed);

			PlayerPawn->SetActorRotation(SmoothRotation);
		}
	}
}

void UPPState_GROUNDED::CheckGround()
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
		if (bJustLanded == false)
		{
			HandleGroundedMovement();
			HandleGroundedRotation();
		}

	}
	else
	{
		// We're falling
		PlayerFSMComponent->ChangeState(EPlayerPawnState::FALLING);
	}
}

void UPPState_GROUNDED::AssignGameplayCamera()
{
	GameplayCamera = Cast<AGameplayCamera>(GameMode->GetGameplayCamera());
	verify(GameplayCamera != nullptr);
}

void UPPState_GROUNDED::OnJumpCompleted()
{
	bJustLanded = false;
}

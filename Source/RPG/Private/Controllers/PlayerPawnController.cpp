// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerPawnController.h"
#include "PlayerPawn.h"
#include "Cameras/GameplayCamera.h"
#include "PlayerPawnMovementComponent.h"
#include "RPGGameModeBase.h"
#include "Kismet/GameplayStatics.h"

void APlayerPawnController::OnPossess(APawn * InPawn)
{
	Super::OnPossess(InPawn);

	PlayerPawn = Cast<APlayerPawn>(InPawn);
	verify(PlayerPawn != nullptr);

	PlayerPawnMovementComponent = Cast<UPlayerPawnMovementComponent>(PlayerPawn->GetPlayerPawnMovementComponent());
	verify(PlayerPawnMovementComponent != nullptr);

	GameMode = Cast<ARPGGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	verify(GameMode != nullptr);

	GameMode->OnCameraSpawned.AddDynamic(this, &APlayerPawnController::AssignGamplayCamera);

	PlayerFSMComponent = PlayerPawn->GetPlayerFSMComponent();
	verify(PlayerFSMComponent != nullptr);

}

void APlayerPawnController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &APlayerPawnController::MoveForward);

	InputComponent->BindAxis("MoveRight", this, &APlayerPawnController::MoveRight);

	InputComponent->BindAxis("CameraPitch", this, &APlayerPawnController::PitchCamera);

	InputComponent->BindAxis("CameraYaw", this, &APlayerPawnController::YawCamera);

	InputComponent->BindAction("Jump", IE_Pressed, this, &APlayerPawnController::Jump);

	InputComponent->BindAction("DropItem", IE_Pressed, this, &APlayerPawnController::DropItem);
}

void APlayerPawnController::MoveRight(float AxisValue)
{
	if (PlayerPawnMovementComponent != nullptr)
	{
		PlayerPawnMovementComponent->MovementInputVector.Y = FMath::Clamp<float>(AxisValue, -1.F, 1.F);
	}
}

void APlayerPawnController::MoveForward(float AxisValue)
{
	if (PlayerPawnMovementComponent != nullptr)
	{
		PlayerPawnMovementComponent->MovementInputVector.X = FMath::Clamp<float>(AxisValue, -1.F, 1.F);
	}
}

void APlayerPawnController::PitchCamera(float AxisValue)
{
	

	if (GameplayCamera != nullptr)
	{
		GameplayCamera->CameraInputVector.Y = FMath::Clamp<float>(AxisValue, -1.F, 1.F);
	}

}

void APlayerPawnController::YawCamera(float AxisValue)
{
	

	if (GameplayCamera != nullptr)
	{
		GameplayCamera->CameraInputVector.X = FMath::Clamp<float>(AxisValue, -1.F, 1.F);
	}
}

void APlayerPawnController::Jump()
{
	if (PlayerFSMComponent->GetCurrentStateEnum() == EPlayerPawnState::GROUNDED)
	{
		PlayerFSMComponent->ChangeState(EPlayerPawnState::JUMP);
	}
}

void APlayerPawnController::DropItem()
{
	if(PlayerPawn != nullptr)
	{
		PlayerPawn->DropItem();
	}
}

void APlayerPawnController::AssignGamplayCamera()
{
	GameplayCamera = Cast<AGameplayCamera>(GameMode->GetGameplayCamera());
	verify(GameplayCamera != nullptr);
}

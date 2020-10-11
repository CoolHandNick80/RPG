// Fill out your copyright notice in the Description page of Project Settings.

#include "RPGGameModeBase.h"
#include "Cameras/GameplayCamera.h"
#include "Globals/GlobalFunctions.h"
#include "Kismet/GameplayStatics.h"

void ARPGGameModeBase::StartPlay()
{
	Super::StartPlay();

	SpawnGameplayCamera();

}

void ARPGGameModeBase::SpawnGameplayCamera()
{
	verify(GameplayCameraClass != nullptr);

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	verify(PlayerPawn != nullptr);

	GameplayCamera = Cast<AGameplayCamera>(UGlobalFunctions::SimpleSpawn(GetWorld(), GameplayCameraClass, PlayerPawn->GetActorLocation(), FRotator::ZeroRotator));
	verify(GameplayCamera != nullptr);

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	verify(PlayerController != nullptr);

	PlayerController->SetViewTarget(GameplayCamera);

	GameplayCamera->SetTargetActor(PlayerPawn);

	EndCameraSpawn();

}

void ARPGGameModeBase::EndCameraSpawn()
{
	OnCameraSpawned.Broadcast();
}

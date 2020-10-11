// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RPGGameModeBase.generated.h"

class AGameplayCamera;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCameraSpawned);
/**
 * 
 */
UCLASS()
class RPG_API ARPGGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:

	virtual void StartPlay() override;

protected:

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AGameplayCamera> GameplayCameraClass = nullptr;

	UPROPERTY()
		AGameplayCamera* GameplayCamera = nullptr;

public:

	FOnCameraSpawned OnCameraSpawned;

protected:

	void SpawnGameplayCamera();

	void EndCameraSpawn();

public:

	AGameplayCamera* GetGameplayCamera() { return GameplayCamera; }
	
};

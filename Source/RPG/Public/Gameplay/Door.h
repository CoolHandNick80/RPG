// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework\Actor.h"
#include "Components\BoxComponent.h"
#include "Components\StaticMeshComponent.h"
#include "TimerManager.h"
#include "DoorKeyStruct.h"
#include "DoorKey.h"
#include "GameInstances\RPGGameInstance.h"
#include "Engine\DataTable.h"
#include "Door.generated.h"

class APlayerPawn;

UCLASS()
class RPG_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

	virtual void PostInitializeComponents() override;

	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UBoxComponent* BoxComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* StaticMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USceneComponent* SceneComponent = nullptr;

	FTimerHandle TimerHandle;

	bool bIsLocked = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DoorKey)
		TSubclassOf<ADoorKey> DoorKeyClass = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DoorKey)
		FName DoorKeyName;

	UPROPERTY()
		URPGGameInstance* GameInstance = nullptr;

	UPROPERTY()
		UDataTable* DoorKeyDataTable = nullptr;

	UPROPERTY()
		FDataTableRowHandle DataTableRowHandle;
		

protected:

	void OpenDoor(APlayerPawn* PlayerPawn);

	void CloseDoor(float DeltaTime);

	UFUNCTION()
		void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	UFUNCTION()
		void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void StartTimer();
	
	UFUNCTION()
	void UpdateTimer(float InStartTime);

	void StopTimer();

};

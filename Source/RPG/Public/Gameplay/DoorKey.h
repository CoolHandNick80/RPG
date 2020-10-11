// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/DataTable.h"
#include "GameInstances/RPGGameInstance.h"
#include "DoorKey.generated.h"

UCLASS()
class RPG_API ADoorKey : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoorKey();

	virtual void OnConstruction(const FTransform& Transform) override;

	// Allow actors to initialize themselves on the C++ side after all of their components have been initialized, only called during gameplay
	virtual void PostInitializeComponents() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UBoxComponent* BoxComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* StaticMeshComponent = nullptr;

	UPROPERTY(EditAnywhere)
		FName DoorKeyName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (FDataTableCostumization), category = DoorKey)
		FDataTableRowHandle DataTableRowHandle;

	UPROPERTY()
		URPGGameInstance* GameInstance = nullptr;

protected:
	UFUNCTION()
		void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

};

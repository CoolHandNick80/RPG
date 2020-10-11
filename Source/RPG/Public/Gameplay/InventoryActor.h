// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "InventoryActor.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API AInventoryActor : public AStaticMeshActor
{
	GENERATED_BODY()
		
public:
	AInventoryActor();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TSubclassOf<AInventoryActor> ActorClass = nullptr;

	virtual void OnConstruction(const FTransform & Transform) override;
};

#pragma once

#include "ObjectMacros.h"
#include "Components/StaticMeshComponent.h"
#include "Gameplay/InventoryActor.h"
#include "InventoryItemStruct.generated.h"

USTRUCT(BlueprintType)
struct RPG_API FInventoryItemStruct
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* StaticMeshComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TSubclassOf<AInventoryActor> ItemClass;

	FORCEINLINE bool operator==(const FInventoryItemStruct& other) const
	{
		/*GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "OPERATOR OVERLOADED!");*/
		return other.ItemClass->GetDesc() == ItemClass->GetDesc() && other.StaticMeshComponent == StaticMeshComponent;
	}
};


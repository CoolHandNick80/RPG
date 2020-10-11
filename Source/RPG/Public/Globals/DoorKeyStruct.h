#pragma once

#include "ObjectMacros.h"
#include "UObject/Class.h"
#include "Engine/DataTable.h"
#include "DoorKeyStruct.generated.h"

USTRUCT(BlueprintType)
struct RPG_API FDoorKeyStruct : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool bIsOwned;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UClass* DoorClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UClass* DoorKeyClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FName DoorKeyName;

	FDoorKeyStruct()
	{
		bIsOwned = false;
		DoorClass = nullptr;
		DoorKeyClass = nullptr;
		DoorKeyName = "NONE";
	}

};
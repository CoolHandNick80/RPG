// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GlobalTypes.generated.h"

UENUM(BlueprintType)
enum class EPlayerPawnState : uint8
{
	NONE,
	GROUNDED,
	FALLING,
	JUMP,
	ROLL
};
/**
 * 
 */
UCLASS()
class RPG_API UGlobalTypes : public UObject
{
	GENERATED_BODY()
	
};

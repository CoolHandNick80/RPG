// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/World.h"
#include "GlobalFunctions.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API UGlobalFunctions : public UObject
{
	GENERATED_BODY()
	
public:

	/* Simple spawn function.
	*	Will spawn an Actor of the specified class, at InLocation, with InRotation.
	*	Will try to adjust spawned Actor location if needed, but it will always spawn regardless.
	*/
	static FORCEINLINE AActor* SimpleSpawn(UWorld* InWorld, UClass* InClass, const FVector& InLocation, const FRotator& InRotation)
	{
		if (!InWorld)	return nullptr;
		if (!InClass)	return nullptr;

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		AActor* SpawnedActor = InWorld->SpawnActor(InClass, &InLocation, &InRotation, SpawnParams);

		if (SpawnedActor)	return SpawnedActor;

		return nullptr;
	}

	static FORCEINLINE bool SimpleTrace(
		UWorld* InWorld,
		AActor* InActorToIgnore,
		const FVector& Start,
		const FVector& End,
		FHitResult& HitOut,
		ECollisionChannel CollisionChannel = ECC_Visibility,
		bool ReturnPhysMat = false)
	{
		if (!InWorld)
		{
			return false;
		}

		FCollisionQueryParams TraceParams(FName(TEXT("Simple Trace")), false, InActorToIgnore);
		TraceParams.bTraceComplex = false;
		TraceParams.bReturnPhysicalMaterial = ReturnPhysMat;
		TraceParams.AddIgnoredActor(InActorToIgnore);

		HitOut = FHitResult(ForceInit);

		InWorld->LineTraceSingleByChannel(HitOut, Start, End, CollisionChannel, TraceParams);

		return (HitOut.GetActor() != NULL);
	}
};

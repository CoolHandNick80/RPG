// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

class APlayerPawn;
class UPlayerPawnMovementComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnJumpCompleted);

/**
 * 
 */
UCLASS()
class RPG_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
protected:

	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

public:
	UPROPERTY()
		FOnJumpCompleted OnJumpCompleted;

protected:

	UPROPERTY()
		APlayerPawn* PlayerPawn = nullptr;

	UPROPERTY()
		UPlayerPawnMovementComponent* MovementComponent = nullptr;

	UPROPERTY(BlueprintReadOnly)
		float NormalizedVelocity = 0.F;

protected:

	void SetupData();

	void NormalizeVelocity();

	UFUNCTION(BlueprintCallable)
		void Broadcast_OnJumpCompleted() { OnJumpCompleted.Broadcast(); }

public:

	UFUNCTION(BlueprintImplementableEvent)
		void FallingLoop();

	UFUNCTION(BlueprintImplementableEvent)
		void Landing();

	UFUNCTION(BlueprintImplementableEvent)
		void Jumping();
};

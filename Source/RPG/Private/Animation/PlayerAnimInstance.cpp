// Fill out your copyright notice in the Description page of Project Settings.

#include "Animation/PlayerAnimInstance.h"
#include "PlayerPawn.h"
#include "Components/PlayerPawnMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"


void UPlayerAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	SetupData();
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	NormalizeVelocity();
}

void UPlayerAnimInstance::SetupData()
{
	if (TryGetPawnOwner() != nullptr)
	{
		PlayerPawn = Cast<APlayerPawn>(GetOwningActor());
		verify(PlayerPawn != nullptr);

		MovementComponent = PlayerPawn->GetPlayerPawnMovementComponent();
		verify(MovementComponent != nullptr);
	}
}

void UPlayerAnimInstance::NormalizeVelocity()
{
	if (MovementComponent != nullptr)
	{
		FVector HorizontalVelocity = FVector(MovementComponent->Velocity.X, MovementComponent->Velocity.Y, 0.F);
		NormalizedVelocity = UKismetMathLibrary::NormalizeToRange(HorizontalVelocity.Size(), 0.F, MovementComponent->MaxSpeed);
		//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Emerald, FString::SanitizeFloat(NormalizedVelocity));

	}
}

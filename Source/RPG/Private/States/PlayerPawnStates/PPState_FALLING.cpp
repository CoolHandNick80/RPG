// Fill out your copyright notice in the Description page of Project Settings.

#include "PPState_FALLING.h"
#include "GlobalFunctions.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UPPState_FALLING::Init(UPlayerFSMComponent* InPlayerFSMComponent)
{
	PlayerFSMComponent = InPlayerFSMComponent;

	SetupData();

	if (PlayerFSMComponent->GetIsDebugActive() == true)
	{
		UE_LOG(PlayerFSMLog, Display, TEXT("PPState_FALLING: Init"));
	}
}

void UPPState_FALLING::Enter()
{
	
	AnimInstance->FallingLoop();

	if (PlayerFSMComponent->GetIsDebugActive() == true)
	{
		UE_LOG(PlayerFSMLog, Display, TEXT("PPState_FALLING: Enter"));
	}
}

void UPPState_FALLING::Execute(float DeltaSeconds)
{
	CheckGround();

	if (PlayerFSMComponent->GetIsDebugActive() == true)
	{
		UE_LOG(PlayerFSMLog, Display, TEXT("PPState_FALLING: Execute"));
	}
}

void UPPState_FALLING::Exit()
{
	if (PlayerFSMComponent->GetIsDebugActive() == true)
	{
		UE_LOG(PlayerFSMLog, Display, TEXT("PPState_FALLING: Exit"));
	}
}

void UPPState_FALLING::SetupData()
{
	PlayerPawn = Cast<APlayerPawn>(PlayerFSMComponent->GetOwner());
	ensure(PlayerPawn != nullptr);

	PlayerPawnMovementComponent = PlayerPawn->GetPlayerPawnMovementComponent();
	ensure(PlayerPawnMovementComponent != nullptr);

	AnimInstance = PlayerPawn->GetPlayerAnimInstance();
	ensure(AnimInstance != nullptr);

	GameMode = Cast<ARPGGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	verify(GameMode != nullptr);

	GameMode->OnCameraSpawned.AddDynamic(this, &UPPState_FALLING::AssignGameplayCamera);
}

void UPPState_FALLING::CheckGround()
{
	const FVector Start = PlayerPawn->GetActorLocation();
	const FVector End = Start + (-FVector::UpVector * 200.F);

	/*UKismetSystemLibrary::DrawDebugPoint(this, Start, 5.F, FColor::Yellow, 0.1F);
	UKismetSystemLibrary::DrawDebugPoint(this, End, 5.F, FColor::Orange, 0.1F);
	UKismetSystemLibrary::DrawDebugLine(this, Start, End, FColor::Yellow, 0.1F, 2.F);*/

	FHitResult HitResult;

	bool bIsTouchingGround = UGlobalFunctions::SimpleTrace(GetWorld(), PlayerPawn, Start, End, HitResult);

	if (bIsTouchingGround == true)
	{
		const FVector SmoothLocation = FMath::VInterpTo(PlayerPawn->GetActorLocation(), HitResult.Location + FVector::UpVector * PlayerPawn->HLocation, GetWorld()->GetDeltaSeconds(), 12.F);
		PlayerPawn->SetActorLocation(SmoothLocation);

		// We touched ground
		PlayerFSMComponent->ChangeState(EPlayerPawnState::GROUNDED);

	}
	else
	{
		// We're falling
		PlayerPawnMovementComponent->Velocity.Z -= 10000.F * GetWorld()->GetDeltaSeconds();
	}
}

void UPPState_FALLING::AssignGameplayCamera()
{
	GameplayCamera = Cast<AGameplayCamera>(GameMode->GetGameplayCamera());
	verify(GameplayCamera != nullptr);
}

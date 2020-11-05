// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/PlayerPawnMovementComponent.h"
#include "PlayerFSMComponent.h"
#include "Animation/PlayerAnimInstance.h"
#include "InventoryComponent.h"
#include "InventoryActor.h"
#include "KeyChain.h"

//#if WITH_EDITOR
#include "Components/ArrowComponent.h"
//#endif

#include "PlayerPawn.generated.h"

class ARPGGameModeBase;
class AGameplayCamera;

UCLASS()
class RPG_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	UPROPERTY(EditDefaultsOnly)
		float HLocation = 130.F;
	
	bool bKeyOwned = false;

	UPROPERTY()
		UInventoryComponent* MyInventory;

	UPROPERTY()
		UKeyChain* MyKeyChain;


protected:
	UPROPERTY(VisibleAnywhere)
		UCapsuleComponent* CapsuleComponent = nullptr;

	UPROPERTY(VisibleAnywhere)
		USkeletalMeshComponent* SkeletalMeshComponent = nullptr;

	UPROPERTY(VisibleAnywhere)
		UPlayerPawnMovementComponent* PlayerPawnMovementComponent = nullptr;

	UPROPERTY(VisibleAnywhere)
		UPlayerFSMComponent* PlayerFSMComponent = nullptr;

//#if WITH_EDITOR
	UPROPERTY(VisibleAnywhere)
		UArrowComponent* ArrowComponent = nullptr;
//#endif
	
	UPROPERTY()
		ARPGGameModeBase* GameMode = nullptr;

	UPROPERTY()
		AGameplayCamera* GameplayCamera = nullptr;

	// The movement from the previous frame
	FVector2D lastInput = FVector2D::ZeroVector;

	const FVector HorizontalMovementInput = FVector::ZeroVector;

public:

	UPlayerPawnMovementComponent* GetPlayerPawnMovementComponent() { return PlayerPawnMovementComponent; }

	UPlayerFSMComponent* GetPlayerFSMComponent() { return PlayerFSMComponent; }

	UPlayerAnimInstance* GetPlayerAnimInstance() { return Cast<UPlayerAnimInstance>(SkeletalMeshComponent->GetAnimInstance()); }

	USkeletalMeshComponent* GetSkeletalMeshComp() { return SkeletalMeshComponent; }

	UFUNCTION()
		void DropItem();

	UFUNCTION()
		void TakeItem(AInventoryActor* InventoryItem);

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);


protected:

	UFUNCTION()
		void AssignGamplayCamera();
};

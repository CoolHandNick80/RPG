// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryActor.h"
#include "ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/CollisionProfile.h"

AInventoryActor::AInventoryActor()
	:Super()
{
	PrimaryActorTick.bCanEverTick = true;
	auto MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	verify(MeshAsset.Object != nullptr);

	if (MeshAsset.Object != nullptr)
	{
		GetStaticMeshComponent()->SetStaticMesh(MeshAsset.Object);
		GetStaticMeshComponent()->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	}

	GetStaticMeshComponent()->SetMobility(EComponentMobility::Movable);

	SetActorEnableCollision(true);
}


void AInventoryActor::OnConstruction(const FTransform & Transform)
{
	Super::OnConstruction(Transform);

	ActorClass = this->StaticClass();

}

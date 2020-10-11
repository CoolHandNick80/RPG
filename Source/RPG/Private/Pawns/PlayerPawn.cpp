// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerPawn.h"
#include "PlayerPawnController.h"
#include "Cameras/GameplayCamera.h"
#include "RPGGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GlobalFunctions.h"
#include "InventoryActor.h"
#include "Engine/Engine.h"


// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>("CapsuleComponent");
	RootComponent = CapsuleComponent;
	CapsuleComponent->OnComponentHit.AddDynamic(this, &APlayerPawn::OnHit);

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMeshcomponent");
	SkeletalMeshComponent->SetupAttachment(CapsuleComponent);

//#if WITH_EDITOR
	ArrowComponent = CreateDefaultSubobject<UArrowComponent>("ArrowComponent");
	ArrowComponent->SetupAttachment(CapsuleComponent);
//#endif

	PlayerPawnMovementComponent = CreateDefaultSubobject<UPlayerPawnMovementComponent>("PlayerPawnMovementComponent");

	PlayerFSMComponent = CreateDefaultSubobject<UPlayerFSMComponent>("PlayerFSMComponent");

	MyInventory = CreateDefaultSubobject<UInventoryComponent>("MyInventory");

	MyKeyChain = CreateDefaultSubobject<UKeyChain>("MyKeyChain");
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
	GameMode = Cast<ARPGGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	verify(GameMode != nullptr);
	
	GameMode->OnCameraSpawned.AddDynamic(this, &APlayerPawn::AssignGamplayCamera);
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
		
}

void APlayerPawn::DropItem()
{
	if (MyInventory->CurrentInventory.Num() == 0)
	{
		return;
	}
	FInventoryItemStruct Item = MyInventory->CurrentInventory.Last();
	
	FVector ItemOrigin;
	FVector ItemBounds;
	FVector BoxExtent;
	float SphereRadius;
	/*Item->GetActorBounds(false, ItemOrigin, ItemBounds);*/
	UKismetSystemLibrary::GetComponentBounds(Item.StaticMeshComponent, ItemOrigin, BoxExtent, SphereRadius);


	FVector PutDownLocation = GetActorLocation() + FVector(RootComponent->GetForwardVector() * (CapsuleComponent->GetScaledCapsuleRadius() + SphereRadius + 10.F));

	AInventoryActor* InvenctoryActor = Cast<AInventoryActor>(UGlobalFunctions::SimpleSpawn(GetWorld(), Item.ItemClass, PutDownLocation, GetActorRotation()));
	verify(InvenctoryActor != nullptr);

	GEngine->AddOnScreenDebugMessage(-1, 5.F, FColor::Emerald, Item.ItemClass->GetDesc());

	MyInventory->RemoveFromInventory(Item);
	/*MyInventory->CurrentInventory.Remove(Item);*/

	/*Item->PutDown(PutDownLocation);*/
}

void APlayerPawn::TakeItem(AInventoryActor * InventoryItem)
{
	/*InventoryItem->PickUp();*/

	FInventoryItemStruct Item = FInventoryItemStruct();

	Item.ItemClass = InventoryItem->ActorClass;
	Item.StaticMeshComponent = InventoryItem->GetStaticMeshComponent();

	MyInventory->AddToInventory(Item);

	InventoryItem->Destroy();

	GEngine->AddOnScreenDebugMessage(-1, 5.F, FColor::Emerald, Item.ItemClass->GetDesc());
	GEngine->AddOnScreenDebugMessage(-1, 5.F, FColor::Black, Item.StaticMeshComponent->GetDesc());
}

void APlayerPawn::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	AInventoryActor* InventoryItem = Cast<AInventoryActor>(OtherActor);

	if (InventoryItem != nullptr)
	{
		TakeItem(InventoryItem);
	}
}

void APlayerPawn::AssignGamplayCamera()
{
	GameplayCamera = Cast<AGameplayCamera>(GameMode->GetGameplayCamera());
	verify(GameplayCamera != nullptr);
}





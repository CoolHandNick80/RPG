// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorKey.h"
#include "Engine\Engine.h"
#include "Pawns\PlayerPawn.h"
#include "Kismet\KismetSystemLibrary.h"

// Sets default values
ADoorKey::ADoorKey()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	RootComponent = BoxComponent;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	StaticMeshComponent->SetupAttachment(RootComponent);

}

void ADoorKey::OnConstruction(const FTransform & Transform)
{
	Super::OnConstruction(Transform);

	

	
}

void ADoorKey::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (BoxComponent != nullptr)
	{
		BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ADoorKey::OnBoxBeginOverlap);
	}
}

// Called when the game starts or when spawned
void ADoorKey::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoorKey::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UKismetSystemLibrary::DrawDebugString(this, GetActorLocation(), "KEY", nullptr, FColor::Emerald, 0.001F);

}

void ADoorKey::OnBoxBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	APlayerPawn* PlayerPawn = Cast<APlayerPawn>(OtherActor);

	if (PlayerPawn != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red,"you have found the key");
		//PlayerPawn->bKeyOwned = true;

		const FName RowName = DataTableRowHandle.RowName;
		FDoorKeyStruct* DKS = DataTableRowHandle.GetRow<FDoorKeyStruct>(RowName.ToString());
		PlayerPawn->MyKeyChain->AddToKeyChain(DKS);

		Destroy();
	}
	

}


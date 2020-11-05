// Fill out your copyright notice in the Description page of Project Settings.

#include "..\..\Public\Gameplay\Door.h"
#include "Engine\Engine.h"
#include "UObject\ConstructorHelpers.h"
#include "Public\Pawns\PlayerPawn.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	RootComponent = BoxComponent;
	BoxComponent->SetBoxExtent(FVector(50.F, 15.F, 115.F));

	SceneComponent = CreateDefaultSubobject<USceneComponent>("Pivot");
	SceneComponent->SetupAttachment(RootComponent);
	SceneComponent->SetRelativeLocation(FVector(40.F, 0.F, -115.F));

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	StaticMesh->SetupAttachment(SceneComponent);
	StaticMesh->SetRelativeLocation(FVector(0.F, -3.5F, 0.F));

	static ConstructorHelpers::FObjectFinder<UDataTable>DataTable(TEXT("/Game/DataTables/DoorKeyDataTable.DoorKeyDataTable"));

	if (DataTable.Object != nullptr)
	{
		DoorKeyDataTable = DataTable.Object;
		
	}
	
	
}

void ADoor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ADoor::OnBoxBeginOverlap);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &ADoor::OnBoxEndOverlap);

	
}

void ADoor::OnConstruction(const FTransform & Transform)
{
	Super::OnConstruction(Transform);

	FDoorKeyStruct DKS = FDoorKeyStruct();
	DKS.DoorClass = this->StaticClass();
	DKS.DoorKeyClass = DoorKeyClass;
	DKS.DoorKeyName = DoorKeyName;



	if (DoorKeyDataTable != nullptr && DoorKeyName != "NONE")
	{

		DoorKeyDataTable->AddRow(DoorKeyName, DKS);
	}
	

	DoorOpening = (int32)DOpening;

}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();

	
	
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADoor::OpenDoor(APlayerPawn* PlayerPawn)
{
	if (DoorKeyName == "NONE")
	{
		StartTimer();
	}
	/*const FDoorKeyStruct* DKS = DoorKeyDataTable->FindRow<FDoorKeyStruct>(DoorKeyName, DoorKeyName.ToString(), true);*/


	for (auto Iter : PlayerPawn->MyKeyChain->CurrentKeyChain)
	{
		if (Iter != nullptr)
		{
			if (Iter->DoorKeyName == DoorKeyName)
			{
				if (bIsLocked == true)
				{
					GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Yellow, "Door unlocked");
					bIsLocked = false;
					StartTimer();
				}
				else
				{
					StartTimer();
				}
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Blue, "The Door is locked, you need the key");
			}
		}	
	}

	if (bIsLocked)
	{
		GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Blue, "The Door is locked, you need the key");
	}
}

void ADoor::CloseDoor(float DeltaTime)
{
}

void ADoor::OnBoxBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	APlayerPawn* PlayerPawn = Cast<APlayerPawn>(OtherActor);
	
	if (PlayerPawn != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Emerald, "PawnOverlapped");
		OpenDoor(PlayerPawn);
	}
}

void ADoor::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

void ADoor::StartTimer()
{
	float StartTime = GetWorld() -> GetTimeSeconds();

	FTimerDelegate Delegate;

	Delegate.BindUFunction(this, "UpdateTimer", StartTime);

	GetWorldTimerManager().SetTimer(TimerHandle, Delegate, GetWorld()->GetDeltaSeconds(), true);
}

void ADoor::UpdateTimer(float InStartTime)
{
	float CurrentTime = GetWorld()->GetTimeSeconds();
	float DeltaTime = CurrentTime - InStartTime;

	FRotator RelativeRotation = SceneComponent->GetRelativeRotation();
	FRotator FinalRotation = FRotator(0, DoorOpening*90, 0);

	if (FMath::Abs(RelativeRotation.Yaw) < FMath::Abs(FinalRotation.Yaw))
	{
		const FRotator SmoothRotation = FMath::RInterpTo(RelativeRotation, FinalRotation, DeltaTime, 0.5f);
		SceneComponent->SetRelativeRotation(SmoothRotation);
	}
	else
	{
		StopTimer();
	}
}

void ADoor::StopTimer()
{
	GetWorldTimerManager().ClearTimer(TimerHandle);
}

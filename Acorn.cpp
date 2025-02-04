#include "Acorn.h"
#include "Tree.h"

// Sets default values
AAcorn::AAcorn()
{
    PrimaryActorTick.bCanEverTick = true;
    AcornMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Acorn Mesh Component"));
    RootComponent = AcornMeshComponent;
}

// Called when the game starts or when spawned
void AAcorn::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void AAcorn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    DropAcorn();
}

void AAcorn::DropAcorn()
{
    FVector TempPosition{ GetActorLocation() };
    TempPosition.Z -= FallSpeed;
    SetActorLocation(TempPosition);

    FRotator NewRotation = GetActorRotation();
    NewRotation.Roll += 1;
    SetActorRotation(NewRotation);

    if (TempPosition.Z < 0)
    {
        Destroy();
    }
}

void AAcorn::Destroyed()
{
    Super::Destroyed();

    // Notify the tree that the acorn has been destroyed
    if (OwningTree)
    {
        OwningTree->AcornFalling = false;
        OwningTree->SpawnAcorn(); // Use the default spawn logic, not the multiple positions
    }
}

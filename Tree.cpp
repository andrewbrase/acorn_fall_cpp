#include "Tree.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
ATree::ATree()
    : AcornFalling(false)
{
    PrimaryActorTick.bCanEverTick = true;

    TreeMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tree Mesh Component"));
    RootComponent = TreeMeshComponent;

    static ConstructorHelpers::FClassFinder<AAcorn> AcornBPClass(TEXT("/Game/Blueprints/BP_Acorn"));
    if (AcornBPClass.Class != nullptr)
    {
        AcornClass = AcornBPClass.Class;
    }
}

// Called when the game starts or when spawned
void ATree::BeginPlay()
{
    Super::BeginPlay();
    SpawnAcorn();
}

// Called every frame
void ATree::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ATree::SpawnAcorn()
{
    // UE_LOG(LogTemp, Warning, TEXT("SpawnAcorn called"));
    if (!AcornFalling && AcornClass != nullptr)
    {
        FVector TreePosition = GetActorLocation();
        FRotator TreeRotation = GetActorRotation();

        FVector HeightOffset = FVector(0, 0, 400);
        TArray<FVector> AcornPositions = {
            TreePosition + HeightOffset + FVector(200, 0, 0),  // Right
            TreePosition + HeightOffset - FVector(200, 0, 0),  // Left
            TreePosition + HeightOffset + FVector(0, 200, 0),  // Front
            TreePosition + HeightOffset - FVector(0, 200, 0)   // Back
        };

        // Randomly select a position
        int32 RandomIndex = FMath::RandRange(0, AcornPositions.Num() - 1);
        FVector SpawnPosition = AcornPositions[RandomIndex];

        FActorSpawnParameters SpawnParams;
        AAcorn* NewAcorn = GetWorld()->SpawnActor<AAcorn>(AcornClass, SpawnPosition, TreeRotation, SpawnParams);

        if (NewAcorn != nullptr)
        {
            NewAcorn->OwningTree = this;
            AcornFalling = true;
            UE_LOG(LogTemp, Warning, TEXT("Acorn spawned successfully at %s"), *SpawnPosition.ToString());
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to spawn Acorn"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("AcornClass is null or Acorn is already falling"));
    }
}
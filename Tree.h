#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Acorn.h"
#include "Tree.generated.h"

UCLASS()
class ACORNFALL_API ATree : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ATree();

    bool AcornFalling;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Acorns")
    TSubclassOf<class AAcorn> AcornClass;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UStaticMeshComponent* TreeMeshComponent;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    void SpawnAcorn();
};

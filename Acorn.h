#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Acorn.generated.h"

UCLASS()
class ACORNFALL_API AAcorn : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AAcorn();
    float FallSpeed{ 1.5 };

    // Reference to the tree
    class ATree* OwningTree;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UStaticMeshComponent* AcornMeshComponent;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;
    void DropAcorn();

    // Override Destroyed function
    virtual void Destroyed() override;
};

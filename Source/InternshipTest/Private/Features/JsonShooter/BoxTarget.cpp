#include "BoxTarget.h"
#include "InternshipTestGameMode.h"
#include "Kismet/GameplayStatics.h"

ABoxTarget::ABoxTarget()
{
    BoxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxMesh"));
    RootComponent = BoxMesh;

    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
    static ConstructorHelpers::FObjectFinder<UMaterial> BoxMaterial(TEXT("/Game/M_BoxColor.M_BoxColor"));

    if (BoxMaterial.Succeeded())
    {
        BoxMesh->SetMaterial(0, BoxMaterial.Object);
    }

    if (CubeMesh.Succeeded())
    {
        BoxMesh->SetStaticMesh(CubeMesh.Object);
    }
}

void ABoxTarget::BeginPlay()
{
    Super::BeginPlay();
}

void ABoxTarget::ApplyDamage()
{
    Health--;

    if (Health <= 0)
    {
        // Add score only when the box is actually destroyed
        AInternshipTestGameMode* GM = Cast<AInternshipTestGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

        if (GM)
        {
            GM->AddScore(ScoreValue);
        }

        Destroy();
    }
}
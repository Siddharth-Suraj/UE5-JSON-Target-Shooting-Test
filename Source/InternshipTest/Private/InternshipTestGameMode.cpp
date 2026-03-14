#include "InternshipTestGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "ScoreWidget.h"

AInternshipTestGameMode::AInternshipTestGameMode()
{
}

void AInternshipTestGameMode::BeginPlay()
{
    Super::BeginPlay();

    // Create the score widget when the level starts
    if (ScoreWidgetClass)
    {
        ScoreWidget = CreateWidget<UScoreWidget>(GetWorld(), ScoreWidgetClass);

        if (ScoreWidget)
        {
            ScoreWidget->AddToViewport();
        }
    }
}

void AInternshipTestGameMode::AddScore(int32 Points)
{
    PlayerScore += Points;

    UE_LOG(LogTemp, Warning, TEXT("Score: %d"), PlayerScore);

    // Push the latest score to the UI after adding points
    if (ScoreWidget)
    {
        ScoreWidget->UpdateScore(PlayerScore);
    }
}
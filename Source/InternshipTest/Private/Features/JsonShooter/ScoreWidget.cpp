#include "ScoreWidget.h"

bool UScoreWidget::Initialize()
{
    bool Success = Super::Initialize();

    if (!Success) return false;

    return true;
}

void UScoreWidget::UpdateScore(int32 NewScore)
{
    if (ScoreText)
    {
        FString ScoreString = FString::Printf(TEXT("Score: %d"), NewScore);
        ScoreText->SetText(FText::FromString(ScoreString));
    }
}
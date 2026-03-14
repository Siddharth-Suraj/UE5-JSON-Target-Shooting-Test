#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "ScoreWidget.generated.h"

UCLASS()
class INTERNSHIPTEST_API UScoreWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    // Updates the score text shown on the UI
    void UpdateScore(int32 NewScore);

protected:
    virtual bool Initialize() override;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* ScoreText;
};
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ScoreWidget.h"
#include "Blueprint/UserWidget.h"
#include "InternshipTestGameMode.generated.h"

UCLASS(abstract)
class AInternshipTestGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AInternshipTestGameMode();

	UPROPERTY(BlueprintReadOnly)
	int32 PlayerScore = 0;

	// Adds points and updates the score UI
	void AddScore(int32 Points);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UScoreWidget> ScoreWidgetClass;

	UScoreWidget* ScoreWidget;
};
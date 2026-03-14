#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JsonManager.generated.h"

UCLASS()
class INTERNSHIPTEST_API AJsonManager : public AActor
{
	GENERATED_BODY()

public:
	AJsonManager();

	// Starts the HTTP request to download the JSON data
	void FetchJson();

protected:
	// Fetch the JSON once the level starts
	virtual void BeginPlay() override;
};
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FPSGameMode.generated.h"

/**
 * 
 */
UCLASS()
class INTERNSHIPTEST_API AFPSGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly)
	int32 PlayerScore = 0;

	void AddScore(int32 Points);
	
};


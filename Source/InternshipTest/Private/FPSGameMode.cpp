// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSGameMode.h"

void AFPSGameMode::AddScore(int32 Points)
{
    PlayerScore += Points;

    UE_LOG(LogTemp, Warning, TEXT("Score: %d"), PlayerScore);
}
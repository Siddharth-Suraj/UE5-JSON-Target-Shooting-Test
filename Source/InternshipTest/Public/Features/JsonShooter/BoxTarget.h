#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoxTarget.generated.h"

UCLASS()
class INTERNSHIPTEST_API ABoxTarget : public AActor
{
	GENERATED_BODY()

public:
	ABoxTarget();

protected:
	virtual void BeginPlay() override;

public:
	// Called when this box gets hit by the player's shot
	void ApplyDamage();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Health = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ScoreValue = 10;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BoxMesh;
};
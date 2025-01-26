// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/AIPawn.h"
#include "GameFramework/Actor.h"
#include "AISpawner.generated.h"

UCLASS()
class DUCKISH_API AAISpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	AAISpawner();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "AISpawner", ClampMin = 1.f, UIMin = 1.f))
	float SpawnRadius = 10000.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "AISpawner", ClampMin = 0.1f, UIMin = 0.1f))
	float SpawnRate = 5.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "AISpawner", ClampMin = 1, UIMin = 1))
	int PawnsPerTick = 3.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "AISpawner"))
	TSubclassOf<AAIPawn> AIPAwnClass = AAIPawn::StaticClass();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "AISpawner"))
	class APatrolArea* PatrolArea;

private:
	void ExecuteSpawnTick();

	FTimerHandle SpawnTimerHandle;
};

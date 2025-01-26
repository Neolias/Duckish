// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Waypoint.h"
#include "GameFramework/Actor.h"
#include "PatrolArea.generated.h"

UCLASS()
class DUCKISH_API APatrolArea : public AActor
{
	GENERATED_BODY()
	
public:	
	APatrolArea();
	TArray<AWaypoint*>* GetValidWaypoints() { return &ValidWaypoints; }
	UFUNCTION(BlueprintCallable)
	AWaypoint* GetRandomWaypoint();
	UFUNCTION(BlueprintCallable)
	void CheckOutWaypoint(AWaypoint* Waypoint);

protected:
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable)
	void GenerateWaypoints();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "PatrolArea | Generation", ClampMin = 1.f, UIMin = 1.f))
	float AreaRadius = 10000.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "PatrolArea | Generation", ClampMin = 1.f, UIMin = 1.f))
	float AreaHeight = 4000.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "PatrolArea | Generation", ClampMin = 1, UIMin = 1))
	int NumberOfWaypoints = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "PatrolArea | Generation"))
	TSubclassOf<AWaypoint> WaypointClass = AWaypoint::StaticClass();

private:
	TArray<AWaypoint*> ValidWaypoints;
};

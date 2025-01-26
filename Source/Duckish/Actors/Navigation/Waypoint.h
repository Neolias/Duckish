// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Waypoint.generated.h"

class APatrolArea;

UCLASS()
class DUCKISH_API AWaypoint : public AActor
{
	GENERATED_BODY()

public:
	AWaypoint();
	void SetPatrolArea(APatrolArea* NewPatrolArea)
	{
		PatrolArea = NewPatrolArea;
	}

protected:
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnDamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);
	UFUNCTION(BlueprintNativeEvent)
	void BecomeSaved();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Waypoint | Components")
	class USphereComponent* CollisionComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Waypoint | Components")
	UStaticMeshComponent* StaticMeshComponent;

private:
	void TriggerDeath();

	TObjectPtr<APatrolArea> PatrolArea;
};

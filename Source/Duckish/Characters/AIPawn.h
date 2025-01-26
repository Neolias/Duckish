// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BasePawn.h"
#include "AIPawn.generated.h"

class APatrolArea;

UCLASS()
class DUCKISH_API AAIPawn : public ABasePawn
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	APatrolArea* GetPatrolArea() const { return PatrolArea; }
	UFUNCTION(BlueprintCallable)
	void SetPatrolArea(APatrolArea* NewPatrolArea)
	{
		PatrolArea = NewPatrolArea;
	}

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AIPawn | Navigaton")
	APatrolArea* PatrolArea;
	
};

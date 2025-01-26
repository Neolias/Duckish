// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/AIPawn.h"
#include "AICat.generated.h"

/**
 * 
 */
UCLASS()
class DUCKISH_API AAICat : public AAIPawn
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnDamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);
	UFUNCTION(BlueprintNativeEvent)
	void TriggerDeath();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AIPawn | AICat")
	float DeathEmergeForce = 5000.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AIPawn | AICat")
	float DeathEmergeLength = 2.f;

private:
	void OnDeath();

	bool bIsEmerging = false;
	FTimerHandle EmergeTimerHandle;
	
};

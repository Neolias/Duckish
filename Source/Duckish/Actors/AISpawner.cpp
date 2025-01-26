// Fill out your copyright notice in the Description page of Project Settings.


#include "AISpawner.h"

#include "Navigation/PatrolArea.h"

AAISpawner::AAISpawner()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AAISpawner::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(PatrolArea))
	{
		ExecuteSpawnTick();
		GetWorldTimerManager().SetTimer(SpawnTimerHandle, [this] {ExecuteSpawnTick(); }, SpawnRate, true);
	}
}

void AAISpawner::ExecuteSpawnTick()
{
	if (!IsValid(PatrolArea))
	{
		return;
	}

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;

	for (int i = 0; i < PawnsPerTick; ++i)
	{
		const float PosX = FMath::RandRange(-SpawnRadius, SpawnRadius);
		const float PosY = FMath::RandRange(-SpawnRadius, SpawnRadius);
		const float PosZ = FMath::RandRange(0.f, SpawnRadius);
		const float Yaw = FMath::RandRange(-180.f, 180.f);
		FVector SpawnLocation = GetActorLocation() + FVector(PosX, PosY, PosZ);
		AAIPawn* NewAIPawn = GetWorld()->SpawnActor<AAIPawn>(AIPAwnClass, SpawnLocation, FRotator(0.f, Yaw, 0.f), SpawnParameters);
		if (IsValid(NewAIPawn))
		{
			NewAIPawn->SetPatrolArea(PatrolArea);
		}
		else
		{
			i--;
		}
	}
}


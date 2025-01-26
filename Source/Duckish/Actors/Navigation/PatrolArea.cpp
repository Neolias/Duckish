// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrolArea.h"

#include "Waypoint.h"


APatrolArea::APatrolArea()
{
	PrimaryActorTick.bCanEverTick = false;
}

AWaypoint* APatrolArea::GetRandomWaypoint()
{
	if (!ValidWaypoints.IsEmpty())
	{
		return ValidWaypoints.Last();
	}

	return nullptr;
}

void APatrolArea::CheckOutWaypoint(AWaypoint* Waypoint)
{
	if (ValidWaypoints.Contains(Waypoint))
	{
		ValidWaypoints.RemoveSingleSwap(Waypoint);
	}
}

void APatrolArea::BeginPlay()
{
	Super::BeginPlay();

	if (ValidWaypoints.IsEmpty())
	{
		GenerateWaypoints();
	}
}

void APatrolArea::GenerateWaypoints()
{
	ValidWaypoints.Reserve(NumberOfWaypoints);

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;
	FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, false);

	for (int i = 0; i < NumberOfWaypoints; ++i)
	{
		const float PosX = FMath::RandRange(-AreaRadius, AreaRadius);
		const float PosY = FMath::RandRange(-AreaRadius, AreaRadius);
		const float PosZ = FMath::RandRange(0.f, AreaHeight);
		const float Yaw = FMath::RandRange(-180.f, 180.f);
		FVector SpawnLocation = GetActorLocation() + FVector(PosX, PosY, PosZ);
		AWaypoint* NewWaypoint = GetWorld()->SpawnActor<AWaypoint>(WaypointClass, SpawnLocation, FRotator(0.f, Yaw, 0.f), SpawnParameters);
		if (IsValid(NewWaypoint))
		{
			NewWaypoint->AttachToActor(this, AttachmentRules);
			NewWaypoint->SetPatrolArea(this);
			ValidWaypoints.Push(NewWaypoint);
		}
		else
		{
			i--;
		}
	}
}


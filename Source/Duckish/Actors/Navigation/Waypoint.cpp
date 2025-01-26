// Fill out your copyright notice in the Description page of Project Settings.


#include "Waypoint.h"

#include "PatrolArea.h"
#include "Components/SphereComponent.h"
#include "Data/DamageTypes/BubbleDamageType.h"


AWaypoint::AWaypoint()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->InitSphereRadius(5.f);
	SetRootComponent(CollisionComponent);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(CollisionComponent);
	StaticMeshComponent->SetIsReplicated(true);
}

void AWaypoint::BeginPlay()
{
	Super::BeginPlay();

	OnTakeAnyDamage.AddDynamic(this, &AWaypoint::OnDamageTaken);
}

void AWaypoint::OnDamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (DamageType->IsA<UBubbleDamageType>())
	{
		BecomeSaved();
	}
	else
	{
		TriggerDeath();
	}
}

void AWaypoint::BecomeSaved_Implementation()
{
	PatrolArea->CheckOutWaypoint(this);
}

void AWaypoint::TriggerDeath()
{
	if (PatrolArea.Get())
	{
		PatrolArea->CheckOutWaypoint(this);
		Destroy();
	}
}


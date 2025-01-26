// Fill out your copyright notice in the Description page of Project Settings.


#include "AICat.h"

#include "Components/CapsuleComponent.h"
#include "Components/CharacterComponents/BasePawnMovement.h"


void AAICat::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bIsEmerging)
	{
		CapsuleCollision->AddForce(FVector::UpVector * DeathEmergeForce * DeltaSeconds);
	}
}

void AAICat::BeginPlay()
{
	Super::BeginPlay();

	OnTakeAnyDamage.AddDynamic(this, &AAICat::OnDamageTaken);
}

void AAICat::OnDamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	TriggerDeath();
}

void AAICat::TriggerDeath_Implementation()
{
	bIsEmerging = true;
	CapsuleCollision->SetSimulatePhysics(true);
	BasePawnMovement->MaxSpeed = 0.f;
	GetWorldTimerManager().SetTimer(EmergeTimerHandle, [this] {OnDeath(); }, DeathEmergeLength, false);
}

void AAICat::OnDeath()
{
	//SetActorTickEnabled(false);
	//SetActorEnableCollision(false);
	//SkeletalMesh->SetVisibility(false, true);
	Destroy();

}

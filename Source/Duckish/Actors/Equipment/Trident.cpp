// Fill out your copyright notice in the Description page of Project Settings.


#include "Trident.h"

#include "Characters/BasePawn.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"

ATrident::ATrident()
{
	USceneComponent* DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));
	SetRootComponent(DefaultRoot);
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(DefaultRoot);
}

void ATrident::StartFire()
{
	if (!IsValid(CachedBasePawn) || bIsFiring)
	{
		return;
	}

	if (CachedBasePawn->IsLocallyControlled())
	{
		GetWorld()->GetTimerManager().ClearTimer(OneShotTimer);
		float FirePeriod = 60.f / FireRate;
		GetWorld()->GetTimerManager().SetTimer(OneShotTimer, [this]() { MakeOneShot(); }, FirePeriod, true, -FirePeriod);
	}

	bIsFiring = true;
}

void ATrident::StopFire()
{
	if (IsValid(CachedBasePawn) && CachedBasePawn->IsLocallyControlled())
	{
		GetWorld()->GetTimerManager().ClearTimer(OneShotTimer);
	}
	bIsFiring = false;
}

void ATrident::MakeOneShot()
{
	if (!IsValid(CachedBasePawn) || !CachedBasePawn->IsLocallyControlled())
	{
		return;
	}

	if (IsValid(PawnFireMontage))
	{
		USkeletalMeshComponent* SkeletalMesh = CachedBasePawn->GetSkeletalMesh();
		if (IsValid(SkeletalMesh))
		{
			SkeletalMesh->PlayAnimation(PawnFireMontage, false);
		}
	}

	if (IsValid(FireSound))
	{
		UGameplayStatics::SpawnSoundAttached(FireSound, RootComponent);
	}

	ShootProjectile();

	GetWorld()->GetTimerManager().SetTimer(OnShotEndTimer, this, &ATrident::OnShotEnd, 60.f / FireRate, false);
}

void ATrident::OnShotEnd()
{
	bIsFiring = false;
}

void ATrident::ShootProjectile()
{
	const AController* Controller = CachedBasePawn->GetController();
	if (!IsValid(Controller))
	{
		return;
	}

	if (!IsValid(CachedBasePawn) || !CachedBasePawn->IsLocallyControlled() || !IsValid(StaticMesh))
	{
		return;
	}

	FVector ViewPointLocation;
	FRotator ViewPointRotation;
	Controller->GetPlayerViewPoint(ViewPointLocation, ViewPointRotation);
	const FVector SpawnLocation = StaticMesh->GetSocketLocation(SpawnSocketName);
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = GetOwningPawn();
	ADuckishProjectile* Projectile = GetWorld()->SpawnActor<ADuckishProjectile>(ProjectileClass, SpawnLocation, FRotator::ZeroRotator, SpawnParameters);

	Projectile->OnCollisionComponentHitEvent.AddDynamic(this, &ATrident::ProcessProjectileHit);
	Projectile->SetProjectileActive(true);
	Projectile->Launch(ViewPointRotation.Vector());
}

APawn* ATrident::GetOwningPawn()
{
	APawn* PawnOwner = Cast<APawn>(GetOwner());
	if (!IsValid(PawnOwner))
	{
		PawnOwner = Cast<APawn>(GetOwner()->GetOwner());
	}
	return PawnOwner;
}

void ATrident::ProcessProjectileHit(ADuckishProjectile* Projectile, const FVector MovementDirection, const FHitResult& Hit)
{
	FPointDamageEvent DamageEvent;
	DamageEvent.HitInfo = Hit;
	DamageEvent.ShotDirection = MovementDirection;
	AActor* DamagedActor = Hit.GetActor();
	if (IsValid(DamagedActor) && IsValid(CachedBasePawn))
	{
		DamagedActor->TakeDamage(Damage, DamageEvent, CachedBasePawn->GetController(), CachedBasePawn);
	}

	if (IsValid(HitSound))
	{
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), HitSound, Projectile->GetActorLocation());
	}

	Projectile->OnCollisionComponentHitEvent.RemoveAll(this);
	Projectile->Destroy();
}

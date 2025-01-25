// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Equipment/EquipmentItem.h"
#include "Actors/Projectiles/DuckishProjectile.h"
#include "Trident.generated.h"

class ADuckishProjectile;

UCLASS()
class DUCKISH_API ATrident : public AEquipmentItem
{
	GENERATED_BODY()

public:
	ATrident();
	void StartFire();
	void StopFire();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "Trident"))
	UStaticMeshComponent* StaticMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "Trident | Shooting"))
	float FireRate = 120.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "Trident | Shooting"))
	TSubclassOf<class ADuckishProjectile> ProjectileClass = ADuckishProjectile::StaticClass();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "Trident | Shooting"))
	FName SpawnSocketName = FName("SpawnSocket");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = "Trident | Shooting"))
	float Damage = 1.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Trident | Animations")
	UAnimMontage* PawnFireMontage;

private:
	FTimerHandle OneShotTimer;
	FTimerHandle OnShotEndTimer;
	bool bIsFiring = false;

	UFUNCTION()
	void MakeOneShot();
	UFUNCTION()
	void OnShotEnd();
	void ShootProjectile();
	APawn* GetOwningPawn();
	UFUNCTION()
	void ProcessProjectileHit(ADuckishProjectile* Projectile, const FVector MovementDirection, const FHitResult& Hit);
	
};

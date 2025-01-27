// Fill out your copyright notice in the Description page of Project Settings.


#include "DuckishProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

ADuckishProjectile::ADuckishProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetCollisionProfileName("BlockAllDynamic");
	CollisionComponent->InitSphereRadius(5.f);
	SetRootComponent(CollisionComponent);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(CollisionComponent);
	StaticMeshComponent->SetIsReplicated(true);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
	ProjectileMovementComponent->MaxSpeed = MaxSpeed;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->Bounciness = Bounciness;
	ProjectileMovementComponent->SetAutoActivate(false);

	//SetReplicates(true);
	SetReplicateMovement(true);
	SetProjectileActive(false);
}

void ADuckishProjectile::BeginPlay()
{
	Super::BeginPlay();

	CollisionComponent->OnComponentHit.AddDynamic(this, &ADuckishProjectile::OnCollisionComponentHit);
}

APawn* ADuckishProjectile::GetOwningPawn() const
{
	APawn* PawnOwner = Cast<APawn>(GetOwner());
	if (!IsValid(PawnOwner))
	{
		PawnOwner = Cast<APawn>(GetOwner()->GetOwner());
	}
	return PawnOwner;
}

void ADuckishProjectile::OnCollisionComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                                                 UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OnCollisionComponentHitEvent.IsBound())
	{
		OnCollisionComponentHitEvent.Broadcast(this, ProjectileMovementComponent->Velocity.GetSafeNormal(), Hit);
	}
}

void ADuckishProjectile::SetProjectileActive(bool bIsActive)
{
	ProjectileMovementComponent->SetActive(bIsActive);
	SetActorTickEnabled(bIsActive);
	SetActorEnableCollision(bIsActive);
	StaticMeshComponent->SetVisibility(bIsActive, true);
}

void ADuckishProjectile::Launch(FVector Direction)
{
	CollisionComponent->IgnoreActorWhenMoving(GetOwningPawn(), true);
	ProjectileMovementComponent->MaxSpeed = MaxSpeed;
	ProjectileMovementComponent->Velocity = LaunchSpeed * Direction;
	ProjectileMovementComponent->Bounciness = Bounciness;

	GetWorldTimerManager().SetTimer(TimeToLiveHandle, this, &ADuckishProjectile::OnTimeToLiveEnded, TimeToLive, false);
}

void ADuckishProjectile::OnTimeToLiveEnded()
{
	//SetProjectileActive(false);
	Destroy();
}

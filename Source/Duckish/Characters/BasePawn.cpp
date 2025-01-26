// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"

#include "Components/CapsuleComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Actors/Equipment/Trident.h"
#include "Duckish/Components/CharacterComponents/BasePawnMovement.h"

ABasePawn::ABasePawn()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollision"));
	SetRootComponent(CapsuleCollision);
	BasePawnMovement = CreateDefaultSubobject<UBasePawnMovement>(TEXT("BasePawnMovement"));
	BasePawnMovement->SetUpdatedComponent(CapsuleCollision);
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->SetupAttachment(CapsuleCollision);
	SkeletalMesh->bCastDynamicShadow = false;
	SkeletalMesh->CastShadow = false;

	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = true;
}

void ABasePawn::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(SkeletalMesh) && IsValid(WeaponClass))
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = this;
		CurrentWeapon = GetWorld()->SpawnActor<AEquipmentItem>(WeaponClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParameters);
		CurrentWeapon->AttachToComponent(SkeletalMesh, FAttachmentTransformRules::KeepRelativeTransform, WeaponSocketName);
	}
}

void ABasePawn::Move(const FInputActionValue& Value)
{
	const FVector MovementVector = Value.Get<FVector>();

	if (Controller != nullptr)
	{
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
		AddMovementInput(GetActorUpVector(), MovementVector.Z);
	}
}

void ABasePawn::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ABasePawn::Shoot(const FInputActionValue& Value)
{
	const bool bIsKeyHeld = Value.Get<bool>();

	ATrident* Trident = Cast<ATrident>(CurrentWeapon);
	if (IsValid(Trident))
	{
		if (bIsKeyHeld)
		{
			Trident->StartFire();
		}
		else
		{
			Trident->StopFire();
		}
	}
}

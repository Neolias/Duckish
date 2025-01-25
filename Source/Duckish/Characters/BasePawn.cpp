// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"

#include "Components/CapsuleComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Duckish/Components/CharacterComponents/BasePawnMovement.h"

ABasePawn::ABasePawn()
{
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));
	BasePawnMovement = CreateDefaultSubobject<UBasePawnMovement>(TEXT("BasePawnMovement"));
	BasePawnMovement->SetUpdatedComponent(DefaultRoot);
	CapsuleCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollision"));
	CapsuleCollision->SetupAttachment(DefaultRoot);
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->SetupAttachment(CapsuleCollision);
	SkeletalMesh->SetOnlyOwnerSee(true);
	SkeletalMesh->bCastDynamicShadow = false;
	SkeletalMesh->CastShadow = false;

	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = true;
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

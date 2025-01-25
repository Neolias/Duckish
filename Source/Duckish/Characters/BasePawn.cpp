// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Duckish/Components/CharacterComponents/BasePawnMovement.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));
	BasePawnMovement = CreateDefaultSubobject<UBasePawnMovement>(TEXT("BasePawnMovement"));
	BasePawnMovement->SetUpdatedComponent(DefaultRoot);
	CapsuleCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollision"));
	CapsuleCollision->SetupAttachment(DefaultRoot);
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->SetupAttachment(CapsuleCollision);
	if (IsValid(SkeletalMesh))
	{
		SkeletalMesh->SetOwnerNoSee(true);
		SkeletalMesh->bCastHiddenShadow = true;
	}
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("FPCamera"));
	Camera->SetupAttachment(SkeletalMesh, CameraSocket);
	Camera->bUsePawnControlRotation = true;

}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class DUCKISH_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	ABasePawn();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Category = "Components"))
	class UBasePawnMovement* BasePawnMovement;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Category = "Components"))
	class UCapsuleComponent* CapsuleCollision;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Category = "Components"))
	USkeletalMeshComponent* SkeletalMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Category = "Components"))
	class UCameraComponent* Camera;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Category = "Components | Camera"))
	FName CameraSocket = FName("CameraSocket");

};

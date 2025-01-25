// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

struct FInputActionValue;
class UInputAction;

UCLASS()
class DUCKISH_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	ABasePawn();

protected:
	virtual void Move(const FInputActionValue& Value);
	virtual void Look(const FInputActionValue& Value);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = Components))
	class UBasePawnMovement* BasePawnMovement;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = Components))
	class UCapsuleComponent* CapsuleCollision;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = Components))
	USkeletalMeshComponent* SkeletalMesh;

};

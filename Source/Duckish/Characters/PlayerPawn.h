// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "PlayerPawn.generated.h"

/**
 * 
 */
UCLASS()
class DUCKISH_API APlayerPawn : public ABasePawn
{
	GENERATED_BODY()

public:
	APlayerPawn();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void NotifyControllerChanged() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = Components))
	class UCameraComponent* Camera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = Camera))
	FName CameraSocket = FName("CameraSocket");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	class UInputMappingContext* DefaultMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	UInputAction* LookAction;
};

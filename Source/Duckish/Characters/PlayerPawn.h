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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Category = Components))
	class UCameraComponent* Camera;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Category = Camera))
	FName CameraSocket = FName("CameraSocket");
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputMappingContext* DefaultMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* LookAction;
};

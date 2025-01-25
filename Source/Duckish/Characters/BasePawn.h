// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Equipment/EquipmentItem.h"
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
	void BeginPlay() override;
	USkeletalMeshComponent* GetSkeletalMesh() const { return SkeletalMesh; }

protected:
	virtual void Move(const FInputActionValue& Value);
	virtual void Look(const FInputActionValue& Value);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = Components))
	class UBasePawnMovement* BasePawnMovement;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = Components))
	class UCapsuleComponent* CapsuleCollision;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = Components))
	USkeletalMeshComponent* SkeletalMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = Equipment))
	TSubclassOf<AEquipmentItem> Weapon = AEquipmentItem::StaticClass();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Category = Equipment))
	FName WeaponSocketName = FName("WeaponSocket");


};

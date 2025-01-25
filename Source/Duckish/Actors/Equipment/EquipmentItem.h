// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EquipmentItem.generated.h"

UCLASS()
class DUCKISH_API AEquipmentItem : public AActor
{
	GENERATED_BODY()
	
public:	
	AEquipmentItem();

protected:
	virtual void SetOwner(AActor* NewOwner) override;
	TObjectPtr<class ABasePawn> CachedBasePawn;

};

// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentItem.h"

#include "Characters/BasePawn.h"

AEquipmentItem::AEquipmentItem()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEquipmentItem::SetOwner(AActor* NewOwner)
{
	Super::SetOwner(NewOwner);


	if (IsValid(NewOwner))
	{
		checkf(GetOwner()->IsA<ABasePawn>(), TEXT("EquipmentItem object should be owned by ABasePawn."))
			CachedBasePawn = StaticCast<ABasePawn*>(GetOwner());
		if (GetLocalRole() == ROLE_Authority)
		{
			SetAutonomousProxy(true);
		}
	}
	else
	{
		CachedBasePawn = nullptr;
	}
}


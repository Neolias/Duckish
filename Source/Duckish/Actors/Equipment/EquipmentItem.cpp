// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Equipment/EquipmentItem.h"

// Sets default values
AEquipmentItem::AEquipmentItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEquipmentItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEquipmentItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


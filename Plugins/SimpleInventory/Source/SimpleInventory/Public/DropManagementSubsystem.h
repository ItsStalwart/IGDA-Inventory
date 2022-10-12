// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ItemDatabase.h"
#include "DropManagementSubsystem.generated.h"

class UDropTableComponent;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FItemDropped,int, DropId, int, DropQuantity,FTransform,DropLocation);
/**
 * 
 */
UCLASS()
class SIMPLEINVENTORY_API UDropManagementSubsystem final : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	FItemDropped OnItemDroppedEvent;
public:
	UFUNCTION()
	void SpawnDrop(int ItemId, int ItemQuantity, FTransform SpawnLocation) const;

	UFUNCTION()
	FItemDropped& GetOnItemDroppedEvent() {return OnItemDroppedEvent;};
};

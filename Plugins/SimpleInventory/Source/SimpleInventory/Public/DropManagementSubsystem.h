// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DropTableComponent.h"
#include "ItemDatabase.h"
#include "DropManagementSubsystem.generated.h"

class UDropTableComponent;
/**
 * 
 */
UCLASS()
class SIMPLEINVENTORY_API UDropManagementSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	UDropManagementSubsystem();
	UPROPERTY(EditAnywhere)
	UItemDatabase* MainDatabase {nullptr};
public:
	UFUNCTION()
	void SpawnDrop(int ItemId, int ItemQuantity, FTransform SpawnLocation);
};

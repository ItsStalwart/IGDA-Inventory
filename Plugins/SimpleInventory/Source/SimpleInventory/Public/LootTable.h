// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LootTable.generated.h"


USTRUCT(BlueprintType)
struct FLootTableElement
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	int ElementId;
	UPROPERTY(EditAnywhere,meta=(Units="Percent", ClampMin="0.0",ClampMax="100.0", UIMin = "0.0", UIMax = "100.0"))
	float ElementDropChance;
};
/**
 * 
 */
UCLASS()
class SIMPLEINVENTORY_API ULootTable final : public UDataAsset
{
	GENERATED_BODY()

	
	UPROPERTY(EditAnywhere)
	TArray<FLootTableElement> ItemDropChances{ };
public:
	UFUNCTION(BlueprintCallable)
	TArray<FLootTableElement> GetItemDropChances(){ return ItemDropChances;};
};

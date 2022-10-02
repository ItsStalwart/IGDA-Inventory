// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemData.h"
#include "UObject/NoExportTypes.h"
#include "InventorySlotData.generated.h"


/**
 * 
 */
UCLASS(BlueprintType)
class SIMPLEINVENTORY_API UInventorySlotData : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	UItemData* ContainedItem;

	UPROPERTY(BlueprintReadWrite)
	int ContentCount;
};

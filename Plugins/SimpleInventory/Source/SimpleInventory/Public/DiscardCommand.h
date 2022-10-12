// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryContextCommand.h"
#include "DiscardCommand.generated.h"

/**
 * 
 */
UCLASS(Blueprintable,BlueprintType)
class SIMPLEINVENTORY_API UDiscardCommand final : public UInventoryContextCommand
{
	GENERATED_BODY()
	
	virtual void Execute() override;
	virtual void Undo() override;
	int DiscardedId {0};
	int DiscardedQuantity {0};
};

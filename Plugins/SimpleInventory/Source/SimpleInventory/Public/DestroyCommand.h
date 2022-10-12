// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryContextCommand.h"
#include "DestroyCommand.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLEINVENTORY_API UDestroyCommand final : public UInventoryContextCommand
{
	GENERATED_BODY()
	virtual void Execute() override;
	virtual void Undo() override;
	int DestroyedId {0};
	int DestroyedQuantity {0};
	
};

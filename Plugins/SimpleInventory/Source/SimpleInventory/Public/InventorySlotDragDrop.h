// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "InventorySlotDragDrop.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLEINVENTORY_API UInventorySlotDragDrop : public UDragDropOperation
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UUserWidget* DragWidget {nullptr};

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int DraggedContent {0};
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int DraggedCount {0};
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int DraggedIndex {0};
	
};

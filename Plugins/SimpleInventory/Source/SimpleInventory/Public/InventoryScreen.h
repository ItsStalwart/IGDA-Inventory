// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryComponent.h"
#include "InventoryPanel.h"
#include "Blueprint/UserWidget.h"
#include "Components/Border.h"
#include "Components/TileView.h"
#include "InventoryScreen.generated.h"


/**
 * 
 */
UCLASS()
class SIMPLEINVENTORY_API UInventoryScreen : public UUserWidget
{
	GENERATED_BODY()
	UPROPERTY(meta=(BindWidget))
	UBorder* InventoryBorder {nullptr};
	UPROPERTY(meta=(BindWidget))
	UInventoryPanel* InventoryPanel {nullptr};
	
	FVector2D DragOffset;
public:
	UFUNCTION(BlueprintCallable)
	UInventoryPanel* GetPanel() {return InventoryPanel;};
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	                          UDragDropOperation* InOperation) override;
	virtual void NativeOnInitialized() override;
};

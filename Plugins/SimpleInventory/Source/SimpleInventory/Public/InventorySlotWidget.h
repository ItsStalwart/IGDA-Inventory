// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "InventorySlotData.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "InventorySlotWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInventorySlotDrag, int, DraggedIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInventorySlotRightClick, int, TargetIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FInventorySlotDrop, int, DraggedIndex, int, DroppedIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FInventorySlotDragCancelled, int, DraggedIndex, int, DraggedContent, int, DraggedCount);
/**
 * 
 */
UCLASS()
class SIMPLEINVENTORY_API UInventorySlotWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

	UPROPERTY()
	UInventorySlotData* SlotData {nullptr};

	UPROPERTY(meta=(BindWidget))
	int SlotIndex {0};

	UPROPERTY(meta=(BindWidget))
	UImage* Icon {nullptr};

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Count {nullptr};
	UPROPERTY(BlueprintAssignable)
	FInventorySlotRightClick InventorySlotRightClickEvent;
	UPROPERTY(BlueprintAssignable)
	FInventorySlotDrag InventorySlotDragEvent;
	UPROPERTY(BlueprintAssignable)
	FInventorySlotDrop InventorySlotDropEvent;
	
public:
	UFUNCTION(BlueprintImplementableEvent)
	void OnContextMenuRequestClose();
	FInventorySlotDrag& OnInventorySlotDrag() {return InventorySlotDragEvent;};
	FInventorySlotRightClick& OnInventorySlotRightClick() {return InventorySlotRightClickEvent;};
	FInventorySlotDrop& OnInventorySlotDrop() {return InventorySlotDropEvent;};
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
};

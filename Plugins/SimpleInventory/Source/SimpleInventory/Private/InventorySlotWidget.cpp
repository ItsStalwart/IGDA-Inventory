// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySlotWidget.h"

#include "InventorySlotDragDrop.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

FReply UInventorySlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	if(InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton))
	{
		InventorySlotRightClickEvent.Broadcast(this->SlotIndex);
		return FReply::Handled();
	}
	FEventReply ReplyResult = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
	return ReplyResult.NativeReply;
}

void UInventorySlotWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
											UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	
	UInventorySlotDragDrop* DragDropOperation = NewObject<UInventorySlotDragDrop>();
	this->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	DragDropOperation->DragWidget = this;
	DragDropOperation->DraggedIndex = this->SlotIndex;
	DragDropOperation->DraggedContent = this->SlotData->ContainedItem->ItemId;
	DragDropOperation->DraggedCount = this->SlotData->ContentCount;
	DragDropOperation->DefaultDragVisual = DuplicateObject(this,nullptr);
	DragDropOperation->DefaultDragVisual->SetRenderOpacity(.7f);
	DragDropOperation->Pivot = EDragPivot::MouseDown;
	InventorySlotDragEvent.Broadcast(this->SlotIndex);
	OutOperation = DragDropOperation;
}

void UInventorySlotWidget::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);
}

bool UInventorySlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
                                        UDragDropOperation* InOperation)
{
	UE_LOG(LogTemp, Warning, TEXT("Dragged slot dropped"))
	UInventorySlotDragDrop* DragOperation = Cast<UInventorySlotDragDrop>(InOperation);
	if(!IsValid(DragOperation))
	{
		return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	}
	InventorySlotDropEvent.Broadcast(DragOperation->DraggedIndex,this->SlotIndex);
	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}


void UInventorySlotWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	UInventorySlotData* InDataObject = Cast<UInventorySlotData>( ListItemObject);
	SlotData = InDataObject;
	Icon->SetBrushFromTexture(InDataObject->ContainedItem->ItemThumbnail);
	Count->SetText(FText::FromString(FString::FromInt(InDataObject->ContentCount)));
	SlotIndex = InDataObject->SlotIndex;
}

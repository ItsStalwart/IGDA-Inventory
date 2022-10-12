// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryScreen.h"

#include "InventoryComponent.h"
#include "InventorySlotData.h"
#include "InventorySlotDragDrop.h"
#include "InventorySlotWidget.h"
#include "SimpleInventory.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

bool UInventoryScreen::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	UInventorySlotDragDrop* DragOperation = Cast<UInventorySlotDragDrop>(InOperation);
	if(!IsValid(DragOperation))
	{
		return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	}
	const FVector2D DropLocation = InDragDropEvent.GetScreenSpacePosition();
	if (!InventoryBorder->GetCachedGeometry().IsUnderLocation(DropLocation))
	{
		InventoryPanel->GetOwnerInventory()->DropItemFromSlot(DragOperation->DraggedIndex);
	}
	UE_LOG(LogTemp,Warning, TEXT("Drop Operation"));
	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}

void UInventoryScreen::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	AActor* OwnerPawn = GetOwningPlayerPawn();
	UInventoryComponent* RefComponent = Cast<UInventoryComponent>(OwnerPawn->GetComponentByClass(UInventoryComponent::StaticClass()));
	InventoryPanel->SetCorrespondingInventory(RefComponent, OwnerPawn);
}

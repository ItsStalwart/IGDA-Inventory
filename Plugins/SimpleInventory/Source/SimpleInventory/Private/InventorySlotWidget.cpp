// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySlotWidget.h"

void UInventorySlotWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	const UInventorySlotData* InDataObject = Cast<UInventorySlotData>( ListItemObject);
	Icon->SetBrushFromTexture(InDataObject->ContainedItem->ItemThumbnail);
	Count->SetText(FText::FromString(FString::FromInt(InDataObject->ContentCount)));
}

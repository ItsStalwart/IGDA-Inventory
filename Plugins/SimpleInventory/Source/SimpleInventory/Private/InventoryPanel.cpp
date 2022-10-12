// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryPanel.h"

#include "InventorySlotWidget.h"
#include "SimpleInventory.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

ITypedUMGListView<UObject*>::FSimpleListItemEvent& UInventoryPanel::OnItemClicked() const
{
	return Super::OnItemClicked();
}

void UInventoryPanel::RefreshView(TArray<int> NewContents, TArray<int> NewCounts)
{
		for (int i=0;i< this->GetListItems().Num();i++)
		{
			UInventorySlotWidget* ItemWidget = Cast<UInventorySlotWidget>(this->GetEntryWidgetFromItem(this->GetItemAt(i)));
			if (ItemWidget != nullptr)
			{
				ItemWidget->OnInventorySlotDrag().Clear();
			}
		}
		this->SetListItems(ConstructItemList(NewContents,NewCounts));
}

TArray<class UInventorySlotData*> UInventoryPanel::ConstructItemList(const TArray<int> NewContents, const TArray<int> NewCounts) const
{
	TArray<class UInventorySlotData*> ReturnData;
	ReturnData.Empty();
	for(int i = 0; i<NewContents.Num();i++)
	{
		UInventorySlotData* NewSlot = NewObject<UInventorySlotData>();
		NewSlot->ContainedItem = FSimpleInventoryModule::GetDefaultDatabase()->GetItemDataById(NewContents[i]);
		NewSlot->ContentCount = NewCounts[i];
		NewSlot->SlotIndex = i;
		ReturnData.Emplace(NewSlot);
	}
	return ReturnData;
}


void UInventoryPanel::SetCorrespondingInventory(UInventoryComponent* InInventory, AActor* OwningPawn)
{
	OwnerInventory = InInventory;
	OwnerInventory->OnInventoryContentChanged().AddDynamic(this, &UInventoryPanel::RefreshView);
	OwningPawn->OnDestroyed.AddDynamic(this, &UInventoryPanel::Deregister);
	//OnEntryWidgetGenerated().AddUObject(this, &UInventoryPanel::RegisterDrag);
	//OnEntryWidgetReleased().Add(&UInventoryPanel::DeregisterDrag);
}

void UInventoryPanel::Deregister(AActor* Owner)
{
	OwnerInventory->OnInventoryContentChanged().RemoveAll(this);
	Owner->OnDestroyed.RemoveAll(this);
}

/*UListViewBase::FOnListEntryGenerated UInventoryPanel::RegisterDrag()
{
	for (int i=0;i< this->GetListItems().Num();i++)
	{
		UInventorySlotWidget* ItemWidget = Cast<UInventorySlotWidget>(this->GetEntryWidgetFromItem(this->GetItemAt(i)));
		if (ItemWidget != nullptr)
		{
			ItemWidget->OnInventorySlotDrag().Clear();
		}
	}
}

void UInventoryPanel::DeregisterDrag(UUserWidget** Widget)
{
}*/

void UInventoryPanel::OnSlotDragged(int DraggedIndex)
{
	//OwnerInventory->RemoveItemFromSlot(DraggedIndex);
}

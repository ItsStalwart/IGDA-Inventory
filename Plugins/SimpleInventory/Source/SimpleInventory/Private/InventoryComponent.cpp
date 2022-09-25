// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

#include "IDetailTreeNode.h"
#include "Serialization/PropertyLocalizationDataGathering.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	this->InitializeInventory(InventoryCapacity);
	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UInventoryComponent::InitializeInventory(const int InventorySize)
{
	this->InventoryContents.Empty(InventorySize);
	this->ContentQuantities.Empty(InventorySize);
}

void UInventoryComponent::LoadInventoryContents(const TArray<int> InInventoryContents, const TArray<int> InInventoryQuantities)
{
	this->InventoryContents = InInventoryContents;
	this->ContentQuantities = InInventoryQuantities;
	InventoryContentChangedEvent.Broadcast();
}

void UInventoryComponent::EmptyInventory(TArray<int>& OutInventoryContents, TArray<int>& OutInventoryQuantities)
{
	OutInventoryContents = this->InventoryContents;
	OutInventoryQuantities = this->ContentQuantities;
	this->InventoryContents.Empty(this->InventoryCapacity);
	this->ContentQuantities.Empty(this->InventoryCapacity);
	InventoryContentChangedEvent.Broadcast();
}

void UInventoryComponent::AddItem(const int ItemId, const int Quantity)
{
	if(this->IsInventoryFull())
	{
		ItemAddFailedEvent.Broadcast(ItemId,Quantity,TEXT("Inventory is full!"));
		return;
	}
	const int FoundPosition = InventoryContents.Find(ItemId);
	if (FoundPosition)
	{
		ContentQuantities[FoundPosition] += Quantity;
		InventoryContentChangedEvent.Broadcast();
		return;
	}
	const int NewPosition = InventoryContents.Emplace(ItemId);
	ContentQuantities.EmplaceAt(NewPosition,Quantity);
	InventoryContentChangedEvent.Broadcast();
}

void UInventoryComponent::RemoveItem(const int ItemId, const int Quantity)
{
	const int FoundPosition = InventoryContents.Find(ItemId);
	if (FoundPosition)
	{
		if (ContentQuantities[FoundPosition] >= Quantity)
		{
			ContentQuantities[FoundPosition] -= Quantity;
			CleanEmptySlots();
			InventoryContentChangedEvent.Broadcast();
			return;
		}
		UE_LOG(LogTemp,Warning, TEXT("Attempted to remove unavailable item quantities"))
		return;
	}
	UE_LOG(LogTemp,Warning, TEXT("Attempted to remove inexistant item"));
}

void UInventoryComponent::MoveItem(const int OriginalSlot, const int TargetSlot)
{
	if(!(InventoryContents.IsValidIndex(OriginalSlot)))
	{
		UE_LOG(LogTemp, Warning, TEXT("Attempted to move item from nonexistant slot"));
		return;
	}
	if(InventoryCapacity != 0 && TargetSlot >= InventoryCapacity)
	{
		UE_LOG(LogTemp, Warning, TEXT("Attempted to move item to nonexistant slot"));
		return;
	}
	if (InventoryContents.IsValidIndex(TargetSlot))
	{
		InventoryContents.Swap(OriginalSlot,TargetSlot);
		ContentQuantities.Swap(OriginalSlot,TargetSlot);
		InventoryContentChangedEvent.Broadcast();
		return;
	}
	InventoryContents.EmplaceAt(TargetSlot,InventoryContents[OriginalSlot]);
	ContentQuantities.EmplaceAt(TargetSlot,ContentQuantities[OriginalSlot]);
	InventoryContents.RemoveAt(OriginalSlot);
	ContentQuantities.RemoveAt(OriginalSlot);
	InventoryContentChangedEvent.Broadcast();
}

bool UInventoryComponent::IsInventoryFull() const
{
	if (InventoryCapacity == 0)
	{
		return false;
	}
	return InventoryCapacity > InventoryContents.Num();
}

void UInventoryComponent::CleanEmptySlots()
{
	for (auto Element : ContentQuantities)
	{
		if(Element <= 0)
		{
			InventoryContents.RemoveAt(ContentQuantities.Find(Element));
			ContentQuantities.Remove(Element);
		}
	}
}


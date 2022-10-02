// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

#include "DropManagementSubsystem.h"
#include "DroppedItemActor.h"
#include "IDetailTreeNode.h"
#include "Serialization/PropertyLocalizationDataGathering.h"
DEFINE_LOG_CATEGORY(LogInventoryComponent);
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

	DropManager = GetWorld()->GetGameInstance()->GetSubsystem<UDropManagementSubsystem>();
	GetOwner()->OnActorBeginOverlap.AddUniqueDynamic(this, &UInventoryComponent::PickUpItem);
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
	InventoryContentChangedEvent.Broadcast(InventoryContents,ContentQuantities);
}

void UInventoryComponent::EmptyInventory(TArray<int>& OutInventoryContents, TArray<int>& OutInventoryQuantities)
{
	OutInventoryContents = this->InventoryContents;
	OutInventoryQuantities = this->ContentQuantities;
	this->InventoryContents.Empty(this->InventoryCapacity);
	this->ContentQuantities.Empty(this->InventoryCapacity);
	InventoryContentChangedEvent.Broadcast(InventoryContents,ContentQuantities);
}

void UInventoryComponent::AddItem(const int ItemId, const int Quantity)
{
	if(Quantity==0)
	{
		UE_LOG(LogTemp,Warning, TEXT("Call to add 0 items"))
		return;
	}
	if(this->IsInventoryFull())
	{
		ItemAddFailedEvent.Broadcast(ItemId,Quantity,TEXT("Inventory is full!"), GetOwner()->GetTransform());
		DropManager->SpawnDrop(ItemId,Quantity, GetOwner()->GetTransform());
		return;
	}
	const int FoundPosition = InventoryContents.Find(ItemId);
	if (FoundPosition>=0)
	{
		ContentQuantities[FoundPosition] += Quantity;
		InventoryContentChangedEvent.Broadcast(InventoryContents,ContentQuantities);
		return;
	}
	const int NewPosition = InventoryContents.Emplace(ItemId);
	ContentQuantities.EmplaceAt(NewPosition,Quantity);
	InventoryContentChangedEvent.Broadcast(InventoryContents,ContentQuantities);
}

void UInventoryComponent::RemoveItem(const int ItemId, const int Quantity)
{
	if(Quantity==0)
	{
		UE_LOG(LogInventoryComponent,Warning, TEXT("Call to remove 0 items"))
		return;
	}
	const int FoundPosition = InventoryContents.Find(ItemId);
	if (FoundPosition>=0)
	{
		if (ContentQuantities[FoundPosition] >= Quantity)
		{
			ContentQuantities[FoundPosition] -= Quantity;
			CleanEmptySlots();
			InventoryContentChangedEvent.Broadcast(InventoryContents,ContentQuantities);
			return;
		}
		UE_LOG(LogInventoryComponent,Warning, TEXT("Attempted to remove unavailable item quantities"))
		return;
	}
	UE_LOG(LogInventoryComponent,Warning, TEXT("Attempted to remove inexistant item"));
}

void UInventoryComponent::MoveItem(const int OriginalSlot, const int TargetSlot)
{
	if(!(InventoryContents.IsValidIndex(OriginalSlot)))
	{
		UE_LOG(LogInventoryComponent, Warning, TEXT("Attempted to move item from nonexistant slot"));
		return;
	}
	if(InventoryCapacity != 0 && TargetSlot >= InventoryCapacity)
	{
		UE_LOG(LogInventoryComponent, Warning, TEXT("Attempted to move item to nonexistant slot"));
		return;
	}
	if (InventoryContents.IsValidIndex(TargetSlot))
	{
		InventoryContents.Swap(OriginalSlot,TargetSlot);
		ContentQuantities.Swap(OriginalSlot,TargetSlot);
		InventoryContentChangedEvent.Broadcast(InventoryContents,ContentQuantities);
		return;
	}
	InventoryContents.EmplaceAt(TargetSlot,InventoryContents[OriginalSlot]);
	ContentQuantities.EmplaceAt(TargetSlot,ContentQuantities[OriginalSlot]);
	InventoryContents.RemoveAt(OriginalSlot);
	ContentQuantities.RemoveAt(OriginalSlot);
	InventoryContentChangedEvent.Broadcast(InventoryContents,ContentQuantities);
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

void UInventoryComponent::PickUpItem(AActor* Owner, AActor* ItemToPickUp)
{
	const ADroppedItemActor* Drop = Cast<ADroppedItemActor>(ItemToPickUp);
	if(Drop == nullptr)
	{
		return;
	}
	AddItem(Drop->GetAssociatedId(),Drop->GetStackSize());
	ItemToPickUp->Destroy();
}


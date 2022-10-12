// Fill out your copyright notice in the Description page of Project Settings.


#include "DropManagementSubsystem.h"

#include "DroppedItemActor.h"
#include "SimpleInventory.h"


void UDropManagementSubsystem::SpawnDrop(const int ItemId, const int ItemQuantity, const FTransform SpawnLocation) const
{
	UItemData* SpawnedItemData = FSimpleInventoryModule::GetDefaultDatabase()->GetItemDataById(ItemId);
	if(!IsValid(SpawnedItemData))
	{
		UE_LOG(LogTemp,Warning,TEXT("Attempt to spawn invalid item, check requested Id: %i"),ItemId);
		return;
	}
	
	ADroppedItemActor* NewItem = GetWorld()->SpawnActorDeferred<ADroppedItemActor>(ADroppedItemActor::StaticClass(),SpawnLocation,nullptr,nullptr,ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
	NewItem->SetActorData(SpawnedItemData);
	NewItem->SetStackSize(ItemQuantity);
	NewItem->FinishSpawning(SpawnLocation);
}

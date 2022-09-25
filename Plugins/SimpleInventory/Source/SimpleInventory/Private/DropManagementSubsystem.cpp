// Fill out your copyright notice in the Description page of Project Settings.


#include "DropManagementSubsystem.h"


UDropManagementSubsystem::UDropManagementSubsystem()
{
	const FSoftObjectPath MyAssetPath(TEXT("/SimpleInventory/Items/MainDatabase.MainDatabase"));
	UObject* MyAsset= MyAssetPath.TryLoad();
	MainDatabase = Cast<UItemDatabase>(MyAsset);
}

void UDropManagementSubsystem::SpawnDrop(int ItemId, int ItemQuantity, FTransform SpawnLocation)
{
	FItemData ItemToSpawn;
	if(MainDatabase==nullptr)
	{
		UE_LOG(LogTemp,Warning,TEXT("Failed to load item database"))
		return;
	}
	if(!MainDatabase->GetItemDataById(ItemId, ItemToSpawn))
	{
		UE_LOG(LogTemp,Warning,TEXT("Attempt to spawn invalid item, check requested Id"))
		return;
	}
	
	GetWorld()->SpawnActor<AActor>(ItemToSpawn.ItemActorClass,SpawnLocation,FActorSpawnParameters());
}

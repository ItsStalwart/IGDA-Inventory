// Copyright Epic Games, Inc. All Rights Reserved.

#include "SimpleInventory.h"

#define LOCTEXT_NAMESPACE "FSimpleInventoryModule"

void FSimpleInventoryModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-modul
	const FSoftObjectPath DatabasePath(TEXT("/SimpleInventory/Items/DroppedItemData/DA_ItemDatabase"));
	UObject* DatabaseObject = DatabasePath.TryLoad();
	DefaultDatabase = Cast<UItemDatabase>(DatabaseObject);
	if(!IsValid(DefaultDatabase))
	{
		UE_LOG(LogTemp, Warning, TEXT("Database asset not found!"))
	}
}

void FSimpleInventoryModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSimpleInventoryModule, SimpleInventory)
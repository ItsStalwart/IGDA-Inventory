// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ItemDatabase.h"
#include "DroppedItemActor.h"
#include "Modules/ModuleManager.h"



class FSimpleInventoryModule : public IModuleInterface
{
	inline static UItemDatabase* DefaultDatabase {nullptr};
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	static UItemDatabase* GetDefaultDatabase() {return DefaultDatabase;};
};

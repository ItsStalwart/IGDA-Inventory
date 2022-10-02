// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "InventorySlotData.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "InventorySlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLEINVENTORY_API UInventorySlotWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

	UPROPERTY()
	UInventorySlotData* SlotData {nullptr};

	UPROPERTY(meta=(BindWidget))
	UImage* Icon {nullptr};

	UPROPERTY(meta=(BindWidget))
	UTextBlock* Count {nullptr};

public:

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
};

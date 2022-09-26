// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemData.generated.h"
/**
 * 
 */

USTRUCT(BlueprintType)
struct SIMPLEINVENTORY_API FItemData
{
	GENERATED_USTRUCT_BODY()
public:
	FItemData();
	~FItemData();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int ItemId {0};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UTexture2D> ItemThumbnail{ nullptr };
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UClass* ItemActorClass {nullptr};
};

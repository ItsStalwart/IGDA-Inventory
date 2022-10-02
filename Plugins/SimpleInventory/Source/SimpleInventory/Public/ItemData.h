// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemData.generated.h"
/**
 * 
 */
UENUM(BlueprintType)
enum EItemRarity
{
	Trash,
	Common,
	Uncommon,
	Rare,
	Mythic,
	Legendary
};

UCLASS(BlueprintType)
class SIMPLEINVENTORY_API UItemData : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int ItemId {0};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* ItemThumbnail{ nullptr };
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TEnumAsByte<EItemRarity> ItemRarity;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UStaticMesh* DroppedItemMesh{ nullptr };
	
};

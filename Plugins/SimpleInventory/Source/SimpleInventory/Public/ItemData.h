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

UENUM(BlueprintType)
enum EItemType
{
	Consumable,
	Equipment,
	Key
};

UCLASS(BlueprintType)
class SIMPLEINVENTORY_API UItemData : public UDataAsset
{
	GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere,BlueprintReadWrite)
    FText ItemName;
    UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FText ItemDescription;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<FName> AllowedContextActions {FName("Discard")};
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int ItemId {0};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* ItemThumbnail{ nullptr };
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TEnumAsByte<EItemRarity> ItemRarity {EItemRarity::Common};
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UStaticMesh* DroppedItemMesh{ nullptr };


	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	 
};

inline void UItemData::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) 
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	if(PropertyChangedEvent.GetPropertyName() == GET_MEMBER_NAME_CHECKED(UItemData, AllowedContextActions))
	{
		AllowedContextActions.Remove(FName("Discard"));
		AllowedContextActions.EmplaceAt(AllowedContextActions.Num(),FName("Discard"));
	}
}

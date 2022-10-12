// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IDetailTreeNode.h"
#include "Engine/DataAsset.h"
#include "LootTable.generated.h"


USTRUCT(BlueprintType)
struct FLootTableElement
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, meta=(DisplayName="Id", ToolTip="The Id of the item to be dropped."))
	int ElementId {0};
	UPROPERTY(EditAnywhere,meta=(DisplayName="Drop Chance",ToolTip="The percentage chance that this item will be dropped.",Units="Percent", ClampMin="0.0",ClampMax="100.0", UIMin = "0.0", UIMax = "100.0"))
	float ElementDropChance{100.0f};

	bool operator < (const FLootTableElement Element) const
	{
		return this->ElementDropChance < Element.ElementDropChance;
	}
};
/**
 * Use this class to define the possible drops from a DropTableComponent.
 * If AutoSort is set to true, the item drops will automatically sort themselves from lowest to highest drop chance.
 * Having this on will ensure all items in the table will be checked when generating a random drop.
 * If you prefer to leave this option disabled, be aware that the list order is important and items can be made unattainable in this manner.
 */
UCLASS()
class SIMPLEINVENTORY_API ULootTable final : public UDataAsset
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta=(DisplayName="Sort List Automatically?", ToolTip="While this is set to true, the Drop Chances list will automatically sort from lowest to highest when a drop chance is set or a new item is added. Toggling this will NOT cause a sort immediately."))
	bool AutoSort {false};
	UPROPERTY(EditAnywhere, meta=(DisplayName="Drop Chance List", ToolTip="A list of Item Id's associated with a drop chance. It is recommended that the higher the drop chance items be last in the list."))
	TArray<FLootTableElement> ItemDropChances{ };
public:
	UFUNCTION(BlueprintCallable)
	TArray<FLootTableElement> GetItemDropChances(){ return ItemDropChances;};
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
};

inline void ULootTable::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	if(AutoSort && (PropertyChangedEvent.GetPropertyName() == GET_MEMBER_NAME_CHECKED(ULootTable, ItemDropChances) || PropertyChangedEvent.GetPropertyName() == GET_MEMBER_NAME_CHECKED(FLootTableElement, ElementDropChance)))
	{
		ItemDropChances.Sort();
	}
}

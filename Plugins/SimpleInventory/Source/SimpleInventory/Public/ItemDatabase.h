// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemData.h"
#include "Components/PropertyViewBase.h"
#include "Engine/DataAsset.h"
#include "ItemDatabase.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class SIMPLEINVENTORY_API UItemDatabase final : public UDataAsset
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere)
	TArray<UItemData*> Database {};

public:
	UFUNCTION(BlueprintCallable)
	TArray<UItemData*> GetFullDatabase();

	UFUNCTION(BlueprintCallable)
	UItemData* GetItemDataById(const int Id);

	UFUNCTION(BlueprintCallable)
	void ClearDatabase();

	UFUNCTION(BlueprintCallable)
	void InsertItem(UItemData* InItem);

	UFUNCTION(BlueprintCallable)
	bool IsDatabaseValid();
	
};

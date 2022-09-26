// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemData.h"
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
	TArray<FItemData> Database {};

public:
	UFUNCTION(BlueprintCallable)
	void GetFullDatabase(TArray<FItemData> &FullData);

	UFUNCTION(BlueprintCallable)
	bool GetItemDataById(const int Id, FItemData& FoundData);
	
};

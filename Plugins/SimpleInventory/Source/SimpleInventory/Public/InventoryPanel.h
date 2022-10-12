// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryComponent.h"
#include "Components/TileView.h"
#include "InventoryPanel.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLEINVENTORY_API UInventoryPanel : public UTileView
{
	GENERATED_BODY()
	virtual FSimpleListItemEvent& OnItemClicked() const override;
	UPROPERTY()
	UInventoryComponent* OwnerInventory;
	UFUNCTION()
	void RefreshView(TArray<int> NewContents, TArray<int> NewCounts);
	TArray<class UInventorySlotData*> ConstructItemList(const TArray<int> NewContents, const TArray<int> NewCounts) const;
	void Deregister(AActor* Owner);
	//UListViewBase::FOnListEntryGenerated RegisterDrag();
	//void DeregisterDrag(UUserWidget& Widget);
public:
	UFUNCTION(BlueprintCallable)
	UInventoryComponent* GetOwnerInventory(){ return OwnerInventory;};
	UFUNCTION(BlueprintCallable)
	void OnSlotDragged(int DraggedIndex);
	void SetCorrespondingInventory(UInventoryComponent* InInventory, AActor* OwningPawn);
	
};

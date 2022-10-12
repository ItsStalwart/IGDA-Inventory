// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DropManagementSubsystem.h"
#include "Components/ActorComponent.h"
#include "Containers/Map.h"
#include "InventoryComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogInventoryComponent, Log, All)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FInventoryContentChanged,TArray<int>,NewContent,TArray<int>,NewCount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FItemAddFailed, int, FailedId, int, FailedCount, FString, FailureReason, FTransform, FailedAt);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SIMPLEINVENTORY_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	
	
	FInventoryContentChanged& OnInventoryContentChanged(){return InventoryContentChangedEvent;};
	FItemAddFailed& OnItemAddFailed(){return ItemAddFailedEvent;};
	
	UFUNCTION(BlueprintCallable)
	void InitializeInventory(const int InventorySize = 0);
	UFUNCTION(BlueprintCallable)
	void AddItem(const int ItemId,const  int Quantity); 
	UFUNCTION(BlueprintCallable)
	void RemoveItem(const int ItemId,const int Quantity);
	UFUNCTION(BlueprintCallable)
	void HandleMoveItem(const int OriginalSlot, const int TargetSlot);
	UFUNCTION(BlueprintCallable)
	void LoadInventoryContents(const TArray<int> InInventoryContents,const TArray<int> InInventoryQuantities);
	UFUNCTION(BlueprintCallable)
	void EmptyInventory(TArray<int> &OutInventoryContents,TArray<int> &OutInventoryQuantities);
	UFUNCTION(BlueprintCallable)
	void DropItemFromSlot(const int SlotIndex, const bool bShouldDrop = true);
	UFUNCTION(BlueprintCallable)
	void GetContentsFromSlot(const int SlotIndex, int& ContainedId, int& ContainedQuantity);

private:
	void MoveItem(const int OriginalSlot, const int TargetSlot);
	void StackItem(const int OriginalSlot, const int TargetSlot);
	UDropManagementSubsystem* DropManager {nullptr};
	int InventoryCapacity{0}; //we will use capacity 0 as infinite
	UPROPERTY(BlueprintAssignable)
	FInventoryContentChanged InventoryContentChangedEvent;
	UPROPERTY(BlueprintAssignable)
	FItemAddFailed ItemAddFailedEvent;
public:
	void SetInventoryCapacity(const int InInventoryCapacity)
	{
		this->InventoryCapacity = InInventoryCapacity;
	}
	UFUNCTION(BlueprintCallable)
	int GetInventoryCapacity() const
	{
		return InventoryCapacity;
	}

	UFUNCTION(BlueprintCallable)
	void GetContents(TArray<int>&Contents,TArray<int>&Counts) const
	{
		Contents = InventoryContents;
		Counts = ContentQuantities;
	}

private:
	TArray<int> InventoryContents;
	TArray<int> ContentQuantities; //using two arrays instead of a map to allow multiple slots to hold the same item

	bool IsInventoryFull() const;
	void CleanEmptySlots();
	UFUNCTION()
	void PickUpItem(AActor* Owner, AActor* ItemToPickUp);
};

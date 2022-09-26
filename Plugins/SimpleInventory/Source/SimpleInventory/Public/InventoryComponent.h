// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Containers/Map.h"
#include "InventoryComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FInventoryContentChanged,TArray<int>,NewContent,TArray<int>,NewCount);
DECLARE_EVENT_ThreeParams(UInventoryComponent,FItemAddFailed, int, int, FString)


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
	void MoveItem(const int OriginalSlot, const int TargetSlot);
	UFUNCTION(BlueprintCallable)
	void LoadInventoryContents(const TArray<int> InInventoryContents,const TArray<int> InInventoryQuantities);
	UFUNCTION(BlueprintCallable)
	void EmptyInventory(TArray<int> &OutInventoryContents,TArray<int> &OutInventoryQuantities);

private:
	int InventoryCapacity{0}; //we will use capacity 0 as infinite
	UPROPERTY(BlueprintAssignable)
	FInventoryContentChanged InventoryContentChangedEvent;
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
	TArray<int> ContentQuantities; //using two arrays instead of a map to facilitate splitting and moving stacks

	bool IsInventoryFull() const;
	void CleanEmptySlots();
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryContextCommand.generated.h"

/**
 * 
 */
UCLASS(Blueprintable,BlueprintType)
class SIMPLEINVENTORY_API UInventoryContextCommand : public UObject
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
	virtual void Execute() PURE_VIRTUAL(UContextCommand::Execute,; );

	UFUNCTION(BlueprintCallable)
	virtual void Undo() PURE_VIRTUAL(UContextCommand::Undo,; );
protected:
	UPROPERTY()
	int TargetedSlot {0};
public:
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	class UInventoryComponent* Container {nullptr};

	UFUNCTION(BlueprintCallable)
	void SetTargetedSlot(const int NewTarget) {TargetedSlot = NewTarget;};
	UFUNCTION(BlueprintCallable)
	int GetTargetedSlot() const {return TargetedSlot;} ;
};

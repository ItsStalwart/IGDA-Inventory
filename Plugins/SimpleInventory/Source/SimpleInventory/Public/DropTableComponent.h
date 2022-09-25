// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DA_LootTable.h"
#include "Components/ActorComponent.h"
#include "DropTableComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FItemDropped,int, DropId, int, DropQuantity,FTransform,DropLocation);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SIMPLEINVENTORY_API UDropTableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDropTableComponent();
	virtual ~UDropTableComponent() override;
	UFUNCTION()
	void DropItems(AActor* Owner); //DropItem function to return the dropped item id and quantities
	virtual void BeginPlay() override;
private:
	FItemDropped ItemDroppedEvent;
	UPROPERTY(EditDefaultsOnly)
	UDA_LootTable* LootTable;
	UPROPERTY(EditAnywhere)
	int MaxNumberOfDrops{1};
	UPROPERTY(EditAnywhere)
	int MinNumberOfDrops{1};

	int GetRandomDrop() const;
public:
	FItemDropped& GetItemDroppedEvent(){return ItemDroppedEvent;};
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DropManagementSubsystem.h"
#include "LootTable.h"
#include "Components/ActorComponent.h"
#include "DropTableComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SIMPLEINVENTORY_API UDropTableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDropTableComponent();
	UFUNCTION()
	void DropItems(AActor* Owner); //DropItem function to return the dropped item id and quantities
	virtual void BeginPlay() override;
private:
	UDropManagementSubsystem* DropManager { nullptr };
	UPROPERTY(EditDefaultsOnly)
	ULootTable* LootTable;
	UPROPERTY(EditAnywhere)
	int MaxNumberOfDrops{1};
	UPROPERTY(EditAnywhere)
	int MinNumberOfDrops{1};

	int GetRandomDrop() const;
};

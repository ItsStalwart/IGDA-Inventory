// Fill out your copyright notice in the Description page of Project Settings.


#include "DropTableComponent.h"
#include "Math/UnrealMathUtility.h"
#include "Windows/WindowsApplication.h"

// Sets default values for this component's properties
UDropTableComponent::UDropTableComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	if(MaxNumberOfDrops<MinNumberOfDrops)
	{
		MaxNumberOfDrops = MinNumberOfDrops;
	}
}

void UDropTableComponent::DropItems(AActor* Owner)
{
	TArray<int> DroppedItems;
	TArray<int> DroppedQuantities;
	const int NumberOfDrops = FMath::RandRange(MinNumberOfDrops,MaxNumberOfDrops);
	for (int i=0;i<NumberOfDrops;i++)
	{
		const int DroppedId = GetRandomDrop();
		const int FoundPosition = DroppedItems.Find(DroppedId);
		if(FoundPosition >= 0)
		{
			DroppedQuantities[FoundPosition]++;
			continue;
		}
		DroppedQuantities.EmplaceAt(DroppedItems.Emplace(DroppedId),1);
	}
	for (int i=0;i<DroppedItems.Num();i++)
	{
		DropManager->SpawnDrop(DroppedItems[i],DroppedQuantities[i],Owner->GetActorTransform());
	}
}

void UDropTableComponent::BeginPlay()
{
	Super::BeginPlay();
	if(GetOwner() == nullptr)
	{
		return;
	}
	GetOwner()->OnDestroyed.AddDynamic(this, &UDropTableComponent::DropItems);
	DropManager = GetWorld()->GetGameInstance()->GetSubsystem<UDropManagementSubsystem>();
}

int UDropTableComponent::GetRandomDrop() const
{
	const float DropRoll = FMath::RandRange(.0f,100.f);
	for (const auto [ElementId, ElementDropChance] : LootTable->GetItemDropChances())
	{
		if (DropRoll <= ElementDropChance)
		{
			return ElementId;
		}
	}
	return 0;
}


// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemData.h"
#include "GameFramework/Actor.h"
#include "DroppedItemActor.generated.h"

UCLASS()
class SIMPLEINVENTORY_API ADroppedItemActor : public AActor
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	UItemData* ActorData {nullptr};
	int StackSize {1};
	UPROPERTY(Category=Mesh, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> Mesh;
	
public:	
	// Sets default values for this actor's properties
	ADroppedItemActor();
	void SetActorData(UItemData* InData);
	int GetAssociatedId() const {return ActorData->ItemId; };
	void SetStackSize(const int InSize) {StackSize = InSize;};
	int GetStackSize() const {return StackSize;};
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void OnActorDataChanged() const;

};

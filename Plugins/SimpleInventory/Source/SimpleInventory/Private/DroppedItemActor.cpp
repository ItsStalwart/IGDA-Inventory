// Fill out your copyright notice in the Description page of Project Settings.


#include "DroppedItemActor.h"

// Sets default values
ADroppedItemActor::ADroppedItemActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateOptionalDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	if (Mesh)
	{
		Mesh->AlwaysLoadOnClient = true;
		Mesh->AlwaysLoadOnServer = true;
		Mesh->bOwnerNoSee = false;
		Mesh->bCastDynamicShadow = true;
		Mesh->bAffectDynamicIndirectLighting = true;
		Mesh->PrimaryComponentTick.TickGroup = TG_PrePhysics;
		Mesh->SetCollisionProfileName(TEXT("Trigger"), true);
		Mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		Mesh->SetGenerateOverlapEvents(true);
		Mesh->SetCanEverAffectNavigation(false);
	}
}

void ADroppedItemActor::SetActorData(UItemData* InData)
{
	this->ActorData = InData;
	OnActorDataChanged();
}

// Called when the game starts or when spawned
void ADroppedItemActor::BeginPlay()
{
	Super::BeginPlay();
	if(!IsValid(this->ActorData))
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawned item without data!"))
		return;
	}
}

void ADroppedItemActor::OnActorDataChanged() const
{
	Mesh->SetStaticMesh(ActorData->DroppedItemMesh);
}


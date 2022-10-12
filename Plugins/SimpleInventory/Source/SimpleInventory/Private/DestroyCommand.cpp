// Fill out your copyright notice in the Description page of Project Settings.


#include "DestroyCommand.h"
#include "InventoryComponent.h"

void UDestroyCommand::Execute()
{
	Container->GetContentsFromSlot(TargetedSlot, DestroyedId,DestroyedQuantity);
	Container->DropItemFromSlot(TargetedSlot, false);
}

void UDestroyCommand::Undo()
{
	Container->AddItem(DestroyedId,DestroyedQuantity);
}

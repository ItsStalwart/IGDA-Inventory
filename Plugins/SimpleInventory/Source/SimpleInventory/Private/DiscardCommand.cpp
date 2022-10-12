// Fill out your copyright notice in the Description page of Project Settings.


#include "DiscardCommand.h"
#include "InventoryComponent.h"

void UDiscardCommand::Execute()
{
	Container->GetContentsFromSlot(TargetedSlot, DiscardedId,DiscardedQuantity);
	Container->DropItemFromSlot(TargetedSlot);
}

void UDiscardCommand::Undo()
{
	Container->AddItem(DiscardedId,DiscardedQuantity);
}

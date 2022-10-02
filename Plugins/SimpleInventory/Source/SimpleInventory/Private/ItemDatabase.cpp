// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemDatabase.h"

TArray<UItemData*> UItemDatabase::GetFullDatabase()
{
	return this->Database;
}

UItemData* UItemDatabase::GetItemDataById(const int Id)
{
	if(Database.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("Database is empty!))"));
		return nullptr;
	}
	for (int i=0;i<Database.Num();i++)
	{
		if(Database[i]->ItemId == Id)
		{
			return Database[i];
		}
	}
	return nullptr;
}

void UItemDatabase::ClearDatabase()
{
	Database.Empty();
}

void UItemDatabase::InsertItem(UItemData* InItem)
{
	Database.Emplace(InItem);
}

bool UItemDatabase::IsDatabaseValid()
{
	for (int i=0;i<Database.Num()-1;i++)
	{
		for (int j=i+1;j<Database.Num();j++)
		{
			if(Database[i]->ItemId == Database[j]->ItemId)
			{
				UE_LOG(LogTemp,Warning,TEXT("Duplicate ItemIds in database! Entries %i and %i have the same ItemId!"),i,j);
				return false;
			}
		}
	}
	return true;
}

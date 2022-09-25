// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemDatabase.h"

void UItemDatabase::GetFullDatabase(TArray<FItemData>& FullData)
{
	FullData = this->Database;
}

bool UItemDatabase::GetItemDataById(const int Id, FItemData& FoundData)
{
	for (int i=0;i<Database.Num();i++)
	{
		if(Database[i].ItemId == Id)
		{
			FoundData = Database[i];
			return true;
		}
	}
	return false;
}

#include "SpaceShooter.h"
#include "SpaceGameInstance.h"
#include "Items/Item.h"
#include "Items/Lootable.h"
#include "Items/Equipable.h"
#include "ItemGlobals.h"

USpaceGameInstance::USpaceGameInstance(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	MasterItemList = GetDefault<UItemGlobals>()->ItemList;

}

TArray<FMetaItem> USpaceGameInstance::GetItemList() const
{
	return MasterItemList;

}

FItem USpaceGameInstance::GetItem(FMetaItem MetaItem)
{
	FItem out;
	out.Name = "None";

	if (MetaItem.LootClass)
	{
		out = MetaItem.LootClass->GetDefaultObject<ALootable>()->SafeGetItem();
		out.id = MetaItem.id;
		out.Name = MetaItem.Name;
		out.Description = MetaItem.Description;
		out.Quantity = MetaItem.Quantity;
		out.Weight = MetaItem.Weight;
		out.Value = MetaItem.Value;
		


	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 11, FColor::Red, "Item is gonna none, from the master list!");
	}

	return out;
}

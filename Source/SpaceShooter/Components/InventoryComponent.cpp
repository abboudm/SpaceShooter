// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceShooter.h"
#include "InventoryComponent.h"
#include "Items/Item.h"
#include "Items/Equipable.h"
#include "Items/Weapons/InstantHitWeapon.h"
#include "Components/ClimbingPawnMovementComponent.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent() : Super()
{
	Gold = 0;
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	//bWantsBeginPlay = true;
	//PrimaryComponentTick.bCanEverTick = true;

}



// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	//FString Message = "Hellow Orld!";
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, Message);
}


// Called every frame
void UInventoryComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	//Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, "Tickity tickidy tickaroo");

	// ...
}
TArray<FItem> UInventoryComponent::GetInventory()
{
	return ItemInventory;
}

TArray<FString> UInventoryComponent::GetNameList()
{
	TArray<FString> outArray;

	if (ItemInventory.Num() <= 0)
	{
		Lib::Msg("Got No items in inventory?");
	}
	else
	{
		FItem* inventorydata = ItemInventory.GetData();
		for (int i = 0; i < ItemInventory.Num(); i++)
		{
			outArray.Emplace(inventorydata[i].Name.ToString());
		}
	
	
	}
	return outArray;


}



// This only checks based on name, so if BattleRifle gets changed to Battle Rifle, itll be two items
int UInventoryComponent::HasItemAlready(FItem item)
{
	int out = -1;
	for (int i = 0; i < ItemInventory.Num(); i++)
	{
		if (ItemInventory.GetData()[i].Name == item.Name)
		{
			//theres a match, so returning true!
			out = i;
			break;
		}
	}

	return out;

}


int UInventoryComponent::GetGold()
{
	return Gold;
}
void UInventoryComponent::AddItemToInventory(FItem item)
{
	if (item.Name == "null")
	{
		//we dont want a "null" item! we want a remove function!
		return;
	}

	if (item.Name == "Gold")
	{
		//Catch loot named Gold, and add to the gold ammount!
		//Just for fun, set Value of Gold to BLANK, then set the gold item to quantity * x !
		Gold += item.Quantity * item.Value;
		return;
	}

	int query = HasItemAlready(item);
	switch (item.ItemType)
	{
		case EItemType::Equipable:
		
			if (query != -1)
			{
				//ItemInventory.GetData()[query].Increment();
				//We dont want 2 of the same equip item!
				break;
			}
			else
			{
				ItemInventory.Emplace(item);
				break;
			}
			break;
		
		case EItemType::Loot:
			//
			if (query != -1)
			{
				ItemInventory.GetData()[query].Increment();
				break;
			}
			else
			{
				ItemInventory.Emplace(item);
				break;
			}
			break;

		case EItemType::KeyItem:
			break;
		case EItemType::Upgrade:
			break;

		default:
			break;
	}



	/*
	//item.id = ItemInventory.Num();
	//ItemInventory.Emplace(item);
	if (ItemInventory.Num() <= 0)
	{
		item.id = 1;
		ItemInventory.Emplace(item);
	}
	else
	{
		for (int i = 0; i < ItemInventory.Num(); i++)
		{
			if (ItemInventory.GetData()[i].Name == item.Name)
			{
				//theres a match, so ignoring - updating ammo count would go here i think?
				return;
			}
		}
		item.id = ItemInventory.Num() + 1;
		ItemInventory.Emplace(item);
	}

	*/
	/*
	IntArray.Init(10,5);
	intarray == [10,10,10,10,10];

	intarray.Add( 5 );
	StringArray.Emplace( TEXT("HI"));
	add/emplace, adds easier to read, but emplace doesn't make a temporary buffer to copy data

	.Add
	.Emplace
	.Append
	.Insert(element,index)
	
	*/
}

FItem UInventoryComponent::GetItem(int index)
{
	return ItemInventory.Pop();
}

void UInventoryComponent::RemoveItemFromInventory(FItem item)
{

	int query = HasItemAlready(item);
	if (query != -1)
	{
		ItemInventory.GetData()[query].Decrement();
		if (ItemInventory.GetData()[query].Quantity <= 0)
		{
			RemoveItemFromInventory(query);
		}
	}

	//item.id = ItemInventory.Num() + 1;
	//ItemInventory.Emplace(item);
	//ItemInventory.RemoveAt(item.id-1);
	//ItemInventory.Remove(item);
}
void UInventoryComponent::RemoveItemFromInventory(int index)
{
	ItemInventory.RemoveAt(index);	
}
/*
*/


AInstantHitWeapon* UInventoryComponent::CreateInstantHitWeaponFromItem(FItem weaponitem)
{
	AInstantHitWeapon* NewWeapon = nullptr;
	return NewWeapon;
}

FItem UInventoryComponent::CreateItemFromInstantHit(AInstantHitWeapon* weapon)
{
	FItem newitem;
	return newitem;

}
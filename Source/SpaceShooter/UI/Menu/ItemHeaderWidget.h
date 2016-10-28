
#pragma once

#include "SlateBasics.h"
#include "Items/Item.h"



// Lays out and controls the Main Menu UI for our tutorial.
class SPACESHOOTER_API SItemHeaderWidget : public SCompoundWidget
{

public:
	SLATE_BEGIN_ARGS(SItemHeaderWidget)
	{}
	SLATE_ARGUMENT(EInventoryCategory, Category)
	SLATE_END_ARGS()


	EInventoryCategory Category;
	/* 
	All
		Name(Quant)		itemtype	value	weight
	Weapons
		Name		WeaponType AmmoType Clip/MaxClip	Damage
	Loot
		Name(Quant)		LootType	Value Weight 
	


	
};
*/
	DECLARE_DELEGATE_OneParam(FOnSort,EItemSortType)
	FOnSort OnSort;

	DECLARE_DELEGATE(FOnRebuildParent)
	FOnRebuildParent OnRebuildParent;


	DECLARE_DELEGATE(FOnSortName);

	DECLARE_DELEGATE(FOnSortQuantity);

	DECLARE_DELEGATE(FOnSortItemType);

	DECLARE_DELEGATE(FOnSortValue);
	DECLARE_DELEGATE(FOnSortWeight);
	DECLARE_DELEGATE(FOnSortWeaponType);
	DECLARE_DELEGATE(FOnSortAmmoType);
	DECLARE_DELEGATE(FOnSortClip);
	DECLARE_DELEGATE(FOnSortClipMax);
	DECLARE_DELEGATE(FOnSortDamage);
	DECLARE_DELEGATE(FOnSortLootType);
	FOnSortName OnSortName;
	FOnSortQuantity OnSortQuantity;
	FOnSortItemType OnSortItemType;
	FOnSortValue OnSortValue;
	FOnSortWeight OnSortWeight;
	FOnSortWeaponType OnSortWeaponType;
	FOnSortAmmoType OnSortAmmoType;
	FOnSortClip OnSortClip;
	FOnSortClipMax OnSortClipMax;
	FOnSortDamage OnSortDamage;
	FOnSortLootType OnSortLootType;

	TAttribute<FText> Name;
	TAttribute<FText> Value;
	TAttribute<FText> Weight;
	TAttribute<FText> WeaponType;
	TAttribute<FText> AmmoType;
	TAttribute<FText> Clip;
	TAttribute<FText> ClipMax;
	TAttribute<FText> Damage;
	TAttribute<FText> LootType;
	TAttribute<FText> Quantity;
	TAttribute<FText> ItemType;

	FText GetName() const;
	FText GetValue() const;
	FText GetWeight() const;
	FText GetWeaponType() const;
	FText GetAmmoType() const;
	FText GetClip() const;
	FText GetClipMax() const;
	FText GetDamage() const;
	FText GetLootType() const;
	FText GetQuantity() const;
	FText GetItemType() const;

	FReply SortName();
	FReply SortValue();
	FReply SortWeight();
	FReply SortWeaponType();
	FReply SortAmmoType();
	FReply SortClip();
	FReply SortClipMax();
	FReply SortDamage();
	FReply SortLootType();
	FReply SortQuantity();
	FReply SortItemType();



	void Construct(const FArguments& args);
	const struct FGlobalStyle* MenuStyle;
	
	//FItem Item;
	/*
	TAttribute<FText> Name;
	TAttribute<FText> Value;
	TAttribute<FText> Weight;

	FText GetName() const;
	FText GetValue() const;
	FText GetWeight() const;
	*/


	//FReply ItemClicked();


};
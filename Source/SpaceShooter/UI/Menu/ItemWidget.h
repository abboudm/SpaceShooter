
#pragma once

#include "SlateBasics.h"
#include "Items/Item.h"



// Lays out and controls the Main Menu UI for our tutorial.
class SPACESHOOTER_API SItemWidget : public SCompoundWidget
{

public:
	SLATE_BEGIN_ARGS(SItemWidget)
	{}
	SLATE_ARGUMENT(FItem, Item)
	SLATE_ARGUMENT(EInventoryCategory, Category)
	SLATE_END_ARGS()

	EInventoryCategory Category;
	FItem Item;

	void Construct(const FArguments& args);
	const struct FGlobalStyle* MenuStyle;
	TSharedPtr<class SButton> Button;

/*
	All
		Name(Quant)		itemtype	value	weight
		Weapons
		Name		WeaponType AmmoType Clip / MaxClip	Damage
		Loot
		Name(Quant)		LootType	Value Weight
*/




	TAttribute<FText> Name;
	TAttribute<FText> Value;
	TAttribute<FText> Weight;

	TAttribute<FText> ItemType;
	TAttribute<FText> WeaponType;
	TAttribute<FText> AmmoType;
	TAttribute<FText> Clip;
	TAttribute<FText> Damage;
	TAttribute<FText> LootType;

	FText GetName() const;
	FText GetValue() const;
	FText GetWeight() const;

	FText GetItemType	() const;
	FText GetWeaponType	() const;
	FText GetAmmoType	() const;
	FText GetClip		() const;
	FText GetDamage		() const;
	FText GetLootType	() const;

	DECLARE_DELEGATE_OneParam(FUseItem, FItem);
	FUseItem UseItem;
	/*
	DECLARE_DELEGATE(FOnUseItem);
	FOnUseItem UseItem;
	*/

	FReply ItemClicked();


};
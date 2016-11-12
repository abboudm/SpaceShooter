
#include "SpaceShooter.h"
#include "ItemWidget.h"
#include "UI/Styles/GlobalMenuStyle.h"
#include "UI/Styles/MenuStyles.h"
#include "Engine.h"
#include "Items/Item.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SItemWidget::Construct(const FArguments& args)
{
	Item = args._Item;
	Category = args._Category;
	MenuStyle = &FMenuStyles::Get().GetWidgetStyle<FGlobalStyle>("Global");
	Name.Bind(this, &SItemWidget::GetName);
	Value.Bind(this, &SItemWidget::GetValue);
	Weight.Bind(this, &SItemWidget::GetWeight);
	ItemType.Bind(this,&SItemWidget::GetItemType);
	WeaponType.Bind(this, &SItemWidget::GetWeaponType);
	AmmoType.Bind(this, &SItemWidget::GetAmmoType);
	Clip.Bind(this, &SItemWidget::GetClip);
	Damage.Bind(this, &SItemWidget::GetDamage);
	LootType.Bind(this, &SItemWidget::GetLootType);


	TSharedPtr<class SHorizontalBox> HBox;

	ChildSlot
		.Padding(0.0,0.0,0.0,0.0)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
	[
		SNew(SOverlay)
		+ SOverlay::Slot()
		.VAlign(VAlign_Fill)
		.HAlign(HAlign_Fill)
		[
			SAssignNew(HBox,SHorizontalBox)
		]

		+ SOverlay::Slot()
			.VAlign(VAlign_Fill)
			.HAlign(HAlign_Fill)
			[
				SAssignNew(Button, SButton)
				.ButtonStyle(&MenuStyle->MenuButtonStyle)
				//.TextStyle(&MenuStyle->MenuButtonTextStyle)
				//.Text(FText::FromString("Play Game!"))
				.OnClicked(this, &SItemWidget::ItemClicked)
			]


		
	];

	switch (Category)
	{
	case EInventoryCategory::All:
		HBox->AddSlot()
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Fill)
			.AutoWidth()
			[
				SNew(STextBlock)
				.TextStyle(&MenuStyle->HUDTextStyle)
				.Text(Name)
				.MinDesiredWidth(250)
			];
		HBox->AddSlot()
			.Padding(0, 0, 0, 0)
			.HAlign(HAlign_Right)
			.VAlign(VAlign_Fill)
			[
				SNew(STextBlock)
				.TextStyle(&MenuStyle->HUDTextStyle)
				.Text(ItemType)
				.MinDesiredWidth(80)
			];
		HBox->AddSlot()
			.Padding(0, 0, 0, 0)
			.HAlign(HAlign_Right)
			.VAlign(VAlign_Fill)
			[
				SNew(STextBlock)
				.TextStyle(&MenuStyle->HUDTextStyle)
				.Text(Value)
				.MinDesiredWidth(50)
			];
		HBox->AddSlot()
			.HAlign(HAlign_Right)
			.VAlign(VAlign_Fill)
			[
				SNew(STextBlock)
				.TextStyle(&MenuStyle->HUDTextStyle)
				.Text(Weight)
				.MinDesiredWidth(50)
			];
		break;
	case EInventoryCategory::Weapons:		//		Name		WeaponType AmmoType Clip / MaxClip	Damage
		HBox->AddSlot()
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Fill)
			.AutoWidth()
			[
				SNew(STextBlock)
				.TextStyle(&MenuStyle->HUDTextStyle)
				.Text(Name)
			.MinDesiredWidth(250)
			];


		HBox->AddSlot()
			.Padding(0, 0, 0, 0)
			.HAlign(HAlign_Right)
			.VAlign(VAlign_Fill)
			[
				SNew(STextBlock)
				.TextStyle(&MenuStyle->HUDTextStyle)
				.Text(WeaponType)
				.MinDesiredWidth(90)
			];
		HBox->AddSlot()
			.Padding(0, 0, 0, 0)
			.HAlign(HAlign_Right)
			.VAlign(VAlign_Fill)
			[
				SNew(STextBlock)
				.TextStyle(&MenuStyle->HUDTextStyle)
			.Text(AmmoType)
			.MinDesiredWidth(90)
			];
		HBox->AddSlot()
			.HAlign(HAlign_Right)
			.VAlign(VAlign_Fill)
			[
				SNew(STextBlock)
				.TextStyle(&MenuStyle->HUDTextStyle)
			.Text(Clip)
			.MinDesiredWidth(50)
			];
		HBox->AddSlot()
			.HAlign(HAlign_Right)
			.VAlign(VAlign_Fill)
			[
				SNew(STextBlock)
				.TextStyle(&MenuStyle->HUDTextStyle)
			.Text(Damage)
			.MinDesiredWidth(50)
			];
		break;
	case EInventoryCategory::Loot:		//Name(Quant)		LootType	Value Weight
		HBox->AddSlot()
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Fill)
			.AutoWidth()
			[
				SNew(STextBlock)
				.TextStyle(&MenuStyle->HUDTextStyle)
			.Text(Name)
			.MinDesiredWidth(350)
			];


		HBox->AddSlot()
			.Padding(0, 0, 0, 0)
			.HAlign(HAlign_Right)
			.VAlign(VAlign_Fill)
			[
				SNew(STextBlock)
				.TextStyle(&MenuStyle->HUDTextStyle)
			.Text(LootType)
			.MinDesiredWidth(80)
			];
		HBox->AddSlot()
			.Padding(0, 0, 0, 0)
			.HAlign(HAlign_Right)
			.VAlign(VAlign_Fill)
			[
				SNew(STextBlock)
				.TextStyle(&MenuStyle->HUDTextStyle)
			.Text(Value)
			.MinDesiredWidth(50)
			];
		HBox->AddSlot()
			.HAlign(HAlign_Right)
			.VAlign(VAlign_Fill)
			[
				SNew(STextBlock)
				.TextStyle(&MenuStyle->HUDTextStyle)
			.Text(Weight)
			.MinDesiredWidth(50)
			];
		break;
	default:
		break;
	}



	/*  
	*/



	/*
	ChildSlot
	[
		SNew(SOverlay)
		+ SOverlay::Slot()
		.HAlign(HAlign_Right)
		.VAlign(VAlign_Bottom)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			[
				SNew(STextBlock)
				.TextStyle(&MenuStyle->HUDTextStyle)
				.Text(Name)
			]
			+ SVerticalBox::Slot()
			[
				SNew(STextBlock)
				.TextStyle(&MenuStyle->HUDTextStyle)
				.Text(Value)
			]
			+ SVerticalBox::Slot()
			[
				SNew(STextBlock)
				.TextStyle(&MenuStyle->HUDTextStyle)
				.Text(Weight)
			]
		]
	];
	*/
	




}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION




FText SItemWidget::GetName() const
{

	FString out = Item.Name.ToString();

	if (Item.Quantity > 1)
	{
		out.Append("(");
		out.Append(FString::FromInt(Item.Quantity));
		out.Append(")");
	}
	//out.Append("||");
	return FText::FromString(out);
}

FText SItemWidget::GetValue() const
{
	FString out = FString::FromInt(Item.Value);
	//out.Append("||");
	return FText::FromString(out);
}

FText SItemWidget::GetWeight() const
{
	FString out = FString::FromInt(Item.Weight);
	//out.Append("||");
	return FText::FromString(out);
}


FText SItemWidget::GetItemType() const 
{
	FString out = "";
	switch (Item.ItemType)
	{
	case EItemType::Ammo:
		out.Append("Ammo");
		break;
	case EItemType::Equipable:
		out.Append("Equipable");
		break;
	case EItemType::KeyItem:
		out.Append("KeyItem");
		break;
	case EItemType::Loot:
		out.Append("Loot");
		break;
	case EItemType::Upgrade:
		out.Append("Upgrade");
		break;
	default:
		out.Append("NotSet!");
		break;
	}
	//out.Append("||");
	return FText::FromString(out);
}
FText SItemWidget::GetWeaponType() const
{
	FString out = "";
	switch (Item.WeaponType)
	{
	case EWeaponType::Launcher:
		out.Append("Launcher");
		break;
	case EWeaponType::Pistol:
		out.Append("Pistol");
		break;
	case EWeaponType::Melee:
		out.Append("Melee");
		break;
	case EWeaponType::Rifle:
		out.Append("Rifle");
		break;
	case EWeaponType::Sniper:
		out.Append("Sniper");
		break;
	default:
		out.Append("NotSet!");
		break;
	}
	//out.Append("||");
	return FText::FromString(out);
}
FText SItemWidget::GetAmmoType() const
{
	FString out = "";
	switch (Item.AmmoType)
	{
	case EAmmoType::Grenade:
		out.Append("Grenade");
		break;
	case EAmmoType::Launcher:
		out.Append("Launcher");
		break;
	case EAmmoType::Pistol:
		out.Append("Pistol");
		break;
	case EAmmoType::Rifle:
		out.Append("Rifle");
		break;
	case EAmmoType::Rocket:
		out.Append("Rocket");
		break;
	case EAmmoType::Sniper:
		out.Append("Sniper");
		break;

	default:
		out.Append("NotSet!");
		break;
	}
	//out.Append("||");
	return FText::FromString(out);
}
FText SItemWidget::GetClip() const
{
	FString out = FString::FromInt(Item.AmmoInClip);
	out.Append("/");
	out.Append(FString::FromInt(Item.ClipSize));

	//out.Append("||");
	return FText::FromString(out);
}
FText SItemWidget::GetDamage() const
{
	FString out = FString::FromInt(Item.HitDamage);
	//out.Append("||");
	return FText::FromString(out);
}
FText SItemWidget::GetLootType() const
{
	FString out = "";
	switch (Item.LootType)
	{
	case ELootType::Equipable:
		out.Append("Equipable");
		break;
	case ELootType::Craftable:
		out.Append("Craftable");
		break;
	case ELootType::Junk:
		out.Append("Junk");
		break;
	default:
		out.Append("Not Set!");
		break;
	}
	//out.Append("||");
	return FText::FromString(out);
}




FReply SItemWidget::ItemClicked()
{
	UseItem.ExecuteIfBound(Item);
	//UseItem.ExecuteIfBound();
	//OnToggleMenu.ExecuteIfBound();
	return FReply::Handled();
}


#include "SpaceShooter.h"
#include "ItemHeaderWidget.h"
#include "UI/Styles/GlobalMenuStyle.h"
#include "UI/Styles/MenuStyles.h"
#include "Engine.h"
#include "Items/Item.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SItemHeaderWidget::Construct(const FArguments& args)
{

	Category = args._Category;
	MenuStyle = &FMenuStyles::Get().GetWidgetStyle<FGlobalStyle>("Global");

	Name.Bind(this, &SItemHeaderWidget::GetName);
	Value.Bind(this, &SItemHeaderWidget::GetValue			);
	Weight.Bind(this, &SItemHeaderWidget::GetWeight			);
	WeaponType.Bind(this, &SItemHeaderWidget::GetWeaponType);
	AmmoType.Bind(this, &SItemHeaderWidget::GetAmmoType		);
	Clip.Bind(this, &SItemHeaderWidget::GetClip				);
	ClipMax.Bind(this, &SItemHeaderWidget::GetClipMax		);
	Damage.Bind(this, &SItemHeaderWidget::GetDamage			);
	LootType.Bind(this, &SItemHeaderWidget::GetLootType		);
	Quantity.Bind(this, &SItemHeaderWidget::GetQuantity);
	ItemType.Bind(this, &SItemHeaderWidget::GetItemType);
	

	/*
	ChildSlot
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
		.HAlign(HAlign_Left)
		.VAlign(VAlign_Fill)
		.AutoWidth()
		[
			SNew(SOverlay)
			+ SOverlay::Slot()
		[
			SNew(STextBlock)
			.TextStyle(&MenuStyle->HUDTextStyle)
		.Text(Name)
		.MinDesiredWidth(550)
		]
	+ SOverlay::Slot()
		.VAlign(VAlign_Fill)
		.HAlign(HAlign_Fill)
		[
			SNew(SButton)
			.ButtonStyle(&MenuStyle->TabButtonStyle)
		.OnClicked(this, &SItemHeaderWidget::SortName)
		]
		]

	+ SHorizontalBox::Slot()
		.Padding(0, 0, 0, 0)
		.HAlign(HAlign_Right)
		.VAlign(VAlign_Fill)
		[
			SNew(SOverlay)
			+ SOverlay::Slot()
		[
			SNew(STextBlock)
			.TextStyle(&MenuStyle->HUDTextStyle)
		.Text(Value)
		.MinDesiredWidth(30)
		]
	+ SOverlay::Slot()
		.VAlign(VAlign_Fill)
		.HAlign(HAlign_Fill)
		[
			SNew(SButton)
			.ButtonStyle(&MenuStyle->TabButtonStyle)
		.OnClicked(this, &SItemHeaderWidget::SortValue)
		]
		]





	+SHorizontalBox::Slot()
		.HAlign(HAlign_Right)
		.VAlign(VAlign_Fill)
		[
			SNew(SOverlay)
			+ SOverlay::Slot()
		[
			SNew(STextBlock)
			.TextStyle(&MenuStyle->HUDTextStyle)
		.Text(Weight)
		.MinDesiredWidth(30)
		]
	+ SOverlay::Slot()
		.VAlign(VAlign_Fill)
		.HAlign(HAlign_Fill)
		[
			SNew(SButton)
			.ButtonStyle(&MenuStyle->TabButtonStyle)
			.OnClicked(this, &SItemHeaderWidget::SortWeight)
		]
		]

		];

	*/
	TSharedPtr<class SHorizontalBox> HBox;
	ChildSlot
		[	
			SAssignNew(HBox,SHorizontalBox)	
		];
	TSharedPtr<class SButton> NameButton;
	TSharedPtr<class SButton> ItemTypeButton;
	TSharedPtr<class SButton> ValueButton;
	TSharedPtr<class SButton> WeightButton;
	switch (Category)
	{

	case EInventoryCategory::All:
		//All
		//		Name(Quant)		itemtype	value	weight
	

		HBox->AddSlot()
			[
				SAssignNew(NameButton, SButton)
				.TextStyle(&MenuStyle->HeaderTextStyle)
				.ButtonStyle(&MenuStyle->TabButtonStyle)
				.Text(FText::FromString("Name"))
				.OnClicked(this, &SItemHeaderWidget::SortName)
			];
		HBox->AddSlot()
			[
				SAssignNew(ItemTypeButton, SButton)
				.TextStyle(&MenuStyle->HeaderTextStyle)
				.Text(FText::FromString("ItemType"))
				.ButtonStyle(&MenuStyle->TabButtonStyle)
			.OnClicked(this, &SItemHeaderWidget::SortItemType)
			];
		HBox->AddSlot()
			[
				SAssignNew(ValueButton, SButton)
				.TextStyle(&MenuStyle->HeaderTextStyle)
				.Text(FText::FromString("Value"))
				.ButtonStyle(&MenuStyle->TabButtonStyle)
			.OnClicked(this, &SItemHeaderWidget::SortValue)
			];
		HBox->AddSlot()
			[
				SAssignNew(WeightButton, SButton)
				.TextStyle(&MenuStyle->HeaderTextStyle)
				.Text(FText::FromString("Weight"))
				.ButtonStyle(&MenuStyle->TabButtonStyle)
			.OnClicked(this, &SItemHeaderWidget::SortWeight)
			];
			
/*
*/		
		
		break;
	case EInventoryCategory::Weapons:
/*
		Weapons
			Name		WeaponType AmmoType Clip / MaxClip	Damage
			Loot
*/
		HBox->AddSlot()
			[
				SAssignNew(NameButton, SButton)
				.TextStyle(&MenuStyle->HeaderTextStyle)
			.ButtonStyle(&MenuStyle->TabButtonStyle)
			.Text(FText::FromString("Name"))
			.OnClicked(this, &SItemHeaderWidget::SortName)
			];
		HBox->AddSlot()
			[
				SAssignNew(ItemTypeButton, SButton)
				.TextStyle(&MenuStyle->HeaderTextStyle)
			.Text(FText::FromString("Weapon"))
			.ButtonStyle(&MenuStyle->TabButtonStyle)
			.OnClicked(this, &SItemHeaderWidget::SortWeaponType)
			];
		HBox->AddSlot()
			[
				SAssignNew(ItemTypeButton, SButton)
				.TextStyle(&MenuStyle->HeaderTextStyle)
			.Text(FText::FromString("Ammo"))
			.ButtonStyle(&MenuStyle->TabButtonStyle)
			.OnClicked(this, &SItemHeaderWidget::SortAmmoType)
			];
		HBox->AddSlot()
			[
				SAssignNew(ItemTypeButton, SButton)
				.TextStyle(&MenuStyle->HeaderTextStyle)
			.Text(FText::FromString("Clip"))
			.ButtonStyle(&MenuStyle->TabButtonStyle)
			.OnClicked(this, &SItemHeaderWidget::SortClip)
			];
		HBox->AddSlot()
			[
				SAssignNew(ValueButton, SButton)
				.TextStyle(&MenuStyle->HeaderTextStyle)
			.Text(FText::FromString("Damage"))
			.ButtonStyle(&MenuStyle->TabButtonStyle)
			.OnClicked(this, &SItemHeaderWidget::SortDamage)
			];

		break;
	case EInventoryCategory::Loot:
			//Name(Quant)		LootType	Value Weight
		HBox->AddSlot()
			[
				SAssignNew(NameButton, SButton)
				.TextStyle(&MenuStyle->HeaderTextStyle)
			.ButtonStyle(&MenuStyle->TabButtonStyle)
			.Text(FText::FromString("Name"))
			.OnClicked(this, &SItemHeaderWidget::SortName)
			];
		HBox->AddSlot()
			[
				SAssignNew(ItemTypeButton, SButton)
				.TextStyle(&MenuStyle->HeaderTextStyle)
			.Text(FText::FromString("Loot"))
			.ButtonStyle(&MenuStyle->TabButtonStyle)
			.OnClicked(this, &SItemHeaderWidget::SortLootType)
			];
		HBox->AddSlot()
			[
				SAssignNew(WeightButton, SButton)
				.TextStyle(&MenuStyle->HeaderTextStyle)
			.Text(FText::FromString("Weight"))
			.ButtonStyle(&MenuStyle->TabButtonStyle)
			.OnClicked(this, &SItemHeaderWidget::SortWeight)
			];
		HBox->AddSlot()
			[
				SAssignNew(ValueButton, SButton)
				.TextStyle(&MenuStyle->HeaderTextStyle)
			.Text(FText::FromString("Value"))
			.ButtonStyle(&MenuStyle->TabButtonStyle)
			.OnClicked(this, &SItemHeaderWidget::SortValue)
			];
		
		break;
	default:
		break;
	}










	/*
	Item = args._Item;
	MenuStyle = &FMenuStyles::Get().GetWidgetStyle<FGlobalStyle>("Global");
	Name.Bind(this, &SItemHeaderWidget::GetName);
	Value.Bind(this, &SItemHeaderWidget::GetValue);
	Weight.Bind(this, &SItemHeaderWidget::GetWeight);

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
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Fill)
			.AutoWidth()
			[
				SNew(STextBlock)
					.TextStyle(&MenuStyle->HUDTextStyle)
					.Text(Name)
					.MinDesiredWidth(550)
			]

			+ SHorizontalBox::Slot()
			.Padding(0, 0, 0, 0)
			.HAlign(HAlign_Right)
			.VAlign(VAlign_Fill)
			[
				SNew(STextBlock)
					.TextStyle(&MenuStyle->HUDTextStyle)
					.Text(Value)
					.MinDesiredWidth(30)
			]
			+ SHorizontalBox::Slot()
			.HAlign(HAlign_Right)
			.VAlign(VAlign_Fill)
			[
				SNew(STextBlock)
					.TextStyle(&MenuStyle->HUDTextStyle)
					.Text(Weight)
					.MinDesiredWidth(30)
			]
		
		]

		+ SOverlay::Slot()
			.VAlign(VAlign_Fill)
			.HAlign(HAlign_Fill)
			[
				SNew(SButton)
				.ButtonStyle(&MenuStyle->MenuButtonStyle)
				//.TextStyle(&MenuStyle->MenuButtonTextStyle)
				//.Text(FText::FromString("Play Game!"))
				.OnClicked(this, &SItemHeaderWidget::ItemClicked)
			]


		
	];
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


	/*

FText SItemHeaderWidget::GetName() const
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

FText SItemHeaderWidget::GetValue() const
{
	FString out = FString::FromInt(Item.Value);
	//out.Append("||");
	return FText::FromString(out);
}

FText SItemHeaderWidget::GetWeight() const
{
	FString out = FString::FromInt(Item.Weight);
	//out.Append("||");
	return FText::FromString(out);
}

FReply SItemHeaderWidget::ItemClicked()
{
	UseItem.ExecuteIfBound(Item);
	//UseItem.ExecuteIfBound();
	//OnToggleMenu.ExecuteIfBound();
	return FReply::Handled();
}
*/
FReply SItemHeaderWidget::SortName()
{
	OnSort.ExecuteIfBound(EItemSortType::Name);
	OnRebuildParent.ExecuteIfBound();
	return FReply::Handled();
}
FReply SItemHeaderWidget::SortValue()
{
	OnSort.ExecuteIfBound(EItemSortType::Value);
	OnRebuildParent.ExecuteIfBound();
	return FReply::Handled();
}
FReply SItemHeaderWidget::SortWeight()
{
	OnSort.ExecuteIfBound(EItemSortType::Weight);
	OnRebuildParent.ExecuteIfBound();
	return FReply::Handled();
}
FReply SItemHeaderWidget::SortWeaponType()
{
	OnSort.ExecuteIfBound(EItemSortType::WeaponType);
	OnRebuildParent.ExecuteIfBound();
	return FReply::Handled();
}
FReply SItemHeaderWidget::SortAmmoType()
{
	OnSort.ExecuteIfBound(EItemSortType::AmmoType);
	OnRebuildParent.ExecuteIfBound();
	return FReply::Handled();
}
FReply SItemHeaderWidget::SortClip()
{
	OnSort.ExecuteIfBound(EItemSortType::Clip);
	OnRebuildParent.ExecuteIfBound(); 
	return FReply::Handled();
}
FReply SItemHeaderWidget::SortClipMax()
{
	//Theres no sort clip max function or sort type! i mean, is it necessary?
	OnSort.ExecuteIfBound(EItemSortType::Clip);
	OnRebuildParent.ExecuteIfBound();
	return FReply::Handled();
}
FReply SItemHeaderWidget::SortDamage()
{
	OnSort.ExecuteIfBound(EItemSortType::Damage);
	OnRebuildParent.ExecuteIfBound(); 
	return FReply::Handled();
}
FReply SItemHeaderWidget::SortLootType()
{
	OnSort.ExecuteIfBound(EItemSortType::LootType);
	OnRebuildParent.ExecuteIfBound(); 
	return FReply::Handled();
}
FReply SItemHeaderWidget::SortQuantity()
{
	OnSort.ExecuteIfBound(EItemSortType::Quantity);
	OnRebuildParent.ExecuteIfBound(); 
	return FReply::Handled();
}
FReply SItemHeaderWidget::SortItemType()
{
	OnSort.ExecuteIfBound(EItemSortType::ItemType);
	OnRebuildParent.ExecuteIfBound(); 
	return FReply::Handled();
}



FText SItemHeaderWidget::GetName() const
{
	FString out = "";
	//out.Append("||");
	return FText::FromString(out);
}
FText SItemHeaderWidget::GetValue() const
{
	FString out = "";
	//out.Append("||");
	return FText::FromString(out);
}
FText SItemHeaderWidget::GetWeight() const
{
	FString out = "";
	//out.Append("||");
	return FText::FromString(out);
}
FText SItemHeaderWidget::GetWeaponType() const
{
	FString out = "";
	//out.Append("||");
	return FText::FromString(out);
}
FText SItemHeaderWidget::GetAmmoType() const
{
	FString out = "";
	//out.Append("||");
	return FText::FromString(out);
}
FText SItemHeaderWidget::GetClip() const
{
	FString out = "";
	//out.Append("||");
	return FText::FromString(out);
}
FText SItemHeaderWidget::GetClipMax() const
{
	FString out = "";
	//out.Append("||");
	return FText::FromString(out);
}
FText SItemHeaderWidget::GetDamage() const
{
	FString out = "";
	//out.Append("||");
	return FText::FromString(out);
}
FText SItemHeaderWidget::GetLootType() const
{
	FString out = "";
	//out.Append("||");
	return FText::FromString(out);
}
FText SItemHeaderWidget::GetItemType() const
{
	FString out = "";
	//out.Append("||");
	return FText::FromString(out);
}
FText SItemHeaderWidget::GetQuantity() const
{
	FString out = "";
	//out.Append("||");
	return FText::FromString(out);
}
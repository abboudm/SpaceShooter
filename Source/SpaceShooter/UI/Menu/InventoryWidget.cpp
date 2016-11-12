 
#include "SpaceShooter.h"
#include "InventoryWidget.h"
#include "UI/Styles/GlobalMenuStyle.h"
#include "UI/Styles/MenuStyles.h"

#include "UI/Menu/ItemWidget.h"
#include "UI/Menu/ItemHeaderWidget.h"

#include "Engine.h"
#include "Characters/BaseTrainer.h"
//#include "Characters/Trainer.h"
#include "Characters/PlayerCharacterController.h"
#include "Items/Item.h"
#include "Components/InventoryComponent.h"
BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SInventoryWidget::Construct(const FArguments& args)
{
	SelectedIndex = -1;
	CurrentIndex = -1;

	PC = args._PC;
	InventoryOwner = args._InventoryOwner;
	inv = InventoryOwner->FindComponentByClass<class UInventoryComponent>();
	Category = EInventoryCategory::All;
	SortType = EItemSortType::Name;
	


	SetActive(true);
	//Inventory = args._Inventory;
	ControllerHideMenuKey = EKeys::Gamepad_Special_Right;
	MenuStyle = &FMenuStyles::Get().GetWidgetStyle<FGlobalStyle>("Global");
	//ClipCount.Bind(this, &SIngameHUD::GetClipCount);
	WindowTitle.Bind(this, &SInventoryWidget::GetTitle);
	GoldAmmt.Bind(this, &SInventoryWidget::GetGold);
	SortType = EItemSortType::Name;

	ChildSlot
		[
			SNew(SCanvas)
			+ SCanvas::Slot()
			.Size(FVector2D(750, 1080))
			.Position(FVector2D(0, 0))
			[
				SNew(SImage)
				//.ColorAndOpacity(FSlateColor(FLinearColor(1, 1, 1, 0.8)))
				.ColorAndOpacity(FSlateColor::FSlateColor(FLinearColor(FColor::Black.WithAlpha(100))))
			]

			+ SCanvas::Slot()
				.Size(FVector2D(650, 80))
				.Position(FVector2D(0, 0))
			[
				
				SNew(STextBlock)
						.TextStyle(&MenuStyle->TitleTextStyle)
						.Text(WindowTitle)
			]

			+ SCanvas::Slot()
				.Size(FVector2D(100, 80))
				.Position(FVector2D(450, 0))
				[

					SNew(STextBlock)
					.TextStyle(&MenuStyle->ItemTextStyle)
					.Text(GoldAmmt)
				]


			+ SCanvas::Slot()
				.Size(FVector2D(750, 100))
				.Position(FVector2D(0, 80))
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				[
					SNew(SButton)
					.TextStyle(&MenuStyle->HeaderTextStyle)
					.ButtonStyle(&MenuStyle->TabButtonStyle)
					.Text(FText::FromString("All"))
					.OnClicked(this, &SInventoryWidget::ShowAllClicked)
	
				  
				]
				+ SHorizontalBox::Slot()
				[
					SNew(SButton)
					.ButtonStyle(&MenuStyle->TabButtonStyle)
					.TextStyle(&MenuStyle->HeaderTextStyle)
					.Text(FText::FromString("Weapons"))
					.OnClicked(this, &SInventoryWidget::ShowWeaponsClicked)
				]
				+ SHorizontalBox::Slot()
				[
					SNew(SButton)
					.TextStyle(&MenuStyle->HeaderTextStyle)
					.ButtonStyle(&MenuStyle->TabButtonStyle)
					.Text(FText::FromString("Loot"))
					.OnClicked(this, &SInventoryWidget::ShowLootClicked)
				]
			]
			+ SCanvas::Slot()
				.Size(FVector2D(750, 600))
				.Position(FVector2D(0, 180))
			[
				SAssignNew(InventoryBox,SScrollBox)
			]
		];
				
				
				
				/*
				+ SVerticalBox::Slot()
				[
					SNew(STextBlock)
						.TextStyle(&MenuStyle->TitleTextStyle)
						.Text(WindowTitle)
				]

				+ SVerticalBox::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					SAssignNew(InventoryBox, SScrollBox)				
				]
			]

		];
	*/

				/*+ SVerticalBox::Slot()
				[
					SNew(STextBlock)
					.TextStyle(&MenuStyle->HUDTextStyle)
					.Text(ClipCount)
				]*/



	//ATrainer* pt = Cast<ATrainer>(GEngine->GetWorld()->GetFirstPlayerController()->GetPawn());
	
	//TSharedRef<SVerticalBox> VBox;
	//SAssignNew(VBox, SVerticalBox);
	
	//VBox = SNew(SVerticalBox) + SVerticalBox::Slot();
	//TSharedRef<SVerticalBox> VBox = SAssignNew(VBox, SVerticalBox);
	//TSharedRef<SVerticalBox> VBox = SNew(SVerticalBox);
	//BContainer = VBox;
	
	/*
	*/
	
	/*
	VBox->AddSlot()
		[
			SNew(SButton)
			.ButtonStyle(&MenuStyle->MenuButtonStyle)
			.TextStyle(&MenuStyle->MenuButtonTextStyle)
			.Text(FText::FromString("Play Game!"))
			.OnClicked(this, &SInventoryWidget::ToggleMenuClicked)
		];
	VBox->AddSlot()
		[
			SNew(SButton)
			.ButtonStyle(&MenuStyle->MenuButtonStyle)
			.TextStyle(&MenuStyle->MenuButtonTextStyle)
			.Text(FText::FromString("Quit Game"))
			.OnClicked(this, &SInventoryWidget::QuitGameClicked)
		];
	*/



	
	/*
	*/
 
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION




void SInventoryWidget::UpdateHighlighted()
{

	if ((CurrentIndex != SelectedIndex) && (ItemButtonList.Num() > 0) && IsActive())
	{
		if (!ItemButtonList.IsValidIndex(CurrentIndex))
		{
			CurrentIndex = 0;
			SelectedIndex = CurrentIndex;
		}
		//ItemButtonList.GetData()[CurrentIndex]->button
		ItemButtonList.GetData()[CurrentIndex]->Button->SetButtonStyle(&MenuStyle->MenuButtonStyle);


		if (ItemButtonList.IsValidIndex(SelectedIndex))
		{
			CurrentIndex = SelectedIndex;
		}
		else
		{
			SelectedIndex = CurrentIndex;
		}

		ItemButtonList.GetData()[CurrentIndex]->Button->SetButtonStyle(&MenuStyle->SelectedMenuButtonStyle);
	}
	else if (CurrentIndex == SelectedIndex && ItemButtonList.IsValidIndex(CurrentIndex) && IsActive())
	{
		ItemButtonList.GetData()[CurrentIndex]->Button->SetButtonStyle(&MenuStyle->SelectedMenuButtonStyle);
	}
	else if (ItemButtonList.IsValidIndex(CurrentIndex) && !IsActive())
	{
		ItemButtonList.GetData()[CurrentIndex]->Button->SetButtonStyle(&MenuStyle->MenuButtonStyle);
	}
	else
	{
		//GEngine->AddOnScreenDebugMessage(-1,3,FColor::Red,"Else inside the highlight item function!!");
	}
}








FReply SInventoryWidget::ToggleMenuClicked()
{
	OnToggleMenu.ExecuteIfBound();
	return FReply::Handled();
}

FReply SInventoryWidget::ShowAllClicked()
{
	Category = EInventoryCategory::All;
	BuildAndShowMenu();
	return FReply::Handled();
}

FReply SInventoryWidget::ShowWeaponsClicked()
{
	Category = EInventoryCategory::Weapons;
	BuildAndShowMenu();
	return FReply::Handled();
}
FReply SInventoryWidget::ShowLootClicked()
{
	Category = EInventoryCategory::Loot;
	BuildAndShowMenu();
	return FReply::Handled();
}
 
void SInventoryWidget::UseItem(FItem item)
{
	if (TradeItem.IsBound())
	{
		TradeItem.Execute(item);
	}
	else
	{

		ABaseTrainer* pt = Cast<ABaseTrainer>(InventoryOwner);

		if (pt)
		{
			switch (item.ItemType)
			{

			case EItemType::Equipable:
				if (pt->hasCurrentItem())
				{
					pt->AddInventory(pt->RemoveCurrentItem());
				}
				pt->SetCurrentItem(item);
				pt->RemoveInventory(item);
				break;
			case EItemType::Loot:
				if (pt->RemoveInventory(item))
				{
					pt->DropItem(item);
				}
				break;
			default:
				//GEngine->AddOnScreenDebugMessage(1, 3, FColor::Red, "Trying to use an item that isnt equipable or loot!!!");
				break;
			}
		}
	}


	BuildAndShowMenu();
}
void SInventoryWidget::SortInventory(EItemSortType sorttype)
{
	SortInventory(sorttype, false);
}
void SInventoryWidget::SortInventory(EItemSortType sorttype,bool inverse)
{
	if (Inventory.Num() >= 1)
	{
		switch (sorttype)
		{
		//---------------------------------------------------------------------------------
		case EItemSortType::Name:
		
			Inventory.Sort([](const FItem& l, const FItem& r)->bool {

				if (l.Name > r.Name)
				{
					return false;
				}
				if (l.Name < r.Name)
				{
					return true;
				}

				return true;

				});
				SortType = EItemSortType::Name;


			break;
			//---------------------------------------------------------------------------------
		case EItemSortType::Value:
			Inventory.Sort([](const FItem& l, const FItem& r)->bool {

				if (l.Value < r.Value)
				{
					return false;
				}
				if (l.Value > r.Value)
				{
					return true;
				}
				if (l.Name > r.Name)
				{
					return false;
				}
				if (l.Name < r.Name)
				{
					return true;
				}

				return true;
				});
			SortType = EItemSortType::Value;
			break;
		//---------------------------------------------------------------------------------
		case EItemSortType::Weight:
			Inventory.Sort([](const FItem& l, const FItem& r)->bool {

				if (l.Weight < r.Weight)
				{
					return false;
				}
				if (l.Weight > r.Weight)
				{
					return true;
				}
				if (l.Name > r.Name)
				{
					return false;
				}
				if (l.Name < r.Name)
				{
					return true;
				}
				return true;

			});
			SortType = EItemSortType::Weight;
			break;
		//---------------------------------------------------------------------------------
		case EItemSortType::Quantity:
			Inventory.Sort([](const FItem& l, const FItem& r)->bool {

				if (l.Quantity < r.Quantity)
				{
					return false;
				}
				if (l.Quantity > r.Quantity)
				{
					return true;
				}
				if (l.Name > r.Name)
				{
					return false;
				}
				if (l.Name < r.Name)
				{
					return true;
				}

				return true;

			});
			SortType = EItemSortType::Quantity;
			break;
		case EItemSortType::ItemType:
			Inventory.Sort([](const FItem& l, const FItem& r)->bool {

				if (l.ItemType > r.ItemType)
				{
					return false;
				}
				if (l.ItemType < r.ItemType)
				{
					return true;
				}
				//This catches just in case ItemTypes are the same, it sorts by name!
				if (l.Name > r.Name)
				{
					return false;
				}
				if (l.Name < r.Name)
				{
					return true;
				}
				return true;
			});
			SortType = EItemSortType::ItemType;
			break;
		case EItemSortType::LootType:
			Inventory.Sort([](const FItem& l, const FItem& r)->bool {

				if (l.LootType > r.LootType)
				{
					return false;
				}
				if (l.LootType < r.LootType)
				{
					return true;
				}
				//This catches just in case ItemTypes are the same, it sorts by name!
				if (l.Name > r.Name)
				{
					return false;
				}
				if (l.Name < r.Name)
				{
					return true;
				}
				return true;
			});
			SortType = EItemSortType::LootType;
			break;
		case EItemSortType::EquipType:
			Inventory.Sort([](const FItem& l, const FItem& r)->bool {

				if (l.EquipType > r.EquipType)
				{
					return false;
				}
				if (l.EquipType < r.EquipType)
				{
					return true;
				}
				//This catches just in case ItemTypes are the same, it sorts by name!
				if (l.Name > r.Name)
				{
					return false;
				}
				if (l.Name < r.Name)
				{
					return true;
				}
				return true;
			});
			SortType = EItemSortType::EquipType;
			break;
		case EItemSortType::WeaponType:
			Inventory.Sort([](const FItem& l, const FItem& r)->bool {

				if (l.WeaponType > r.WeaponType)
				{
					return false;
				}
				if (l.WeaponType < r.WeaponType)
				{
					return true;
				}
				//This catches just in case ItemTypes are the same, it sorts by name!
				if (l.Name > r.Name)
				{
					return false;
				}
				if (l.Name < r.Name)
				{
					return true;
				}
				return true;
			});
			SortType = EItemSortType::WeaponType;
			break;
		case EItemSortType::AmmoType:
			Inventory.Sort([](const FItem& l, const FItem& r)->bool {

				if (l.AmmoType > r.AmmoType)
				{
					return false;
				}
				if (l.AmmoType < r.AmmoType)
				{
					return true;
				}
				//This catches just in case ItemTypes are the same, it sorts by name!
				if (l.Name > r.Name)
				{
					return false;
				}
				if (l.Name < r.Name)
				{
					return true;
				}
				return true;
			});
			SortType = EItemSortType::AmmoType;
			break;
		case EItemSortType::Clip:
			Inventory.Sort([](const FItem& l, const FItem& r)->bool {

				if (l.AmmoInClip < r.AmmoInClip)
				{
					return false;
				}
				if (l.AmmoInClip > r.AmmoInClip)
				{
					return true;
				}
				//This catches just in case ItemTypes are the same, it sorts by name!
				if (l.Name > r.Name)
				{
					return false;
				}
				if (l.Name < r.Name)
				{
					return true;
				}
				return true;
			});
			SortType = EItemSortType::Damage;
			break;
		case EItemSortType::Burst:
			break;
		case EItemSortType::FullAuto:
			break;
		default:
			break;
		}

	}
}
/**

*/
void SInventoryWidget::BuildAndShowMenu()
{
	if (InventoryOwner && InventoryBox.IsValid())
	{
		
		
		if (inv)
		{
			//--------------------------------------------------------------
			//Initialize containers
			Inventory = inv->GetInventory();
			SortInventory(SortType);
			//Clear the button list
			ItemButtonList.Empty();
			//clear the actual button widgets && header widget
			InventoryBox->ClearChildren();
			
			//---------------------------------------------------------------
			//Construct Header
			TSharedPtr<class SItemHeaderWidget> Header;
			InventoryBox->AddSlot()
				[
					SAssignNew(Header, SItemHeaderWidget)
					.Category(Category)
				];
			Header->OnSort.BindSP(this, &SInventoryWidget::SortInventory);
			Header->OnRebuildParent.BindSP(this, &SInventoryWidget::BuildAndShowMenu);
			
			//---------------------------------------------------------------
			//Construct Buttons Items
			for (int i = 0; i < Inventory.Num(); i++)
			{
				TSharedPtr<class SItemWidget> ItemButton;
				switch (Category)
				{
				case EInventoryCategory::All:
					//GEngine->AddOnScreenDebugMessage(0, 1, FColor::Yellow, "All Category Button Making!");
					InventoryBox->AddSlot()
						[
							SAssignNew(ItemButton, SItemWidget)
							.Item(Inventory.GetData()[i])
							.Category(Category)
						];
					ItemButton->UseItem.BindSP(this, &SInventoryWidget::UseItem);
					ItemButtonList.Add(ItemButton);
					break;
				case EInventoryCategory::Weapons:
					//GEngine->AddOnScreenDebugMessage(0, 1, FColor::Yellow, "Weapons Category Button Making!");
					if (!(Inventory.GetData()[i].ItemType == EItemType::Loot))
					{
						InventoryBox->AddSlot()
							[
								SAssignNew(ItemButton, SItemWidget)
								.Item(Inventory.GetData()[i])
								.Category(Category)
							];
						ItemButton->UseItem.BindSP(this, &SInventoryWidget::UseItem);
						ItemButtonList.Add(ItemButton);
					}
					
					break;
				case EInventoryCategory::Loot:
					//GEngine->AddOnScreenDebugMessage(0, 1, FColor::Yellow, "Loot Category Button Making!");
					if (!(Inventory.GetData()[i].ItemType == EItemType::Equipable))
					{
						InventoryBox->AddSlot()
							[
								SAssignNew(ItemButton, SItemWidget)
								.Item(Inventory.GetData()[i])
								.Category(Category)
							];
						ItemButton->UseItem.BindSP(this, &SInventoryWidget::UseItem);
						ItemButtonList.Add(ItemButton);
					}
					break;
				default:
					break;
				}


				if (i == CurrentIndex && ItemButtonList.IsValidIndex(CurrentIndex) && IsActive())
				{
					ItemButtonList.GetData()[CurrentIndex]->Button->SetButtonStyle(&MenuStyle->MenuButtonStyle);
				}

			}
		
			//---------------------------------------------------------------
			//Update the current index

			
			if ((CurrentIndex == -1 || SelectedIndex == -1) && ItemButtonList.Num() > 0)
			{
				CurrentIndex = 0;
				SelectedIndex = CurrentIndex;
			}
			else if (ItemButtonList.Num() > 0)
			{
				if (CurrentIndex >= ItemButtonList.Num())
				{
					CurrentIndex = ItemButtonList.Num() - 1;
				}
				else if (ItemButtonList.IsValidIndex(CurrentIndex))
				{
					SelectedIndex = CurrentIndex;
				}
				else
				{
					CurrentIndex = 0;
					SelectedIndex = CurrentIndex;
				}
			}
			else
			{
				CurrentIndex = -1;
				SelectedIndex = CurrentIndex;
			}

			UpdateHighlighted();


		}
	}

	//VBox->ClearChildren();
}

void SInventoryWidget::RebuildList()
{
	OnRebuildParent.ExecuteIfBound();
}
void SInventoryWidget::HideMenu()
{

}

FText SInventoryWidget::GetTitle() const
{
	//FString out = "Window Title";
	FString out = InventoryOwner->GetName();
	//out.Append(FString::FromInt(pt->GetAmmo(pt->GetCurrentItem().AmmoType)));
	out.Append("");
	//out.Append(pt->GetCurrentItem().Name.ToString());
	return FText::FromString(out);

}
FText SInventoryWidget::GetGold() const
{
	FString out = "";
	//out.Append(FString::FromInt(pt->GetAmmo(pt->GetCurrentItem().AmmoType)));
	if (inv && inv->GetGold() > 0)
	{
		out.Append("Gold: ");
		out.Append(FString::FromInt(inv->GetGold()));
	}
	//out.Append(pt->GetCurrentItem().Name.ToString());
	return FText::FromString(out);

}



FReply SInventoryWidget::OnFocusReceived(const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent)
{
	//return FReply::Handled().ReleaseMouseCapture().SetUserFocus(SharedThis(this), EFocusCause::SetDirectly, true);
	//return FReply::Handled().ReleaseMouseCapture().CaptureJoystick(SharedThis(this), true);
	//return FReply::Handled().ReleaseMouseCapture().SetUserFocus(SharedThis(this));
	return FReply::Handled();
}



void SInventoryWidget::ClickSelectedIndex()
{
	if (ItemButtonList.IsValidIndex(CurrentIndex))
	{
		ItemButtonList.GetData()[CurrentIndex]->ItemClicked();
	}
	UpdateHighlighted();

}


void SInventoryWidget::IncrementIndex()
{
	if (!(SelectedIndex >= ItemButtonList.Num()))
	{
		SelectedIndex++;
	}
	UpdateHighlighted();


}

void SInventoryWidget::DecrementIndex()
{
	if (!(SelectedIndex < 0))
	{
		SelectedIndex--;
	}
	UpdateHighlighted();

}



bool SInventoryWidget::IsActive() const
{
	return bIsActive;
}
void SInventoryWidget::SetActive(bool isactive)
{
	bIsActive = isactive;
	BuildAndShowMenu();//maybe useless/not good to call here?
}


FReply SInventoryWidget::OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
{
	FReply Result = FReply::Unhandled();
	const int32 UserIndex = InKeyEvent.GetUserIndex();
	//bool bEventUserCanInteract = GetOwnerUserIndex() == -1 || UserIndex == GetOwnerUserIndex();

	//if (!bControlsLocked && bEventUserCanInteract)
	//if(true)
	if(PC->IsGameMenuUp())
	{
		const FKey Key = InKeyEvent.GetKey();
		
		//Main Pause Menu Close
		if ((Key == ControllerHideMenuKey || Key == EKeys::One || Key == EKeys::Global_Play || Key == EKeys::Global_Menu) && !InKeyEvent.IsRepeat())
		{
			OnToggleMenu.ExecuteIfBound();
			Result = FReply::Handled();
		}
		



		//-------------------------------------------------------------------------------
		//Buttons
		//B Button, back
		else if (Key == EKeys::Gamepad_FaceButton_Right && !InKeyEvent.IsRepeat())
		{
			OnToggleMenu.ExecuteIfBound();
			Result = FReply::Handled();
		}
		//A Button, select
		else if (Key == EKeys::Gamepad_FaceButton_Bottom && !InKeyEvent.IsRepeat())
		{
			ClickSelectedIndex();
			Result = FReply::Handled();
		}




		//-------------------------------------------------------------------------------
		//Directions Up/Down, analog stick is possibly repeating
		else if (Key == EKeys::Gamepad_DPad_Up && !InKeyEvent.IsRepeat())
		{
			DecrementIndex();
			Result = FReply::Handled();
		}

		else if (Key == EKeys::Gamepad_DPad_Down && !InKeyEvent.IsRepeat())
		{
			
			IncrementIndex();
			Result = FReply::Handled();

		}
		
		else if (Key == EKeys::Gamepad_LeftStick_Down)
		{
			IncrementIndex();
			Result = FReply::Handled();
		}
		else if (Key == EKeys::Gamepad_LeftStick_Up)
		{
			DecrementIndex();
			Result = FReply::Handled();
		}



		else if (Key == EKeys::Gamepad_LeftStick_Left && !InKeyEvent.IsRepeat())
		{
		}
		else if (Key == EKeys::Gamepad_LeftStick_Right && !InKeyEvent.IsRepeat())
		{
		}


		else if (Key == EKeys::Gamepad_DPad_Left && !InKeyEvent.IsRepeat())
		{
		}
		else if (Key == EKeys::Gamepad_DPad_Right && !InKeyEvent.IsRepeat())
		{
		}

		else if (Key == EKeys::Gamepad_FaceButton_Top && !InKeyEvent.IsRepeat())
		{
			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Yellow, "Y Button Pressed inside the inventory!!");
		}
		else if (Key == EKeys::Gamepad_FaceButton_Left && !InKeyEvent.IsRepeat())
		{
		}
		else if (Key == EKeys::Gamepad_LeftShoulder && !InKeyEvent.IsRepeat())
		{
		}
		
		
		
		
		
		else if (Key == EKeys::Gamepad_LeftThumbstick && !InKeyEvent.IsRepeat())
		{
		}
		else if (Key == EKeys::Gamepad_LeftTrigger && !InKeyEvent.IsRepeat())
		{
		}
		else if (Key == EKeys::Gamepad_LeftTriggerAxis && !InKeyEvent.IsRepeat())
		{
		}
		else if (Key == EKeys::Gamepad_LeftX && !InKeyEvent.IsRepeat())
		{
		}
		else if (Key == EKeys::Gamepad_LeftY && !InKeyEvent.IsRepeat())
		{
		}
		else if (Key == EKeys::Gamepad_RightShoulder && !InKeyEvent.IsRepeat())
		{
		}
		else if (Key == EKeys::Gamepad_RightStick_Down && !InKeyEvent.IsRepeat())
		{
		}
		else if (Key == EKeys::Gamepad_RightStick_Left && !InKeyEvent.IsRepeat())
		{
		}
		else if (Key == EKeys::Gamepad_RightStick_Right && !InKeyEvent.IsRepeat())
		{
		}
		else if (Key == EKeys::Gamepad_RightStick_Up && !InKeyEvent.IsRepeat())
		{
		}
		else if (Key == EKeys::Gamepad_RightThumbstick && !InKeyEvent.IsRepeat())
		{
		}
		else if (Key == EKeys::Gamepad_RightTrigger)
		{
		}
		else if (Key == EKeys::Gamepad_RightTriggerAxis)
		{
		}
		else if (Key == EKeys::Gamepad_RightX && !InKeyEvent.IsRepeat())
		{
		}
		else if (Key == EKeys::Gamepad_RightY && !InKeyEvent.IsRepeat())
		{
		}
		else if (Key == EKeys::Gamepad_Special_Left && !InKeyEvent.IsRepeat())
		{
		}
		else if (Key == EKeys::Gamepad_Special_Right && !InKeyEvent.IsRepeat())
		{
		}

	
		/*
		if (Key == EKeys::Up || Key == EKeys::Gamepad_DPad_Up || Key == EKeys::Gamepad_LeftStick_Up)
		{
			ControllerUpInputPressed();
			int32 NextValidIndex = GetNextValidIndex(-1);
			if (NextValidIndex != SelectedIndex)
			{
				ButtonClicked(NextValidIndex);
			}
			Result = FReply::Handled();
		}
		else if (Key == EKeys::Down || Key == EKeys::Gamepad_DPad_Down || Key == EKeys::Gamepad_LeftStick_Down)
		{
			ControllerDownInputPressed();
			int32 NextValidIndex = GetNextValidIndex(1);
			if (NextValidIndex != SelectedIndex)
			{
				ButtonClicked(NextValidIndex);
			}
			Result = FReply::Handled();
		}
		else if (Key == EKeys::Left || Key == EKeys::Gamepad_DPad_Left || Key == EKeys::Gamepad_LeftStick_Left)
		{
			ChangeOption(-1);
			Result = FReply::Handled();
		}
		else if (Key == EKeys::Right || Key == EKeys::Gamepad_DPad_Right || Key == EKeys::Gamepad_LeftStick_Right)
		{
			ChangeOption(1);
			Result = FReply::Handled();
		}
		else if (Key == EKeys::Gamepad_FaceButton_Top)
		{
			ProfileUISwap(UserIndex);
			Result = FReply::Handled();
		}
		else if (Key == EKeys::Enter)
		{
			ConfirmMenuItem();
			Result = FReply::Handled();
		}
		else if (Key == EKeys::Gamepad_FaceButton_Bottom && !InKeyEvent.IsRepeat())
		{
			ControllerFacebuttonDownPressed();
			ConfirmMenuItem();
			Result = FReply::Handled();
		}
		else if ((Key == EKeys::Escape || Key == EKeys::Gamepad_FaceButton_Right || Key == EKeys::Gamepad_Special_Left || Key == EKeys::Global_Back || Key == EKeys::Global_View) && !InKeyEvent.IsRepeat())
		{
			MenuGoBack();
			Result = FReply::Handled();
		}
		else if (Key == EKeys::Gamepad_FaceButton_Left)
		{
			ControllerFacebuttonLeftPressed();
			Result = FReply::Handled();
		}
		else if ((Key == ControllerHideMenuKey || Key == EKeys::Global_Play || Key == EKeys::Global_Menu) && !InKeyEvent.IsRepeat())
		{
			OnToggleMenu.ExecuteIfBound();
			Result = FReply::Handled();
		}










		ChildSlot
		[
		SNew(SOverlay)
		+ SOverlay::Slot()
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Top)
		[
		SNew(STextBlock)
		.ColorAndOpacity(FLinearColor::White)
		.ShadowColorAndOpacity(FLinearColor::Black)
		.ShadowOffset(FIntPoint(-1, 1))
		.Font(FSlateFontInfo("Arial", 26))
		.Text(FText::FromString("Main Menu"))
		]
		+ SOverlay::Slot()
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		[
		SNew(SScrollBox)
		+ SScrollBox::Slot()
		[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		[
		SNew(SButton)
		.Text(FText::FromString("Play Game!"))
		.OnClicked(this, &SInventoryWidget::ToggleMenuClicked)
		]
		+ SVerticalBox::Slot()
		[
		SNew(SButton)
		.Text(FText::FromString("Quit Game"))
		.OnClicked(this, &SInventoryWidget::QuitGameClicked)
		]
		]
		]
		];




		*/
	}
	return Result;
}

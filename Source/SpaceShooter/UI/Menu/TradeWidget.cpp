 
#include "SpaceShooter.h"
#include "TradeWidget.h"
#include "UI/Styles/GlobalMenuStyle.h"
#include "UI/Styles/MenuStyles.h"
#include "Characters/PlayerCharacterController.h"
#include "Components/InventoryComponent.h"
#include "UI/Menu/InventoryWidget.h"
//#include "UI/Menu/ItemWidget.h"
//#include "UI/Menu/ItemHeaderWidget.h"

#include "Engine.h"

#include "Items/Item.h"
BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void STradeWidget::Construct(const FArguments& args)
{
	ActiveWidget = true; //set to the traders default active
	InventoryOwner = args._InventoryOwner;
	PC = args._PC;
	Trader = args._Trader;
	PlayerInventory = InventoryOwner->FindComponentByClass<class UInventoryComponent>();
	TraderInventory = Trader->FindComponentByClass<class UInventoryComponent>();


	//inv = InventoryOwner->FindComponentByClass<class UInventoryComponent>();
	//Category = EInventoryCategory::All;
	//SortType = EItemSortType::Name;
	
	//Inventory = args._Inventory;
	ControllerHideMenuKey = EKeys::Gamepad_Special_Right;
	MenuStyle = &FMenuStyles::Get().GetWidgetStyle<FGlobalStyle>("Global");
	//ClipCount.Bind(this, &SIngameHUD::GetClipCount);
	
	bTradeMoney = false;


	ChildSlot
		[
			SNew(SCanvas)
			+ SCanvas::Slot()
			.Size(FVector2D(750, 1080))
			.Position(FVector2D(0, 0))
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SAssignNew(PlayerWidget, SInventoryWidget)
				.InventoryOwner(InventoryOwner)
				.PC(PC)
				.Cursor(EMouseCursor::None)
				
			]
			+ SCanvas::Slot()
			.Size(FVector2D(750, 1080))
			.Position(FVector2D(750, 0))
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SAssignNew(TraderWidget, SInventoryWidget)
				.InventoryOwner(Trader)
				.PC(PC)
				.Cursor(EMouseCursor::None)
			]

		];

	PlayerWidget->OnToggleMenu.BindSP(this, &STradeWidget::ToggleChildren);
	TraderWidget->OnToggleMenu.BindSP(this, &STradeWidget::ToggleChildren);
	
	PlayerWidget->TradeItem.BindSP(this, &STradeWidget::GiveItem);
	TraderWidget->TradeItem.BindSP(this, &STradeWidget::TakeItem);

	if (ActiveWidget)
	{
		TraderWidget->SetActive(true);
		PlayerWidget->SetActive(false);
	}




	/*
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
					.OnClicked(this, &STradeWidget::ShowAllClicked)
				]
				+ SHorizontalBox::Slot()
				[
					SNew(SButton)
					.ButtonStyle(&MenuStyle->TabButtonStyle)
					.TextStyle(&MenuStyle->HeaderTextStyle)
					.Text(FText::FromString("Weapons"))
					.OnClicked(this, &STradeWidget::ShowWeaponsClicked)
				]
				+ SHorizontalBox::Slot()
				[
					SNew(SButton)
					.TextStyle(&MenuStyle->HeaderTextStyle)
					.ButtonStyle(&MenuStyle->TabButtonStyle)
					.Text(FText::FromString("Loot"))
					.OnClicked(this, &STradeWidget::ShowLootClicked)
				]
			]
			+ SCanvas::Slot()
				.Size(FVector2D(750, 600))
				.Position(FVector2D(0, 180))
			[
				SAssignNew(InventoryBox,SScrollBox)
			]
		];
	*/
	
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
FReply STradeWidget::ToggleMenuClicked()
{
	OnToggleMenu.ExecuteIfBound();
	return FReply::Handled();
}
void STradeWidget::ToggleChildren()
{
	OnToggleMenu.ExecuteIfBound();

}
/*
FReply STradeWidget::ShowAllClicked()
{
	Category = EInventoryCategory::All;
	BuildAndShowMenu();
	return FReply::Handled();
}

FReply STradeWidget::ShowWeaponsClicked()
{
	Category = EInventoryCategory::Weapons;
	BuildAndShowMenu();
	return FReply::Handled();
}
FReply STradeWidget::ShowLootClicked()
{
	Category = EInventoryCategory::Loot;
	BuildAndShowMenu();
	return FReply::Handled();
}
*/
void STradeWidget::TakeItem(FItem item)
{
	if (PlayerInventory && TraderInventory)
	{

		if (bTradeMoney)
		{
			if (PlayerInventory->GetGold() >= item.Value)
			{
				//UseGold, plug that into Add Gold, then remove/Add items to respective inventory
				TraderInventory->AddGold(PlayerInventory->UseGold(item.Value));
				TraderInventory->RemoveItemFromInventory(item);
				if (item.Quantity > 1)
				{
					//handle what happens 
					//should instead be telling inventory "im taking X ammount" and then it returns Y ammount, how ammo is working already
					item.Quantity = 1;
				}
				PlayerInventory->AddItemToInventory(item);
			
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(0, 2, FColor::Yellow, "Dont have enough money!");
			}

		}
		else
		{
			TraderInventory->RemoveItemFromInventory(item);
			if (item.Quantity > 1)
			{
				//handle what happens 
				//should instead be telling inventory "im taking X ammount" and then it returns Y ammount, how ammo is working already
				item.Quantity = 1;
			}
			PlayerInventory->AddItemToInventory(item);
		}
	}

	BuildAndShowMenu();
}


void STradeWidget::GiveItem(FItem item)
{
	if (PlayerInventory && TraderInventory)
	{

		if (bTradeMoney)
		{
			if (TraderInventory->GetGold() >= item.Value)
			{
				//UseGold, plug that into Add Gold, then remove/Add items to respective inventory
				PlayerInventory->AddGold(TraderInventory->UseGold(item.Value));
				PlayerInventory->RemoveItemFromInventory(item);
				TraderInventory->AddItemToInventory(item);

			}
			else
			{
				GEngine->AddOnScreenDebugMessage(0, 2, FColor::Yellow, "Dont have enough money!");
			}

		}
		else
		{
			PlayerInventory->RemoveItemFromInventory(item);
			TraderInventory->AddItemToInventory(item);
	
		}

	}




	/*
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
				GEngine->AddOnScreenDebugMessage(1, 3, FColor::Red, "Trying to use an item that isnt equipable or loot!!!");
				break;
			}
		}
	}


	*/
	BuildAndShowMenu();
}


void STradeWidget::BuildAndShowMenu()
{
	PlayerWidget->BuildAndShowMenu();
	TraderWidget->BuildAndShowMenu();

	if (PlayerWidget.IsValid() && TraderWidget.IsValid())
	{
		if (ActiveWidget)
		{
			TraderWidget->SetActive(true);
			PlayerWidget->SetActive(false);
		}
		else
		{
			TraderWidget->SetActive(false);
			PlayerWidget->SetActive(true);
		}

	}
	




	/*
	if (InventoryOwner && InventoryBox.IsValid())
	{

		
		if (inv)
		{
				Inventory = inv->GetInventory();
				SortInventory(SortType);
	
			InventoryBox->ClearChildren();
			
			TSharedPtr<class SItemHeaderWidget> Header;
			InventoryBox->AddSlot()
				[
					SAssignNew(Header, SItemHeaderWidget)
					.Category(Category)
				];
			Header->OnSort.BindSP(this, &STradeWidget::SortInventory);
			Header->OnRebuildParent.BindSP(this, &STradeWidget::BuildAndShowMenu);
			for (int i = 0; i < Inventory.Num(); i++)
			{
				TSharedPtr<class SItemWidget> ItemButton;
				switch (Category)
				{
				case EInventoryCategory::All:
					GEngine->AddOnScreenDebugMessage(0, 1, FColor::Yellow, "All Category Button Making!");
					InventoryBox->AddSlot()
						[
							SAssignNew(ItemButton, SItemWidget)
							.Item(Inventory.GetData()[i])
							.Category(Category)
						];
					ItemButton->UseItem.BindSP(this, &STradeWidget::UseItem);
					break;
				case EInventoryCategory::Weapons:
					GEngine->AddOnScreenDebugMessage(0, 1, FColor::Yellow, "Weapons Category Button Making!");
					if (!(Inventory.GetData()[i].ItemType == EItemType::Loot))
					{
						InventoryBox->AddSlot()
							[
								SAssignNew(ItemButton, SItemWidget)
								.Item(Inventory.GetData()[i])
								.Category(Category)
							];
						ItemButton->UseItem.BindSP(this, &STradeWidget::UseItem);
					}
					
					break;
				case EInventoryCategory::Loot:
					GEngine->AddOnScreenDebugMessage(0, 1, FColor::Yellow, "Loot Category Button Making!");
					if (!(Inventory.GetData()[i].ItemType == EItemType::Equipable))
					{
						InventoryBox->AddSlot()
							[
								SAssignNew(ItemButton, SItemWidget)
								.Item(Inventory.GetData()[i])
								.Category(Category)
							];
						ItemButton->UseItem.BindSP(this, &STradeWidget::UseItem);
					}
					break;
				default:
					break;
				}

			}
		}
	}

	*/
	//VBox->ClearChildren();
}

void STradeWidget::RebuildList()
{
	OnRebuildParent.ExecuteIfBound();
}
/*
FText STradeWidget::GetTitle() const
{
	FString out = "Window Title";
	//out.Append(FString::FromInt(pt->GetAmmo(pt->GetCurrentItem().AmmoType)));
	out.Append("");
	//out.Append(pt->GetCurrentItem().Name.ToString());
	return FText::FromString(out);

}
*/

FReply STradeWidget::OnFocusReceived(const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent)
{
	//return FReply::Handled().ReleaseMouseCapture().SetUserFocus(SharedThis(this), EFocusCause::SetDirectly, true);
	//return FReply::Handled().ReleaseMouseCapture().CaptureJoystick(SharedThis(this), true);
	//return FReply::Handled().ReleaseMouseCapture().SetUserFocus(SharedThis(this));
	return FReply::Handled();
}

FReply STradeWidget::OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
{
	FReply Result = FReply::Unhandled();
	const int32 UserIndex = InKeyEvent.GetUserIndex();
	//bool bEventUserCanInteract = GetOwnerUserIndex() == -1 || UserIndex == GetOwnerUserIndex();

	//if (!bControlsLocked && bEventUserCanInteract)
	if (PC->IsGameMenuUp())
	{
		const FKey Key = InKeyEvent.GetKey();
		
		//B button, and also start menu button - only gamepad bindings + the key '1'
		if ((Key == EKeys::Gamepad_FaceButton_Right || Key == ControllerHideMenuKey || Key == EKeys::One || Key == EKeys::Global_Play || Key == EKeys::Global_Menu) && !InKeyEvent.IsRepeat())
		{
			OnToggleMenu.ExecuteIfBound();
			Result = FReply::Handled();
		}

		//-------------------------------------------------------------------------------
		//A Button, select
		else if (Key == EKeys::Gamepad_FaceButton_Bottom && !InKeyEvent.IsRepeat())
		{
			if (ActiveWidget)
			{
				//Selecting FROM trademenu
				TraderWidget->ClickSelectedIndex();
			}
			else
			{
				PlayerWidget->ClickSelectedIndex();
			}
			Result = FReply::Handled();
		}




		//-------------------------------------------------------------------------------
		//Directions Up/Down, analog stick is possibly repeating
		else if (Key == EKeys::Gamepad_DPad_Up && !InKeyEvent.IsRepeat())
		{
			if (ActiveWidget)
			{
				//Tradermenu active
				TraderWidget->DecrementIndex();
			}
			else
			{
				//Player menu active
				PlayerWidget->DecrementIndex();
			}
			Result = FReply::Handled();
		}

		else if (Key == EKeys::Gamepad_DPad_Down && !InKeyEvent.IsRepeat())
		{
			if (ActiveWidget)
			{
				//Tradermenu active
				TraderWidget->IncrementIndex();
			}
			else
			{
				//Player menu active
				PlayerWidget->IncrementIndex();
			}
			Result = FReply::Handled();

		}

		else if (Key == EKeys::Gamepad_LeftStick_Down)
		{
			if (ActiveWidget)
			{
				//Tradermenu active
				TraderWidget->IncrementIndex();
			}
			else
			{
				//Player menu active
				PlayerWidget->IncrementIndex();
			}
			Result = FReply::Handled();
		}
		else if (Key == EKeys::Gamepad_LeftStick_Up)
		{
			if (ActiveWidget)
			{
				//Tradermenu active
				TraderWidget->DecrementIndex();
			}
			else
			{
				//Player menu active
				PlayerWidget->DecrementIndex();
			}
			Result = FReply::Handled();
		}
		else if (Key == EKeys::Gamepad_Special_Left)
		{
			ActiveWidget = !ActiveWidget;
			BuildAndShowMenu();
			Result = FReply::Handled();
		}
	}
	return Result;
}

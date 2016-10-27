 
#include "SpaceShooter.h"
#include "InventoryWidget.h"
#include "UI/Styles/GlobalMenuStyle.h"
#include "UI/Styles/MenuStyles.h"

#include "UI/Menu/ItemWidget.h"

#include "Engine.h"
#include "Characters/BaseTrainer.h"
//#include "Characters/Trainer.h"
#include "Characters/PlayerCharacterController.h"
#include "Items/Item.h"
#include "Components/InventoryComponent.h"
BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SInventoryWidget::Construct(const FArguments& args)
{
	InventoryOwner = args._InventoryOwner;
	inv = InventoryOwner->FindComponentByClass<class UInventoryComponent>();
	
	
	
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
					.Text(FText::FromString("Name"))
					.OnClicked(this, &SInventoryWidget::SortNameClicked)
				]
				+ SHorizontalBox::Slot()
				[
					SNew(SButton)
					.Text(FText::FromString("Value"))
					.OnClicked(this, &SInventoryWidget::SortValueClicked)
				]
				+ SHorizontalBox::Slot()
				[
					SNew(SButton)
					.Text(FText::FromString("Quantity"))
					.OnClicked(this, &SInventoryWidget::SortQuantityClicked)
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
FReply SInventoryWidget::ToggleMenuClicked()
{
	OnToggleMenu.ExecuteIfBound();
	return FReply::Handled();
}

FReply SInventoryWidget::SortNameClicked()
{
	SortType = EItemSortType::Name;
	BuildAndShowMenu();
	return FReply::Handled();
}

FReply SInventoryWidget::SortValueClicked()
{
	SortType = EItemSortType::Value;
	BuildAndShowMenu();
	return FReply::Handled();
}
FReply SInventoryWidget::SortQuantityClicked()
{
	SortType = EItemSortType::Quantity;
	BuildAndShowMenu();
	return FReply::Handled();
}
 
void SInventoryWidget::UseItem(FItem item)
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

			break;
		case EItemSortType::ItemType:
			break;
		case EItemSortType::LootType:
			break;
		case EItemSortType::EquipType:
			break;
		case EItemSortType::WeaponType:
			break;
		case EItemSortType::AmmoType:
			break;
		case EItemSortType::Clip:
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


void SInventoryWidget::BuildAndShowMenu()
{
	if (InventoryOwner && InventoryBox.IsValid())
	{

		
		if (inv)
		{
				Inventory = inv->GetInventory();
				SortInventory(SortType);
			//UInventoryComponent* inv = InventoryOwner->GetComponentByClass(UInventoryComponent)
			//Inventory = InventoryOwner->GetInventory();
		

			/*
			Inventory.Sort([](const FItem& Lhs, const FItem& Rhs) -> bool 
			{
				if (Lhs.Value < Rhs.Value) return true;
				if (Lhs.Value > Rhs.Value) return false;

			});
			*/




			InventoryBox->ClearChildren();
			for (int i = 0; i < Inventory.Num(); i++)
			{
				TSharedPtr<class SItemWidget> ItemButton;

				InventoryBox->AddSlot()
					[
						SAssignNew(ItemButton, SItemWidget)
						.Item(Inventory.GetData()[i])
					];
				ItemButton->UseItem.BindSP(this, &SInventoryWidget::UseItem);
			}
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
	FString out = "Window Title";
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
	return FReply::Handled().ReleaseMouseCapture().SetUserFocus(SharedThis(this));

}

FReply SInventoryWidget::OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
{
	FReply Result = FReply::Unhandled();
	const int32 UserIndex = InKeyEvent.GetUserIndex();
	//bool bEventUserCanInteract = GetOwnerUserIndex() == -1 || UserIndex == GetOwnerUserIndex();

	//if (!bControlsLocked && bEventUserCanInteract)
	if(true)
	{
		const FKey Key = InKeyEvent.GetKey();
		if ((Key == ControllerHideMenuKey || Key == EKeys::One || Key == EKeys::Global_Play || Key == EKeys::Global_Menu) && !InKeyEvent.IsRepeat())
		{
			OnToggleMenu.ExecuteIfBound();
			Result = FReply::Handled();
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

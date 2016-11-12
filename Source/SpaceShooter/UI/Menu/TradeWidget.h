
#pragma once
 
#include "SlateBasics.h"
#include "Items/Item.h"
#include "Components/InventoryComponent.h"
#include "Characters/BaseTrainer.h"
// Lays out and controls the Main Menu UI for our tutorial.
class SPACESHOOTER_API STradeWidget : public SCompoundWidget
{
 
public:
	SLATE_BEGIN_ARGS(STradeWidget)
	{}
	SLATE_ARGUMENT(AActor* , InventoryOwner)
	SLATE_ARGUMENT(APlayerCharacterController*, PC)

	SLATE_ARGUMENT(AActor*, Trader)
	SLATE_END_ARGS()
 
    void Construct(const FArguments& args);
	
	//-----------------------------------------------------
	//Inventory
	//-----------------------------------------------------

	bool ActiveWidget; //True = trader, false = player, prob not the best way for doing this, but i mean, its always gonna be two widgets, players, and other


	APlayerCharacterController* PC;
	AActor* InventoryOwner;
	AActor* Trader;
	TSharedPtr<class SInventoryWidget> PlayerWidget;
	TSharedPtr<class SInventoryWidget> TraderWidget;
	UInventoryComponent* PlayerInventory;
	UInventoryComponent* TraderInventory;
	
	TSharedPtr<class SWidgetSwitcher> WidgetSwitcher;

	bool bTradeMoney;
	void GiveItem(FItem item);
	void TakeItem(FItem item);
	
	/*
	TArray<FItem> Inventory;
	TSharedPtr<class SScrollBox> InventoryBox;
	UInventoryComponent* inv;

	TAttribute<FText> WindowTitle;
	FText GetTitle() const;

	TAttribute<FText> GoldAmmt;
	FText GetGold() const;



	EInventoryCategory Category;
	FReply ShowAllClicked();
	FReply ShowWeaponsClicked();
	FReply ShowLootClicked();

	EItemSortType SortType;
	void SortInventory(EItemSortType sorttype);
	void SortInventory(EItemSortType sorttype,bool inverse);





	//-----------------------------------------------------
	
	//TAttribute<FText> AmmoCount;
	//FText GetAmmoCount() const;


	// Stores a weak reference to the HUD controlling this class.
	//TWeakObjectPtr<class ASpaceHUD> SpaceHUD;

	//TSharedPtr<SVerticalBox> VBox;
	*/
	FReply ToggleMenuClicked(); //OnExecute function
	void ToggleChildren();


	//-----------------------------------------------------
	//DELAGATES
	//-----------------------------------------------------
	
	
	//OnToggleMenu.ExecuteIfBound() this should toggle parents function of hiding this (inventory)
	DECLARE_DELEGATE(FOnToggleMenu);
	FOnToggleMenu OnToggleMenu;
	//trigger parent rebuild
	DECLARE_DELEGATE(FOnRebuildParent);
	FOnRebuildParent OnRebuildParent;
	//-----------------------------------------------------

	virtual bool SupportsKeyboardFocus() const override { return true; }
	virtual FReply OnFocusReceived(const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent) override;
	FKey ControllerHideMenuKey;
	FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent);

	
	const struct FGlobalStyle* MenuStyle;

	
	void RebuildList();
	void BuildAndShowMenu();
	

	
    



	

};
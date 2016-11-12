
#pragma once
 
#include "SlateBasics.h"
#include "Items/Item.h"
#include "Components/InventoryComponent.h"
#include "Characters/BaseTrainer.h"
// Lays out and controls the Main Menu UI for our tutorial.
class SPACESHOOTER_API SInventoryWidget : public SCompoundWidget
{
 
public:
	SLATE_BEGIN_ARGS(SInventoryWidget)
	{}
	SLATE_ARGUMENT(AActor* , InventoryOwner)
	SLATE_ARGUMENT(APlayerCharacterController*, PC)

	//SLATE_ARGUMENT(TArray<FItem>, Inventory)
	//SLATE_ARGUMENT(AActor* , Owner)
	SLATE_END_ARGS()
 
    void Construct(const FArguments& args);
	
	//-----------------------------------------------------
	//INventory
	//-----------------------------------------------------
	AActor* InventoryOwner;
	TArray<FItem> Inventory;
	TSharedPtr<class SScrollBox> InventoryBox;
	void UseItem(FItem item);
	UInventoryComponent* inv;

	TAttribute<FText> WindowTitle;
	FText GetTitle() const;

	TAttribute<FText> GoldAmmt;
	FText GetGold() const;

	bool bIsActive;
	bool IsActive() const;
	void SetActive(bool isactive);
	void UpdateHighlighted();
	void IncrementIndex();
	void DecrementIndex();
	void ClickSelectedIndex();


	EInventoryCategory Category;
	FReply ShowAllClicked();
	FReply ShowWeaponsClicked();
	FReply ShowLootClicked();

	EItemSortType SortType;
	void SortInventory(EItemSortType sorttype);
	void SortInventory(EItemSortType sorttype,bool inverse);




	//-----------------------------------------------------
	//Gamepad Selector
	APlayerCharacterController* PC;
	int SelectedIndex;
	int CurrentIndex;
	TArray<TSharedPtr<class SItemWidget>> ItemButtonList;



	//-----------------------------------------------------
	
	//TAttribute<FText> AmmoCount;
	//FText GetAmmoCount() const;


	// Stores a weak reference to the HUD controlling this class.
	//TWeakObjectPtr<class ASpaceHUD> SpaceHUD;

	//TSharedPtr<SVerticalBox> VBox;
	FReply ToggleMenuClicked(); //OnExecute function
 


	//-----------------------------------------------------
	//DELAGATES
	//-----------------------------------------------------
	DECLARE_DELEGATE_OneParam(FTradeItem, FItem);
	FTradeItem TradeItem;

	
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
	void HideMenu();
	
	
    



	

};

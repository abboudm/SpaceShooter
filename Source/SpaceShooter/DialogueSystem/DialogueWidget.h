
#pragma once
 
#include "SlateBasics.h"
//#include "Items/Item.h"
#include "DialogueSystem/Branch.h"
#include "DialogueSystem/Topic.h"
//#include "Components/InventoryComponent.h"
#include "Characters/BaseTrainer.h"
// Lays out and controls the Main Menu UI for our tutorial.



UENUM(BlueprintType)
enum class EDialogueState : uint8
{
	Idle,
	Speaking,
	FinishedSpeaking,
};


class SPACESHOOTER_API SDialogueWidget : public SCompoundWidget
{
 
public:
	SLATE_BEGIN_ARGS(SDialogueWidget)
	{}
	SLATE_ARGUMENT(AActor* , Speaker)
	SLATE_ARGUMENT(APlayerCharacterController*, PC)

	SLATE_END_ARGS()
 
    void Construct(const FArguments& args);
	
	AActor* Speaker;
	TArray<UBranch* > RootBranchList;
	UTopic* CurrentTopic;
	TArray<UTopic* > CurrentTopicList;
	bool bInsideBranch;

	EDialogueState CurrentState;





	//TArray<FItem> Inventory;
	//TSharedPtr<class SScrollBox> InventoryBox;
	//TAttribute<FText> WindowTitle;
	//FText GetTitle() const;



	
	void ClickSelectedIndex();
	void IncrementIndex();
	void DecrementIndex();


	//FTimerHandle TimerHandle_HandleTyping;
	

	//TFunction<void ()> TypeResponseString();
	//void TypeResponseString();
	
	void UpdateState();
	
	float TypeWriterSpeed;
	void SpeakResponse();
	void FinishSpeaking();
	int TypeWriterIndex;

	void SpeakHelloTopic();
	void FillRootTopics();
	void FillFromTopic(UTopic* topic);



	void UpdateHighlightedTopic();
	TArray<TSharedPtr<class SButton>> TopicListButtons;
	TSharedPtr<class SVerticalBox> TopicListBox;
	TAttribute<EVisibility> TopicVisibility;
	EVisibility GetTopicVisibility() const;

	FString ResponseDisplayString;
	FString ResponseString;
	TAttribute<FText> ResponseText;
	FText GetResponse() const;

	//EInventoryCategory Category;
	//FReply ShowAllClicked();
	//FReply ShowWeaponsClicked();
	//FReply ShowLootClicked();

	
	//-----------------------------------------------------
	//Gamepad Selector
	APlayerCharacterController* PC;
	int SelectedIndex;
	int CurrentIndex;
	//TArray<TSharedPtr<class SItemWidget>> ItemButtonList;



	FReply ToggleMenuClicked(); //OnExecute function
 


	//-----------------------------------------------------
	//DELAGATES
	//-----------------------------------------------------
	//DECLARE_DELEGATE_OneParam(FTradeItem, FItem);
	//FTradeItem TradeItem;

	
	//OnToggleMenu.ExecuteIfBound() this should toggle parents function of hiding this (inventory)
	DECLARE_DELEGATE(FOnToggleMenu);
	FOnToggleMenu OnToggleMenu;
	//trigger parent rebuild
	DECLARE_DELEGATE(FOnRebuildParent);
	FOnRebuildParent OnRebuildParent;
	//-----------------------------------------------------

	virtual bool SupportsKeyboardFocus() const override { return true; }
	virtual FReply OnFocusReceived(const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent) override;
	//FKey ControllerHideMenuKey;
	//ControllerHideMenuKey = EKeys::Gamepad_Special_Right;
	FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent);

	
	const struct FGlobalStyle* MenuStyle;

	
	
	void RebuildList();
	void BuildAndShowMenu();
	void HideMenu();
	
	
    



	

};

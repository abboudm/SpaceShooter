 
#include "SpaceShooter.h"

#include "UI/Styles/GlobalMenuStyle.h"
#include "UI/Styles/MenuStyles.h"

//#include "InventoryWidget.h"
//#include "UI/Menu/ItemWidget.h"
//#include "UI/Menu/ItemHeaderWidget.h"

#include "Engine.h"
#include "Characters/BaseTrainer.h"
#include "Characters/PlayerCharacterController.h"
#include "Components/InteractionComponent.h"
#include "DialogueSystem/Branch.h"
#include "DialogueSystem/Topic.h"


#include "DialogueWidget.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SDialogueWidget::Construct(const FArguments& args)
{

	bInsideBranch = false;
	CurrentTopic = nullptr;
	TypeWriterSpeed = 0.05;
	TypeWriterIndex = -1;
	SelectedIndex = -1;
	CurrentIndex = -1;

	PC = args._PC;
	Speaker = args._Speaker;
	RootBranchList = Speaker->FindComponentByClass<class UInteractionComponent>()->Branchs;

	
	MenuStyle = &FMenuStyles::Get().GetWidgetStyle<FGlobalStyle>("Global");
	ResponseText.Bind(this, &SDialogueWidget::GetResponse);
	TopicVisibility.Bind(this, &SDialogueWidget::GetTopicVisibility);

	FVector2D ScreenResolution;
	GEngine->GameViewport->GetViewportSize(ScreenResolution);
	FVector2D ResponseWidgetSize = FVector2D(ScreenResolution.X * 0.8, ScreenResolution.Y / 3);
	FVector2D ResponseWidgetPos = FVector2D(ScreenResolution.X * 0.1 , (ScreenResolution.Y / 3) * 2);

	FVector2D TopicWidgetSize = FVector2D(ScreenResolution.X * 0.4, ScreenResolution.Y * 0.4);
	FVector2D TopicWidgetPos = FVector2D(ScreenResolution.X * 0.8 - 325, ScreenResolution.Y * 0.4);

	
	ChildSlot
		[
			SNew(SCanvas)
			//--------------------------------------------
			//Background Image For Text Block
		+ SCanvas::Slot()
		//
		.Size(ResponseWidgetSize)
		.Position(ResponseWidgetPos)
		[
			SNew(SImage)
			//.ColorAndOpacity(FSlateColor(FLinearColor(1, 1, 1, 0.8)))
		.ColorAndOpacity(FSlateColor::FSlateColor(FLinearColor(FColor::Black.WithAlpha(100))))
		]
	+ SCanvas::Slot()
		.Size(ResponseWidgetSize)
		.Position(ResponseWidgetPos)
		[
			SNew(STextBlock)
			.Text(ResponseText)
			.TextStyle(&MenuStyle->DialogueTextStyle)
			.AutoWrapText(true)
		]
	//--------------------------------------------
	//Topic Widget
	+ SCanvas::Slot()
		//
		.Size(TopicWidgetSize)
		.Position(TopicWidgetPos)
		[
			SNew(SImage)
			.Visibility(TopicVisibility)
			.ColorAndOpacity(FSlateColor::FSlateColor(FLinearColor(FColor::Black.WithAlpha(150))))
		]
	+ SCanvas::Slot()
		.Size(TopicWidgetSize)
		.Position(TopicWidgetPos)
		[
			SAssignNew(TopicListBox, SVerticalBox)
				.Visibility(TopicVisibility)
				
				]
		];

	

	CurrentState = EDialogueState::Idle;
	SpeakHelloTopic();

	BuildAndShowMenu();
	UpdateHighlightedTopic();
	//FillRootTopics();


	//ResponseString = RootBranchList.Pop()->Topics.GetData()[0]->ResponseText;

 
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION




FReply SDialogueWidget::ToggleMenuClicked()
{
	OnToggleMenu.ExecuteIfBound();
	return FReply::Handled();
}



void SDialogueWidget::FillFromTopic(UTopic* topic)
{
	for (UTopic* Topic : topic->ChildrenTopics)
	{
		if (!Topic->bHello && Topic->IsActive())
		{
			CurrentTopicList.Add(Topic);
		}

	}
}
void SDialogueWidget::SpeakHelloTopic()
{
	for (UBranch* Branch : RootBranchList)
	{
		for (UTopic* Topic : Branch->Topics)
		{
			if (Topic->bHello && Topic->IsActive())
			{
				CurrentTopic = Topic;
				//this is where typewriter stuff would come into play
				//ResponseString = Topic->ResponseText;
				SpeakResponse();
				return;
			}
			
		}

	}

}

void SDialogueWidget::SpeakResponse()
{
	if (CurrentTopic)
	{
		CurrentState = EDialogueState::Speaking;
	
	
		ResponseString = CurrentTopic->ResponseText;
		ResponseDisplayString = "";
		TypeWriterIndex = 0;

		PC->TypeWriter(ResponseString,ResponseDisplayString,TypeWriterSpeed);
		CurrentTopic->StartScript();
		CurrentTopic->bSpoken = true;
	}

}


void SDialogueWidget::FillRootTopics()
{
	for (UBranch* Branch : RootBranchList)
	{
		for (UTopic* Topic : Branch->Topics)
		{
			if (!Topic->bHello && Topic->IsActive())
			{
				CurrentTopicList.Add(Topic);
			}
			
		}

	}

}

void SDialogueWidget::BuildAndShowMenu()
{
	if (CurrentState == EDialogueState::Idle)
	{

		CurrentTopicList.Empty();
		TopicListButtons.Empty();
		TopicListBox->ClearChildren();
	
		if (!bInsideBranch)
		{
			FillRootTopics();
		}
		else if (CurrentTopic && bInsideBranch)
		{
			FillFromTopic(CurrentTopic);
		}
		else
		{
			bInsideBranch = false;
			FillRootTopics();
		}

	
	
	
		if (CurrentTopicList.Num() > 0)
		{
			for (UTopic* Topic : CurrentTopicList)
			{
				TSharedPtr<class SButton> TempButton;
				if (Topic->IsActive())
				{
					TopicListBox->AddSlot()
						[
							SAssignNew(TempButton, SButton)
								.TextStyle(&MenuStyle->TopicTextStyle)
								.ButtonStyle(&MenuStyle->TopicButtonStyle)
								.Text(FText::FromString(Topic->TopicText))
						];

					if (TopicListButtons.Num() <= 0)
					{
						SelectedIndex = 0;
						CurrentIndex = 0;
					}

					TopicListButtons.Add(TempButton);

				}
			}
		}
		UpdateHighlightedTopic();
	
		/*
		TopicListBox->AddSlot()
			[
				SNew(SButton)
				.TextStyle(&MenuStyle->HeaderTextStyle)
				.ButtonStyle(&MenuStyle->TabButtonStyle)
				.Text(FText::FromString("Loot"))
				//.OnClicked(this, &SDialogueWidget::ShowLootClicked)
			];
	
		*/

		/*
		SNew(SButton)
		.TextStyle(&MenuStyle->HeaderTextStyle)
		.ButtonStyle(&MenuStyle->TabButtonStyle)
		.Text(FText::FromString("Loot"))
		.OnClicked(this, &SDialogueWidget::ShowLootClicked)
		*/

	}
	else
	{
		CurrentTopicList.Empty();
		TopicListButtons.Empty();
		TopicListBox->ClearChildren();
	}
}
void SDialogueWidget::UpdateHighlightedTopic()
{
	if ((CurrentIndex != SelectedIndex) && (TopicListButtons.Num() > 0))
	{
		if (!TopicListButtons.IsValidIndex(CurrentIndex))
		{
			CurrentIndex = 0;
			SelectedIndex = CurrentIndex;
		}
		//TopicListButtons.GetData()[CurrentIndex]->button
		TopicListButtons.GetData()[CurrentIndex]->SetButtonStyle(&MenuStyle->TopicButtonStyle);


		if (TopicListButtons.IsValidIndex(SelectedIndex))
		{
			CurrentIndex = SelectedIndex;
		}
		else
		{
			SelectedIndex = CurrentIndex;
		}
		TopicListButtons.GetData()[CurrentIndex]->SetButtonStyle(&MenuStyle->SelectedTopicButtonStyle);
	}
	else if (CurrentIndex == SelectedIndex && TopicListButtons.IsValidIndex(CurrentIndex))
	{
		TopicListButtons.GetData()[CurrentIndex]->SetButtonStyle(&MenuStyle->SelectedTopicButtonStyle);
	}
	else
	{
	
	}
}



void SDialogueWidget::ClickSelectedIndex()
{
	if (TopicListButtons.IsValidIndex(CurrentIndex) && CurrentTopicList.IsValidIndex(CurrentIndex))
	{
		//Enter Topic here!
		UTopic* temp = CurrentTopicList.GetData()[CurrentIndex];
		if (temp->IsActive())
		{
			CurrentTopic = temp;
			CurrentTopic->StartScript();
			//CurrentTopic = CurrentTopicList.GetData()[CurrentIndex];
			CurrentTopicList.Empty();
			TopicListButtons.Empty();
			TopicListBox->ClearChildren();
			SpeakResponse();
		}

		
		//this is where typewriter stuff would come into play, also when getting the hello topic
		//ResponseString = temp->ResponseText;
		//temp->StartScript();

		//TopicListButtons.GetData()[CurrentIndex]->ItemClicked();
	}
	//UpdateHighlightedTopic();
}


void SDialogueWidget::IncrementIndex()
{
	if (!(SelectedIndex >= TopicListButtons.Num()))
	{
		SelectedIndex++;
	}
	UpdateHighlightedTopic();
	/*
	*/


}

void SDialogueWidget::DecrementIndex()
{
	if (!(SelectedIndex < 0))
	{
		SelectedIndex--;
	}
	UpdateHighlightedTopic();

	/*
	*/
}



void SDialogueWidget::RebuildList()
{
	OnRebuildParent.ExecuteIfBound();
}
void SDialogueWidget::HideMenu()
{
	OnToggleMenu.ExecuteIfBound();
}

EVisibility SDialogueWidget::GetTopicVisibility() const
{
	if (CurrentTopicList.Num() > 0)
	{
		return EVisibility::Visible;
	}
	else
	{
		return EVisibility::Collapsed;
	}

	return EVisibility::Collapsed;
}

void SDialogueWidget::UpdateState()
{
	if (ResponseString == ResponseDisplayString && CurrentState == EDialogueState::Speaking)
	{
		CurrentState = EDialogueState::FinishedSpeaking;
		
		CurrentTopic->StopScript();

		if (CurrentTopic)
		{


			if (CurrentTopic->bGoodByeAfterScript)
			{
				OnToggleMenu.ExecuteIfBound();
			}
			else if (CurrentTopic->ChildrenTopics.Num() > 0)
			{
				bInsideBranch = true;
			}
			else if (CurrentTopic || bInsideBranch)
			{
				bInsideBranch = false;
				CurrentTopic = nullptr;
			}

			BuildAndShowMenu();
		}




	}
}

FText SDialogueWidget::GetResponse() const
{
	//FString out = "This is gonna be a text box full of stuff! woooooooooooooooooo!";
	//FString out = InventoryOwner->GetName();
	//out.Append(FString::FromInt(pt->GetAmmo(pt->GetCurrentItem().AmmoType)));
	//out.Append("");
	//out.Append(pt->GetCurrentItem().Name.ToString());

	//UpdateState();
	
	return FText::FromString(ResponseDisplayString);

}
/*
*/



FReply SDialogueWidget::OnFocusReceived(const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent)
{
	//return FReply::Handled().ReleaseMouseCapture().SetUserFocus(SharedThis(this), EFocusCause::SetDirectly, true);
	//return FReply::Handled().ReleaseMouseCapture().CaptureJoystick(SharedThis(this), true);
	//return FReply::Handled().ReleaseMouseCapture().SetUserFocus(SharedThis(this));
	return FReply::Handled();
}



FReply SDialogueWidget::OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
{
	FReply Result = FReply::Unhandled();
	const int32 UserIndex = InKeyEvent.GetUserIndex();
	
	if(PC->IsGameMenuUp())
	{
		const FKey Key = InKeyEvent.GetKey();
		
		//The main Menu Close
		//Start button, esc button, b button, no repeats
		if ((Key == EKeys::Escape || Key == EKeys::Gamepad_Special_Right ||Key == EKeys::Gamepad_FaceButton_Right || Key == EKeys::Global_Play || Key == EKeys::Global_Menu) && !InKeyEvent.IsRepeat())
		{
			OnToggleMenu.ExecuteIfBound();
			Result = FReply::Handled();
		}
		


		//-------------------------------------------------------------------------------
		//A Button, select topic or move to next branch or whatever, select
		else if (Key == EKeys::Gamepad_FaceButton_Bottom && !InKeyEvent.IsRepeat())
		{
			/*
			if (RootBranchList.Num() > 0)
			{
				UBranch* b = RootBranchList.Pop();
				ResponseString = b->Topics.GetData()[0]->ResponseText;
			}
			else
			{
				OnToggleMenu.ExecuteIfBound();
			}
			*/
			//OnToggleMenu.ExecuteIfBound();
			
			if (CurrentState == EDialogueState::Speaking)
			{
				PC->UpdateDelayTime(TypeWriterSpeed * 0.15);
				//wait until response is finished, else speed up the typewriter!
			}
			else if (CurrentState == EDialogueState::FinishedSpeaking)
			{
				CurrentState = EDialogueState::Idle;
				BuildAndShowMenu();
				UpdateHighlightedTopic();
			}
			else if (CurrentTopicList.Num() > 0)
			{
				ClickSelectedIndex();
			}
			else
			{
				OnToggleMenu.ExecuteIfBound();
			}
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
		.OnClicked(this, &SDialogueWidget::ToggleMenuClicked)
		]
		+ SVerticalBox::Slot()
		[
		SNew(SButton)
		.Text(FText::FromString("Quit Game"))
		.OnClicked(this, &SDialogueWidget::QuitGameClicked)
		]
		]
		]
		];




		*/
	}
	return Result;
}

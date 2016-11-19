// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "SpaceShooter.h"
#include "Characters/BaseTrainer.h"
#include "Characters/PlayerCharacterController.h"
#include "DialogueMenu.h"
#include "DialogueSystem/DialogueWidget.h"

void FDialogueMenu::UpdateDialogueState()
{
	if (GameMenuWidget.IsValid())
	{
		GameMenuWidget->UpdateState();

	}
}

void FDialogueMenu::Construct(APlayerCharacterController* _PC, AActor* _Other)
{
	PC = _PC;
	bIsGameMenuUp = false;

	if (!GEngine || !GEngine->GameViewport)
	{
		return;
	}
	
	//Construct the widget, lives in memory now!
	if (!GameMenuWidget.IsValid())
	{

		SAssignNew(GameMenuWidget, SDialogueWidget)
			.Speaker(_Other)
			.PC(PC)
			.Cursor(EMouseCursor::None)
		;
		GameMenuWidget->OnToggleMenu.BindSP(this,&FDialogueMenu::ToggleGameMenu);
	}
}

void FDialogueMenu::DetachGameMenu()
{

	if (GEngine && GEngine->GameViewport)
	{
		GEngine->GameViewport->RemoveViewportWidgetContent(GameMenuContainer.ToSharedRef());
		//FSlateApplication::Get().SetFocusToGameViewport();
		FSlateApplication::Get().SetUserFocusToGameViewport(0);
		if (PC)
		{
			// Make sure viewport has focus
			PC->SetGameMenuUp(false);
			FInputModeGameOnly Mode;
			PC->SetInputMode(Mode);
			PC->bShowMouseCursor = false;
			FSlateApplication::Get().SetAllUserFocusToGameViewport();
		}

	
	}
	bIsGameMenuUp = false;

}

void FDialogueMenu::ToggleGameMenu()
{
	
	if (!GameMenuWidget.IsValid())
	{
		return;
	}

	//Construct menu if not up already - widget lives in memory already (like current index/propertys) but not on viewport, this puts it up on the display
	if (!bIsGameMenuUp)
	{
		GEngine->GameViewport->AddViewportWidgetContent(
			SAssignNew(GameMenuContainer,SWeakWidget)
			.PossiblyNullContent(GameMenuWidget.ToSharedRef())
			);
		FSlateApplication::Get().SetKeyboardFocus(GameMenuWidget.ToSharedRef());
		GameMenuWidget->BuildAndShowMenu();
		//GameMenuWidget->RebuildList();
		bIsGameMenuUp = true;

		if (PC)
		{
			//PCOwner->SetCinematicMode(true, false, false, true, true);
			//PC->SetPause(true);
			//PC->bShowMouseCursor = true;
			PC->SetGameMenuUp(true);
			PC->bShowMouseCursor = false;
			FInputModeUIOnly Mode;
			Mode.SetWidgetToFocus(GameMenuWidget);
			PC->SetInputMode(Mode);
			//UVirtualCursorFunctionLibrary::EnableVirtualCursor(PC);
		}
		else
		{
			Lib::Msg("no pcowner?!");
		}
	} 
	else
	{
		DetachGameMenu();
	}
}
//#undef LOCTEXT_NAMESPACE

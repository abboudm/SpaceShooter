// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "SpaceShooter.h"
#include "Characters/BaseTrainer.h"
#include "Characters/PlayerCharacterController.h"
#include "Components/ClimbingPawnMovementComponent.h"
#include "IngameMenu.h"
#include "UI/Menu/InventoryWidget.h"

#include "VirtualCursor/VirtualCursorFunctionLibrary.h"
//#include "UI/ShooterHUD.h"

//#define LOCTEXT_NAMESPACE "ShooterGame.HUD.Menu"

void FIngameMenu::Construct(APlayerCharacterController* _PC)
{
	PC = _PC;
	bIsGameMenuUp = false;

	if (!GEngine || !GEngine->GameViewport)
	{
		return;
	}
	
	if (!GameMenuWidget.IsValid())
	{

		SAssignNew(GameMenuWidget, SInventoryWidget)
			.InventoryOwner(Cast<AActor>(PC->GetPawn()))
			//.Inventory(Cast<ABaseTrainer>(PC->GetPawn())->GetInventory())
			.Cursor(EMouseCursor::Default);
		/*
		SAssignNew(GameMenuWidget, SGameMenuWidget)
			//.PC(TWeakObjectPtr<ULocalPlayer>(PC))
			.PC(PC)
			.Cursor(EMouseCursor::Default);
			//.IsGameMenu(true);			
		*/
	
		//GameMenuWidget->MainMenu = GameMenuWidget->CurrentMenu = RootMenuItem->SubMenu;
		//GameMenuWidget->OnMenuHidden.BindSP(this,&FIngameMenu::DetachGameMenu);
		GameMenuWidget->OnToggleMenu.BindSP(this,&FIngameMenu::ToggleGameMenu);
		//GameMenuWidget->OnGoBack.BindSP(this, &FIngameMenu::OnMenuGoBack);
	}
}

void FIngameMenu::DetachGameMenu()
{
	if (GEngine && GEngine->GameViewport)
	{
		GEngine->GameViewport->RemoveViewportWidgetContent(GameMenuContainer.ToSharedRef());
		//FSlateApplication::Get().SetFocusToGameViewport();
		FSlateApplication::Get().SetUserFocusToGameViewport(0);
	}
	bIsGameMenuUp = false;

}

void FIngameMenu::ToggleGameMenu()
{
	//Update the owner in case the menu was opened by another controller
	//UpdateMenuOwner();

	if (!GameMenuWidget.IsValid())
	{
		return;
	}

	/*
	// check for a valid user index.  could be invalid if the user signed out, in which case the 'please connect your control' ui should be up anyway.
	// in-game menu needs a valid userindex for many OSS calls.
	if (GetOwnerUserIndex() == -1)
	{
		UE_LOG(LogShooter, Log, TEXT("Trying to toggle in-game menu for invalid userid"));
		return;
	}
	

	if (bIsGameMenuUp && GameMenuWidget->CurrentMenu != RootMenuItem->SubMenu)
	{
		GameMenuWidget->MenuGoBack();
		return;
	}
	*/
	//todo attached func
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
			UVirtualCursorFunctionLibrary::EnableVirtualCursor(PC);
		}
		else
		{
			Lib::Msg("no pcowner?!");
		}
	} 
	else
	{
		//Start hiding animation
		//GameMenuWidget->HideMenu();
		if (PC)
		{
			// Make sure viewport has focus
			//PC->SetPause(false);
			//PC->bShowMouseCursor = false;
			PC->SetGameMenuUp(false);
			UVirtualCursorFunctionLibrary::DisableVirtualCursor(PC);
			FSlateApplication::Get().SetAllUserFocusToGameViewport();
		}
		DetachGameMenu();
	}
}
//#undef LOCTEXT_NAMESPACE

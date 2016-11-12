
#pragma once
#include "SlateBasics.h"
#include "SlateExtras.h"
#include "Characters/PlayerCharacterController.h"

class FDialogueMenu : public TSharedFromThis<FDialogueMenu>
{
public:
	
	//void Construct();
	void Construct(APlayerCharacterController* PC, AActor* other);
	// toggles in game menu 
	void ToggleGameMenu();

	/** removes widget from viewport */
	void DetachGameMenu();

	void UpdateDialogueState();

protected:

	// Owning player controller
	APlayerCharacterController* PC;

	// game menu container widget - used for removing */
	TSharedPtr<class SWeakWidget> GameMenuContainer;

	// root menu item pointer
	//TSharedPtr<FShooterMenuItem> RootMenuItem;
	//TSharedPtr<FShooterMenuItem> MainMenuItem;

	// Game menu widget
	//TSharedPtr<class SGameMenuWidget> GameMenuWidget; 
	TSharedPtr<class SDialogueWidget> GameMenuWidget; 
	
	// if game menu is currently opened
	bool bIsGameMenuUp;
	

};

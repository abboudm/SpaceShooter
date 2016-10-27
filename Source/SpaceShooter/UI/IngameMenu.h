
#pragma once
#include "SlateBasics.h"
#include "SlateExtras.h"
#include "Characters/PlayerCharacterController.h"

class FIngameMenu : public TSharedFromThis<FIngameMenu>
{
public:
	
	//void Construct();
	void Construct(APlayerCharacterController* PC);
	// toggles in game menu 
	void ToggleGameMenu();



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
	TSharedPtr<class SInventoryWidget> GameMenuWidget; 
	
	// if game menu is currently opened
	bool bIsGameMenuUp;
	
	/** removes widget from viewport */
	void DetachGameMenu();

};


#pragma once
#include "SlateBasics.h"
#include "SlateExtras.h"
#include "Characters/PlayerCharacterController.h"

class FTradeMenu : public TSharedFromThis<FTradeMenu>
{
public:
	
	//void Construct();
	void Construct(APlayerCharacterController* PC,AActor* Trader);
	// toggles in game menu 
	void ToggleGameMenu();



protected:

	// Owning player controller
	APlayerCharacterController* PC;
	AActor* Trader;

	// game menu container widget - used for removing */
	TSharedPtr<class SWeakWidget> GameMenuContainer;

	// root menu item pointer
	//TSharedPtr<FShooterMenuItem> RootMenuItem;
	//TSharedPtr<FShooterMenuItem> MainMenuItem;

	// Game menu widget
	TSharedPtr<class STradeWidget> GameMenuWidget; 
	
	// if game menu is currently opened
	bool bIsGameMenuUp;
	
	/** removes widget from viewport */
	void DetachGameMenu();

};

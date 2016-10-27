// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "SpaceShooter.h"
#include "UI/IngameMenu.h"
#include "Characters/PlayerCharacterController.h"
#include "Characters/Trainer.h"
#include "UI/SpaceHUD.h"



APlayerCharacterController::APlayerCharacterController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bGameMenuUp = false;
	
}

void APlayerCharacterController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// UI input
	InputComponent->BindAction("InventoryMenu", IE_Pressed, this, &APlayerCharacterController::OnToggleInGameMenu);
	
}


void APlayerCharacterController::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	//FShooterStyle::Initialize();
}

void APlayerCharacterController::BeginPlay()
{
	Super::BeginPlay();	

	//Build menu only after game is initialized
	IngameMenu = MakeShareable(new FIngameMenu());
	//IngameMenu->Construct();
	//IngameMenu->Construct(Cast<ULocalPlayer>(Player));
	/*
	*/
	
	IngameMenu->Construct(this);

}

void APlayerCharacterController::OnToggleInGameMenu()
{
	if (IngameMenu.IsValid())
	{
		IngameMenu->ToggleGameMenu();
			
	}
	
}

bool APlayerCharacterController::IsGameMenuUp() { return bGameMenuUp; }
void APlayerCharacterController::SetGameMenuUp(bool isup) { bGameMenuUp = isup; }


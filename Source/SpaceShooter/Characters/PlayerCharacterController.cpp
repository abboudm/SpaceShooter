// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "SpaceShooter.h"
#include "UI/IngameMenu.h"
#include "UI/TradeMenu.h"
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


void APlayerCharacterController::ConstructAndShowTradeMenu(AActor* other)
{
	if (!IsGameMenuUp())
	{
		GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Red, other->GetName());
		TradeMenu = MakeShareable(new FTradeMenu());
		if (TradeMenu.IsValid())
		{
			TradeMenu->Construct(this, other);
			TradeMenu->ToggleGameMenu();

		}
	}
}

void APlayerCharacterController::OnToggleInGameMenu()
{
	if (!IsGameMenuUp())
	{
		if (IngameMenu.IsValid())
		{
			IngameMenu->ToggleGameMenu();

		}
	}
	else
	{
		if (IngameMenu.IsValid())
		{
			IngameMenu->DetachGameMenu();
		}
	}
}

bool APlayerCharacterController::IsGameMenuUp() { return bGameMenuUp; }
void APlayerCharacterController::SetGameMenuUp(bool isup) { bGameMenuUp = isup; }


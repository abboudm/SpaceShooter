// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "SpaceShooter.h"
#include "UI/IngameMenu.h"
#include "UI/TradeMenu.h"
#include "DialogueSystem/DialogueMenu.h"
#include "Characters/PlayerCharacterController.h"
#include "Characters/Trainer.h"
#include "UI/SpaceHUD.h"
#include "DialogueSystem/DialogueWidget.h"


void APlayerCharacterController::Typer()
{

	
	if (ResponseString != *DisplayString)
	{
	
		GEngine->AddOnScreenDebugMessage(-1, 0.5, FColor::Yellow, "typewriting");
		*DisplayString += ResponseString.GetCharArray().GetData()[TypeWriterIndex];
		TypeWriterIndex++;
		GetWorldTimerManager().SetTimer(TypeWriterHandle, this, &APlayerCharacterController::Typer, TypeWriterSpeed, false);
	}
	else
	{
		TypeWriterIndex = -1;
		ResponseString = "";
		DialogueMenu->UpdateDialogueState();
		//DialogueWidget->UpdateState();
	}
	/*

	if (ResponseString != ResponseDisplayString)
	{
		ResponseDisplayString += ResponseString.GetCharArray().GetData()[TypeWriterIndex];
		TypeWriterIndex++;
		UWorld* world = PC->GetWorld();
		if (world && TimerHandle_HandleTyping.IsValid())
		{

			//PC->GetWorldTimerManager().SetTimer(TimerHandle_HandleTyping, &SDialogueWidget::TypeResponseString, TypeWriterSpeed, false);
			//world->getworldtimer.SetTimer(this, &SDialogueWidget::TypeResponseString, TypeWriterSpeed, false);
			world->GetTimerManager().SetTimer(TimerHandle_HandleTyping, TypeWriterSpeed, false);
			TypeResponseString();
		}
		//PC->GetWorld()->GetTimerManager().SetTimer(TimerHandle_HandleTyping, this, &SDialogueWidget::TypeResponseString, TypeWriterSpeed, false);
	}
	else if (ResponseString == ResponseDisplayString)
	{
		CurrentState = EDialogueState::FinishedSpeaking;
		TypeWriterIndex = -1;

	}
	*/
	//add to the array
}

void APlayerCharacterController::TypeWriter(FString finalstring, FString& displaystring, float delaytime)
{
		DisplayString = &displaystring;
		ResponseString = finalstring;
		TypeWriterIndex = 0;
		TypeWriterSpeed = delaytime;
		GetWorldTimerManager().SetTimer(TypeWriterHandle, this, &APlayerCharacterController::Typer,TypeWriterSpeed, false);
	/*
	if (dialogue.IsValid())
	{
		DialogueWidget = dialogue;
	}
	*/

}



void APlayerCharacterController::UpdateDelayTime(float updatedtime)
{
	TypeWriterSpeed = updatedtime;

}



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


void APlayerCharacterController::ConstructDialogueMenu(AActor* other)
{
	if (!IsGameMenuUp())
	{
		//GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Red, other->GetName());
		DialogueMenu = MakeShareable(new FDialogueMenu());
		if (DialogueMenu.IsValid())
		{
			DialogueMenu->Construct(this, other);
			DialogueMenu->ToggleGameMenu();

		}
	}
}


void APlayerCharacterController::ConstructAndShowTradeMenu(AActor* other)
{
	if (!IsGameMenuUp())
	{
		//GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Red, other->GetName());
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


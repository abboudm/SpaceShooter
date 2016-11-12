// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "PlayerCharacterController.generated.h"

class AShooterHUD;

UCLASS(config=Game)
class APlayerCharacterController : public APlayerController
{
	GENERATED_UCLASS_BODY()

public:

	void ConstructAndShowTradeMenu(AActor* other);
	void ConstructDialogueMenu(AActor* other);
	
	
	//--------------------------------------
	//TyperWriter
	int TypeWriterIndex;
	float TypeWriterSpeed;
	FString ResponseString;
	FString *DisplayString;


	FTimerHandle TypeWriterHandle;
	
	//TSharedPtr<class SDialogueWidget> DialogueWidget;
	//SDialogueWidget* DialogueWidget;
	void TypeWriter(FString finalstring, FString& displaystring, float delaytime);
	void Typer();
	void UpdateDelayTime(float updatedtime);

	//--------------------------------------

	void OnToggleInGameMenu();
	bool IsGameMenuUp();
	void SetGameMenuUp(bool isup);
protected:

	
	TSharedPtr<class SWeakWidget> GameMenuContainer;
	//TSharedPtr<class SInventoryUI> InventoryUI;
	//TSharedPtr<class FShooterIngameMenu> ShooterIngameMenu;
	//virtual void TickActor(float DeltaTime, enum ELevelTick TickType, FActorTickFunction& ThisTickFunction) override;
	
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	bool bGameMenuUp;
	TSharedPtr<class FIngameMenu> IngameMenu;
	TSharedPtr<class FTradeMenu> TradeMenu;
	TSharedPtr<class FDialogueMenu> DialogueMenu;

	/** Handle for efficient management of ClientStartOnlineGame timer */
	//imerHandle TimerHandle_ClientStartOnlineGame;
};


// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceShooter.h"
#include "Characters/PlayerCharacterController.h"
#include "UI/SpaceHUD.h"
#include "SpaceShooterGameMode.h"

ASpaceShooterGameMode::ASpaceShooterGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/Characters/PlayerCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	HUDClass = ASpaceHUD::StaticClass();
	PlayerControllerClass = APlayerCharacterController::StaticClass();
}

	/*
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnOb(TEXT("/Game/Blueprints/Characters/PlayerCharacter"));
	DefaultPawnClass = PlayerPawnOb.Class;
	
	
	HUDClass = AShooterHUD::StaticClass();
	PlayerControllerClass = AShooterPlayerController::StaticClass();
	PlayerStateClass = AShooterPlayerState::StaticClass();
	SpectatorClass = AShooterSpectatorPawn::StaticClass();
	GameStateClass = AShooterGameState::StaticClass();
	ReplaySpectatorPlayerControllerClass = AShooterDemoSpectator::StaticClass();
	*/


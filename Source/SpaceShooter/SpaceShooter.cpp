// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceShooter.h"
#include "UI/Styles/MenuStyles.h"

class FSpaceShooterGameModule : public FDefaultGameModuleImpl
{
	virtual void StartupModule() override
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(FMenuStyles::GetStyleSetName());
		FMenuStyles::Initialize();
	}

	virtual void ShutdownModule() override
	{
		FMenuStyles::Shutdown();
	}
};

//DEFINE_LOG_CATEGORY(SpaceShooter);
IMPLEMENT_PRIMARY_GAME_MODULE( FSpaceShooterGameModule, SpaceShooter, "SpaceShooter" );

//IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, SpaceShooter, "SpaceShooter" );

 
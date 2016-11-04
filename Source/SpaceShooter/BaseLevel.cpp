
#include "SpaceShooter.h"
#include "BaseLevel.h"

//ABaseLevel::ABaseLevel(const class FPostConstructInitializeProperties& PCIP) : Super(PCIP)
ABaseLevel::ABaseLevel(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	//SolusLevelName = NAME_None;
}

//Actor.h 		ReceiveBeginPlay()
void ABaseLevel::BeginPlay()
{
	Super::BeginPlay();
	//~~~~~~~~~~

	//UE_LOG(YourLog,Error,TEXT("STREAMING LEVEL BEGIN PLAY %s"), *GetName());
}



void ABaseLevel::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	//UE_LOG(YourLog,Error,TEXT("STREAMING LEVEL UNSTREAMED (name should not be none) %s"), *GetName());
	//UE_LOG(YourLog,Error,TEXT("Victory!!!"));
	//UE_LOG(YourLog,Error,TEXT("RUN ALL UNSTREAMING LEVEL LOGIC HERE"));

	//Super::OnRemoveFromWorld();
}

void ABaseLevel::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	//UE_LOG(YourLog,Warning,TEXT("Level Name Is: %s"), *SolusLevelName);
}

void ABaseLevel::TestCommand()
{
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, "CustomConsoleCommands!");
}
/*
*/
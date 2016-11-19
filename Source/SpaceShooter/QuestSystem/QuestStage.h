// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
//#include "GameFramework/Pawn.h"
//#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#include "Runtime/CoreUObject/Public/UObject/UObject.h"
#include "QuestStage.generated.h"



UCLASS(Blueprintable, BlueprintType, Abstract)
class SPACESHOOTER_API UQuestStage : public UObject
{
	GENERATED_BODY()

public:

	UQuestStage(const FObjectInitializer& ObjectInitializer);



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stage")
		int Index;
		
	//	-this runs on quest start, even if the quest is activated by SetStage() and its setting a stage other than the marked startup stage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stage")
		bool bStartupStage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stage")
		bool bShutdownStage;
	
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stage")
		//TArray<UStageItems* > StageItems;
	
	UFUNCTION(BlueprintNativeEvent, meta = (DisplayName = "Stage - Is Active"))
		bool IsActive();

	FORCEINLINE bool IsActive_Implementation() { return true; }


	/*
	QuestStageItems
	{
		LogEntry	-this is the string like "I helped out Lydia find her Dragonborn helmet" aka the quest summary/log entry
		ResultScript	-this has conditionals, and when this stage is activated, it runs those conditionals. if true, run the attached script
					-example would be having a Kill or Protect Character objective, the associated Stage would then run conditionals on whether the player saved/kill the target. 
					then it would set the next stage, and make the appropriate log entry/objective complete
		Conditionals	-a system/struct in of itself, that has a {DataType, Desired Result} so conditoinals can be aactors/locations/etcetcetc
		bComplete	-mark quest as completed if this stage runs
		bFailed		-mark quest as failed if this stage runs
	}
	*/

	
};

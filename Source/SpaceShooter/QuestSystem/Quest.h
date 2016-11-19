// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
//#include "GameFramework/Pawn.h"
//#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#include "Runtime/CoreUObject/Public/UObject/UObject.h"
#include "Quest.generated.h"



/*
UENUM(BlueprintType)
enum class EQuestType : uint8
{
	Normal,
	TopLevel,
	Blocking,
};
*/

/*

//UPROPERTY(EditDefaultsOnly, Category "Item")
//TSubclassOf<class AEquipablePickup> LootCompanion; //this is the Item->Loot class that would drop from the final product class aka BattleRifle_instanthit <-> BattleRifle_loot

UCLASS(Blueprintable, BlueprintType)

UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
class USkeletalMeshComponent* Mesh;

UFUNCTION(BlueprintNativeEvent, meta = (DisplayName = "OnPrimaryTrigger"))
void ReceiveOnPrimaryTrigger();

void AEquipable::ReceiveOnPrimaryTrigger_Implementation() { this->OnPrimaryTrigger(); }
void AEquipable::OnPrimaryTrigger() {}

UFUNCTION(BlueprintCallable, Category = "Equipable")

class ABaseTrainer* GetPawnOwner() const;
*/



UCLASS(Blueprintable, BlueprintType, Abstract)
class SPACESHOOTER_API UQuest : public UObject
{
	GENERATED_BODY()

public:

	UQuest(const FObjectInitializer& ObjectInitializer);





  //Complete the quest
  UFUNCTION(BlueprintCallable, Category = "Quest")
    void CompleteAllObjectives();
  UFUNCTION(BlueprintCallable, Category = "Quest")
    void CompleteQuest();
  UFUNCTION(BlueprintCallable, Category = "Quest")
    void FailAllObjectives();


    //Get Stuff
    //Alias GetAlias(int aliasID);
  UFUNCTION(BlueprintCallable, Category = "Quest")
    int GetCurrentStageID(); //obtain highest completed stage on this quest
  UFUNCTION(BlueprintCallable, Category = "Quest")
    int GetStage();
  UFUNCTION(BlueprintCallable, Category = "Quest")
    bool GetStageDone(int stageID);
  UFUNCTION(BlueprintCallable, Category = "Quest")
    int GetObjectiveDisplayed();


    //is stuff
  UFUNCTION(BlueprintCallable, Category = "Quest")
    bool IsActive(); //is this quest active
  UFUNCTION(BlueprintCallable, Category = "Quest")
    bool IsCompleted();
  UFUNCTION(BlueprintCallable, Category = "Quest")
    bool IsObjectiveCompleted(int objectiveID);
  UFUNCTION(BlueprintCallable, Category = "Quest")
    bool IsObjectiveDisplayed(int objectiveID);
  UFUNCTION(BlueprintCallable, Category = "Quest")
    bool IsObjectiveFailed(int objectiveID);
  UFUNCTION(BlueprintCallable, Category = "Quest")
    bool IsRunning();
  UFUNCTION(BlueprintCallable, Category = "Quest")
    bool IsStageDone(int stageID);
  UFUNCTION(BlueprintCallable, Category = "Quest")
    bool IsStarting();
  UFUNCTION(BlueprintCallable, Category = "Quest")
    bool IsStopping(); //checks if its marked active/inactive yet still notrunning/running


    //not needed? bool modobjectiveglobal(float modvalue, globalvariable modglobal, int objectiveid, float targetvalue , bool countingup, bool completeobjective, bool redisplayobjective);
  UFUNCTION(BlueprintCallable, Category = "Quest")
    void SetActive(bool Active);
  UFUNCTION(BlueprintCallable, Category = "Quest")
    bool SetCurrentStageID(int stageID); //sets quest to stage, returns bool if succeed
  UFUNCTION(BlueprintCallable, Category = "Quest")
    void SetObjectiveCompleted(int objectiveID, bool completed);
  UFUNCTION(BlueprintCallable, Category = "Quest")
    void SetObjectiveDisplayed(int objectiveID, bool Displayed);
  UFUNCTION(BlueprintCallable, Category = "Quest")
    void SetObjectiveFailed(int objectiveID, bool failed);
  UFUNCTION(BlueprintCallable, Category = "Quest")
    bool SetStage(int stageID); // same as setstageid



    //quest manager handlers
  UFUNCTION(BlueprintCallable, Category = "Quest")
	void Start();
  UFUNCTION(BlueprintCallable, Category = "Quest")
    void Stop();
  UFUNCTION(BlueprintCallable, Category = "Quest")
    void Reset();
    //bool UpdateCurrentInstanceGlobal(GlobalVariable aUpdateGlobal);



/*
QuestManager

  Quest
    Quest Data
    Quest Alias
    Quest Dialogue
    QuestStage
    Quest Objectives
    Conditionals
    */


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
		FName Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
		int ID;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
		//EQuestType QuestType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
		int Priority;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
		//EActivationEvent ActivationType
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
		bool bRunOnce;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
		bool bGameStart;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
		bool bAllowedRepeatStages;
	
	UFUNCTION(BlueprintNativeEvent, meta = (DisplayName = "Quest - Is Active"))
		bool IsActive();

	FORCEINLINE bool IsActive_Implementation() { return true; }




	
	




	//UPROPERTY(BlueprintReadOnly, Category = "Quest")
		//TArray<UTopic* > Topics;

	

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest", meta = (AllowPrivateAccess = "true"))
		//TArray<TSubclassOf<class UTopic>> TopicClasses;
	
};

/*
----------------------------------------------------------------------------------------------------------------
QuestManager

  Quest
    Quest Data
    Quest Alias
    Quest Dialogue
    QuestStage
    Quest Objectives
    Conditionals
---------------------------------------------------------------------------------------------------------------------------------------------------------------------
QuestData
{
	Name
	ID		- like GSQ001 or something unique
	Type 		- misc/side/deadric quest
	Priority	- this would affect dialogue, and push higher priorty quest dialogue up the list
	Event		- this is the activation event, can be NONE or a specific Event
		if None
			this quest doesn't start up until a script manually calls ID.StartQuest() or ID.SetStage(int)
		if Event
			the story manager adds conditionals and checks in an update/tick function. ideas for this, type it later
			example events:
				increase Level, steal item, pickup item, location change, load level, get arrested, get caught sneaking, kill actor, damage actor, etcetcetc

	Bools
		bGameStart	- if no event specified && this is true, the quest starts at the beginning of the game
		bRunOnce
		bAllowedRepeatStages
	TArray<DialogeConditions>	-comeback to this, unimportant now
}

---------------------------------------------------------------------------------------------------------------------------------------------------------------------
QuestStage
{

	int Index	-stage 0, stage 10, stage 20, etcetc, bethesda uses increments of 10, so if later you want to add something, like a sub stage, you could add stage 11 or something (i dont quite agree/understand this convention)
	bStartupStage	-this runs on quest start, even if the quest is activated by SetStage() and its setting a stage other than the marked startup stage
	bShutdownStage	-same thing, but on shutdown/finished quest
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
}

---------------------------------------------------------------------------------------------------------------------------------------------------------------------
Conditionals
{
	Animations
	DialogueSpoken
	AIPackages/Behaviors
	QuestStages
	QuestObjectives
	Quests
	AActors and other UObjects
	FVector and other data types
}


---------------------------------------------------------------------------------------------------------------------------------------------------------------------
Quest Objectives
{
	Index
	DisplayText
	bORedPrevious	-if true, it combines the previous objective
				-example: Objective(1) = Kill Billy, Objective(2)(bOred=true) = Save Billy
						-result = Kill Billy OR Save Billy
	QuestTarget	-this is the map marker/waypoint that is then set
}

---------------------------------------------------------------------------------------------------------------------------------------------------------------------
Quest Alias
{
	AliasType	-Reference Alias || Location Alias
	Alias Name / ID
	DisplayName
	Various bools 	-essential,unique,optional,allowed
}
ReferenceAliasType
{
	TemplateActor	- a template of an actor, would then set stuff like (inventory, ai level, etc etc, think bandits or thieves)
	Unique Actor 	- a specific actor	(think lydia or King of Whiterun)
	Specific Ref 	-a specific actor, but hardcoded, couldn't be modified by the Quest/Story Manager (difference is unique actor could have conditionals saying anyone of these uniques are good, where specific is this and only this actor)
	
	Alias Data
		Scripts
		Inventory
		Spells/Weapons
}
---------------------------------------------------------------------------------------------------------------------------------------------------------------------
*/


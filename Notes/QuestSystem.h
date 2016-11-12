----------------------------------------------------------------------------------------------------------------

//UFUNCTION(BlueprintCallable, Category "QuestSystem")
void CompleteAllObjectives();
void CompleteQuest();
void FailAllObjectives();
Alias GetAlias(int aliasID);
int GetCurrentStageID(); //obtain highest completed stage on this quest
int GetStage();
bool GetStageDone(int stageID);
int GetObjectiveDisplayed();
bool IsActive(); //is this quest active
bool IsCompleted();
bool IsObjectiveCompleted(int objectiveID);
bool IsObjectiveDisplayed(int objectiveID);
bool IsObjectiveFailed(int objectiveID);
bool IsRunning();
bool IsStageDone(int stageID);
bool IsStarting();
bool Is Stopping(); //checks if its marked active/inactive yet still notrunning/running
//not needed? bool modobjectiveglobal(float modvalue, globalvariable modglobal, int objectiveid, float targetvalue , bool countingup, bool completeobjective, bool redisplayobjective);
void Reset();
void SetActive(bool Active);
bool SetCurrentStageID(int stageID); //sets quest to stage, returns bool if succeed
void SetObjectiveCompleted(int objectiveID, bool completed);
void SetObjectiveDisplayed(int objectiveID, bool Displayed);
void SetObjectiveFailed(int objectiveID, bool failed);
bool SetStage(int stageID); // same as setstageid
bool Start();
void Stop();
//bool UpdateCurrentInstanceGlobal(GlobalVariable aUpdateGlobal);




---------------------------------------------------------------------------------------------------------------------------------------------------------------------
struct FResponse
{
  FString Text;
  //etc bools to determine emotions/voice to play/animations
};


class Info
{
  FString TopicText; //set by the owning topic
  FString Prompt;      //this is the dialogue choice to make; what the player says. uses topictext if this is blank

  UFUNCTION(BlueprintImplementable) //BlueprintNative lets c++ write a _Implementation function and blueprint can call parent/write its own. infos tho are a blueprint level class, so no c++ stuff here! could easily add if needed later
    OnResponseStart();

  UFUNCTION(BlueprintImplementable) //BlueprintNative lets c++ write a _Implementation function and blueprint can call parent/write its own. infos tho are a blueprint level class, so no c++ stuff here! could easily add if needed later
    OnResponseEnd();

  TArray<FResponse>;
  TArray<Conditionals>;

  //various bools

}



class Topic
{

  FString ID;
  FString TopicText;//pointless if a child info has a prompt
  int Priority; //this determines the order of the topics listed

}


class Branch
{


}








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

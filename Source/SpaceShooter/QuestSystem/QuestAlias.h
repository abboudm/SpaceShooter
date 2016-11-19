// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
//#include "GameFramework/Pawn.h"
//#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#include "Runtime/CoreUObject/Public/UObject/UObject.h"
#include "QuestAlias.generated.h"




UCLASS(Blueprintable, BlueprintType, Abstract)
class SPACESHOOTER_API UQuestAlias : public UObject
{
	GENERATED_BODY()

public:

	UQuestAlias(const FObjectInitializer& ObjectInitializer);

	
	//EAliasFillType FillType
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QuestAlias")
		TSubclassOf<class ABaseTrainer> CharacterRef;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QuestAlias")
		FName Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QuestAlias")
		int ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QuestAlias")
		FName DisplayName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QuestAlias")
		bool bEssential;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QuestAlias")
		bool bUnique;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QuestAlias")
		bool bOptional;
	
	
	
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
	
	

};

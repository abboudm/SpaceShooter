
#include "SpaceShooter.h"
#include "DialogueSystem/Topic.h"
#include "Branch.h"

UBranch::UBranch(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	//MaxAnalogCursorSpeed = 1300.0f;
	//AnalogCursorAccelerationCurve.EditorCurveData.AddKey(0, 0);
	//AnalogCursorAccelerationCurve.EditorCurveData.AddKey(1, 1);

}


UTopic* UBranch::SetupTopic(UObject* Outer, TSubclassOf<class UTopic> TopicClass)
{


	//Depreceated! use NewObject! too lazy to figure out outer class - easy, just add it as a parameter to the construct()
	//when you create the branch object it would be 
	//branch* newobject(outer,branch);
	//branch->construct(outer);
	//UTopic* out = NewObject<UTopic>(Outer, TopicClass);
	//UTopic* out = ConstructObject<UTopic>(TopicClass);
	
	UTopic* out = NewObject<UTopic>(Outer, TopicClass);
	out->Parent = Owner;
	if (out)
	{
		for (TSubclassOf<class UTopic> ChildTopicClass : out->ChildrenTopicClasses)
		{
			out->ChildrenTopics.Add(SetupTopic(Outer, ChildTopicClass));
		}
	}
	/*
	*/
	return out;
}

void UBranch::Construct(AActor* ActorOwner, UWorld* world)
{
	/*
	ChildrenTopics
		ChildrenTopicClasses
		TopicClasses
		Topics
	*/
	Owner = ActorOwner;
	World = world;
	UObject* Outer = Owner;
	for (TSubclassOf<class UTopic> TopicClass : TopicClasses)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Red, "Iterating the topic classes!");
		//UTopic* out = NewObject<UTopic>(Outer, TopicClass);
		
		Topics.Add(SetupTopic(Outer,TopicClass));

		//Topics.Add(SetupTopic(Outer, TopicClass->GetClass()));
		//Topics.Add(SetupTopic(Cast<UToTopicClass);
	}
}
/*
QuestManager.h
QuestInterface.h

Quest.h
Objective.h
Stage.h
QuestWidget.h
QuestMenu.h

Branch.h
Topic.h
TopicInfo.h
DialogueView.h
DialogueWidget.h
DialogueMenu.h


-----------------------------
Dialogue Handling 
-----------------------------
Quests Store Dialogue View(s) 
	Could have multiple views for a single quest, but each one has actor references
	so if a dialogueQuery, it would get all relavent views from each quest
	conditions for speakers could be specific/has other tags/class or whatever
	
	
Actors Store a single Dialogue View - could be empty
	has any specific/unique dialogue options
	these could have lots of conditions like "if quest x is complete" or whatever
	but these would never have relation to quests
	like these wouldn't start a quest, it would just be random chatter
	specifically, a sign post is an example - no relation to quests

Quest/Stage/Objective/Topics/etc have ScriptNodes that fire
	blueprints implement the scriptnodes logic / add conditionals
	they return/fire QuestInterface messages 

Player interacts with a dialouge interactable

so in ATrainer, in ActionX(), for case Character & interacts Dialogue
	
	PC->Spaek(reachableActor);

*/

void APlayerController::Speak(AActor* OtherActor)
{
	TArray<UDialogueView> questviews = QuestManager->GetViews(otherActor->getID());
	questviews.add(otherActor->getDialougeView());
	//Setup input to point to UI
	//Construct Speaking Menu
	DialogueWidget->Construct(this,OtherActor,questviews);
}
/*
dialogueresponse style
getattribute stringdisplay first branches topic responseelse if more than one, display first topic marked hello

on button press, move to next topic
if at the end of topics, togglemenu 
*/




/*

	DialogueWidget
		for each view, find any root views
			these would be blocking/forcegreets, ignore for now
			
		if no roots
			GetHelloPhrase
				Could come from player view, like "hey its me, zaphod!"
				could come from quest views, "omg, its the dragonborn!"
				could come from quest views, which are just dialogue views, like peasant talks, "the rain sucks!"
			Display HelloPhrase with highest priority, or random if matching priorities
				*again, blocking would be different, but ignore for now*
			
			***the attribute "RESPONSE" is now set, the widget is now showing it to the player
			------------------------------------------------------------------------------------
			
			
			
			
			FString ResponseString;
			
			TArray<FString> TopicStrings;
			
			TArray<UBranch*> RootBranchs;
			
			
			UBranch* 		 CurrentBranch;
			TArray<UTopic*> CurrentTopics;
			
			void RebuildMenu
			{
				
				
				//Inside a Branch of conversation
				if (CurrentBranch)
				{
					TopicStrings.empty();
					for(CurrentBranch.gettopics()
					
					
					
					
					
				}
				else if (RootBranches.Num() > 0)
				{
					CurrentTopics.empty();
					For each RootBranch
						CurrentTopics.add(rootbranch->getRootTopic);
					
					
					
					
					
					
					
					
					
				}

			
			}
			
			
			
			Construct{
				
			}
			
			
			OnButtonPress{
				if valid topics
					b button destroys dialogue, says goodbye (no widget, only audio/subtitle)
					up/down moves selector over topics
					a button click the selected topic
				else if !topics && response
					click a to move on
						if 
				
				
				
			}
			
			
			
			
			
			
			
			
			
			



*/
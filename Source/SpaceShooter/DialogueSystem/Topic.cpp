
#include "SpaceShooter.h"
#include "DialogueSystem/TopicInfo.h"
#include "Topic.h"

UTopic::UTopic(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	//---------------------------------------------------------------------------	

	bDoAllBeforeRepeating = false;
	bSpoken = false;
	bHello = false; //mark if its a hello topic...should this be in info instead?
	bGoodByeAfterScript = false;
	bAutoConfirm = false;
	bOverrideTypeWriterSpeed = false;
	TypeWriterSpeed = 0.25;


}
FString UTopic::GetTopicText()
{
	FString out = "";

	for (UTopicInfo* Info : Infos)
	{
		if (Info->IsActive() && Info->HasPrompt())
		{
			out = Info->GetPrompt();
		}
	}


	if (out == "")
	{
		out = TopicText;
	}

	return out;
}

FString UTopic::GetTopicResponse()
{
	FString out = "";
	for (UTopicInfo* Info : Infos)
	{
		if (Info->IsActive() && Info->HasResponse())
		{
			out = Info->GetResponse();
			break;
		}
	}


	if (out == "")
	{
		out = ResponseText;
	}

	return out;

}

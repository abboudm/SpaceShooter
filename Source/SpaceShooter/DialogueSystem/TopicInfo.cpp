
#include "SpaceShooter.h"
#include "TopicInfo.h"

UTopicInfo::UTopicInfo(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	//MaxAnalogCursorSpeed = 1300.0f;
	//AnalogCursorAccelerationCurve.EditorCurveData.AddKey(0, 0);
	//AnalogCursorAccelerationCurve.EditorCurveData.AddKey(1, 1);

}

FString UTopicInfo::GetResponse()
{
	FString out = "";
	if (Responses.Num() > 0)
	{
		out = Responses.GetData()[0].Response;
	}

	return out;
}

FString UTopicInfo::GetPrompt()
{
	return Prompt;
}

bool UTopicInfo::HasPrompt()
{
	bool p = (Prompt != "");
	return p;
}

bool UTopicInfo::HasResponse()
{
	bool p = (Responses.Num() > 0);
	return p;
}
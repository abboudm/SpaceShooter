
#include "SpaceShooter.h"
#include "Quest.h"

UQuest::UQuest(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	//MaxAnalogCursorSpeed = 1300.0f;
	//AnalogCursorAccelerationCurve.EditorCurveData.AddKey(0, 0);
	//AnalogCursorAccelerationCurve.EditorCurveData.AddKey(1, 1);

}
void UQuest::CompleteAllObjectives()
{

}
void UQuest::CompleteQuest()
{

}
void UQuest::FailAllObjectives()
{

}


int UQuest::GetCurrentStageID()
{
  

  return 0;
}
int UQuest::GetStage()
{

  return 0;
}
bool UQuest::GetStageDone(int stageID)
{

  return false;
}
int UQuest::GetObjectiveDisplayed()
{

  return 0;
}


bool UQuest::IsActive()
{

  return false;
}
bool UQuest::IsCompleted()
{
  return false;

}
bool UQuest::IsObjectiveCompleted(int objectiveID)
{

  return false;
}
bool UQuest::IsObjectiveDisplayed(int objectiveID)
{

  return false;
}
bool UQuest::IsObjectiveFailed(int objectiveID)
{

  return false;
}
bool UQuest::IsRunning()
{

  return false;
}
bool UQuest::IsStageDone(int stageID)
{

  return false;
}
bool UQuest::IsStarting()
{

  return false;
}
bool UQuest::IsStopping()
{

  return false;
}


void UQuest::SetActive(bool Active)
{

}
bool UQuest::SetCurrentStageID(int stageID)
{

  return false;
}
void UQuest::SetObjectiveCompleted(int objectiveID, bool completed)
{

}
void UQuest::SetObjectiveDisplayed(int objectiveID, bool Displayed)
{

}
void UQuest::SetObjectiveFailed(int objectiveID, bool failed)
{

}
bool UQuest::SetStage(int stageID)
{

  return false;
}



void UQuest::Start()
{

}
void UQuest::Stop()
{

}
void UQuest::Reset()
{

}



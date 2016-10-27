//Copyright (c) 2016 Artem A. Mavrin and other contributors

#pragma once

#include "SpaceShooter.h"

#include "DialogueSystem/DialogueSystemPrivatePCH.h"
#include "DialogueSettings.h"

bool ADialogueSettings::GetPropertyBoolValue(FString ValueName)
{
	FName TheName(*ValueName);
	UBoolProperty* BoolProp = FindField<UBoolProperty>(GetClass(), TheName);
	if (BoolProp != NULL)
	{
		return BoolProp->GetPropertyValue_InContainer(this);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No %s Propery!"), *ValueName);
		return false;
	}
}

void ADialogueSettings::SetPropertyBoolValue(FString ValueName, bool NewValue)
{
	FName TheName(*ValueName);
	UBoolProperty* BoolProp = FindField<UBoolProperty>(GetClass(), TheName);
	if (BoolProp != NULL)
	{
		BoolProp->SetPropertyValue_InContainer(this, NewValue);
	}
}

TArray<FString> ADialogueSettings::GetBoolVariables()
{
	TArray<FString> Result;
	Result.Add("None");
	for (TFieldIterator<UBoolProperty> PropIt(GetClass(), EFieldIteratorFlags::IncludeSuper); PropIt; ++PropIt)
	{
		UBoolProperty* Property = *PropIt;
		int32 Index = Property->GetFullName().Find(FString(TEXT("/Script/Engine.Actor")));
		if (Index == INDEX_NONE)
		{
			
			Result.Add(Property->GetName());
		}
	}

	return Result;
}

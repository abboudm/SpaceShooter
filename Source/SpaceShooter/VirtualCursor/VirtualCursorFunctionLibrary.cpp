// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "SpaceShooter.h"
#include "VirtualCursor/GameGlobals.h"
#include "VirtualCursor/GameAnalogCursor.h"
#include "VirtualCursorFunctionLibrary.h"

void UVirtualCursorFunctionLibrary::EnableVirtualCursor(class APlayerController* PC)
{
	FGameAnalogCursor::EnableAnalogCursor(PC, TSharedPtr<SWidget>());
}

void UVirtualCursorFunctionLibrary::DisableVirtualCursor(class APlayerController* PC)
{
	FGameAnalogCursor::DisableAnalogCursor(PC);
}


bool UVirtualCursorFunctionLibrary::IsCursorOverInteractableWidget()
{
	TSharedPtr<FGameAnalogCursor> Analog = GetDefault<UGameGlobals>()->GetAnalogCursor();
	if ( Analog.IsValid() )
	{
		return Analog->IsHovered();
	}

	return false;
}

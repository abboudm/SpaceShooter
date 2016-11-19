// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
//#include "GameFramework/Pawn.h"
//#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#include "Runtime/CoreUObject/Public/UObject/UObject.h"
#include "QuestObjective.generated.h"

UCLASS(Blueprintable, BlueprintType, Abstract)
class SPACESHOOTER_API UQuestObjective : public UObject
{
	GENERATED_BODY()

public:

	UQuestObjective(const FObjectInitializer& ObjectInitializer);

	
	
	UFUNCTION(BlueprintNativeEvent, meta = (DisplayName = "Objective - Is Active"))
		bool IsActive();

	FORCEINLINE bool IsActive_Implementation() { return true; }
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objective")
		int Index;	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objective")
		FString DisplayText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objective")
		bool bORedPrevious;
				//-if true, it combines the previous objective
				//-example: Objective(1) = Kill Billy, Objective(2)(bOred=true) = Save Billy
						//-result = Kill Billy OR Save Billy
	
	
	//QuestTarget	-this is the map marker/waypoint that is then set
}


};

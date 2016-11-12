
#pragma once
#include "Runtime/CoreUObject/Public/UObject/UObject.h"

#include "TopicInfo.generated.h"

UCLASS()
class SPACESHOOTER_API UTopicInfo : public UObject
{
	GENERATED_BODY()

public:

	UTopicInfo(const FObjectInitializer& ObjectInitializer);
	
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Topic")
		FString TopicText; //inherited from topics topic text
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TopicInfo")
		FString Prompt;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TopicInfo")
		TArray<FString> Responses; //should use FResponse instead, that would hold animations/other data
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TopicInfo")
		TArray<AActor*> Conditions;
		
	/*
	UFUNCTION(BlueprintImplementable)
		void BeginScript();
	UFUNCTION(BlueprintImplementable)
		void EndScript();
	*/
	
private:


	//
	
	
};
	
	
	
	
	
	
	
	
	
	
	


#pragma once
#include "Runtime/CoreUObject/Public/UObject/UObject.h"

#include "TopicInfo.generated.h"


USTRUCT(BlueprintType)
struct FResponse
{
	GENERATED_USTRUCT_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Response;

};



UCLASS(Blueprintable, BlueprintType, Abstract)
class SPACESHOOTER_API UTopicInfo : public UObject
{
	GENERATED_BODY()

public:

	UTopicInfo(const FObjectInitializer& ObjectInitializer);
	
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TopicInfo")
		FString Prompt;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TopicInfo")
		TArray<FResponse> Responses; //should use FResponse instead, that would hold animations/other data
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TopicInfo")
		TArray<AActor*> Conditions;


	UFUNCTION(BlueprintCallable, Category = "TopicInfo")
		bool HasResponse();
	UFUNCTION(BlueprintCallable, Category = "TopicInfo")
		bool HasPrompt();

	UFUNCTION(BlueprintCallable, Category = "TopicInfo")
		FString GetResponse();
	UFUNCTION(BlueprintCallable, Category = "TopicInfo")
		FString GetPrompt();




	UFUNCTION(BlueprintNativeEvent, meta = (DisplayName = "InfoTopic - Is Active"))
		bool IsActive();

	FORCEINLINE bool IsActive_Implementation() { return true; }

	/*
	UFUNCTION(BlueprintImplementable)
		void BeginScript();
	UFUNCTION(BlueprintImplementable)
		void EndScript();
	*/
	
private:


	//
	
	
};
	
	
	
	
	
	
	
	
	
	
	

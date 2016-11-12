#pragma once
#include "Runtime/CoreUObject/Public/UObject/UObject.h"
#include "Topic.generated.h"



/*

//UPROPERTY(EditDefaultsOnly, Category "Item")
//TSubclassOf<class AEquipablePickup> LootCompanion; //this is the Item->Loot class that would drop from the final product class aka BattleRifle_instanthit <-> BattleRifle_loot

UCLASS(Blueprintable, BlueprintType)

UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
class USkeletalMeshComponent* Mesh;

UFUNCTION(BlueprintNativeEvent, meta = (DisplayName = "OnPrimaryTrigger"))
void ReceiveOnPrimaryTrigger();

void AEquipable::ReceiveOnPrimaryTrigger_Implementation() { this->OnPrimaryTrigger(); }
void AEquipable::OnPrimaryTrigger() {}

UFUNCTION(BlueprintCallable, Category = "Equipable")

class ABaseTrainer* GetPawnOwner() const;
*/


UCLASS(Blueprintable, BlueprintType,Abstract)
class SPACESHOOTER_API UTopic : public UObject
{
	GENERATED_BODY()

public:

	UTopic(const FObjectInitializer& ObjectInitializer);
	
	
	UPROPERTY(BlueprintReadOnly, Category = "Topic")
		AActor* Parent;
	//---------------------------------------------------------------------------
	//These are temporary
	//TopicText stays, but would also have potentially multiple UInfo children, so multiple things to say, different responses, but it always goes to the same children
	//				..could have the do all bool determine if all child infos are said before moving on to chi
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Topic")
		FString TopicText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Topic")
		FString ResponseText;
	//---------------------------------------------------------------------------	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Topic")
		FString ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Topic")
		float Priority;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Topic")
		bool bDoAllBeforeRepeating;


	UFUNCTION(BlueprintNativeEvent, meta = (DisplayName = "Start Speaking Script"))
		void StartScript();

	FORCEINLINE void StartScript_Implementation() {  }

	UFUNCTION(BlueprintNativeEvent, meta = (DisplayName = "Start Speaking Script"))
		void StopScript();

	FORCEINLINE void StopScript_Implementation() {  }


	UFUNCTION(BlueprintNativeEvent, meta = (DisplayName = "Topic - Is Active"))
		bool IsActive();

	FORCEINLINE bool IsActive_Implementation() { return true; }

	
	UPROPERTY(BlueprintReadOnly, Category = "Topic")
		TArray<UTopic* > ChildrenTopics;
	
	UPROPERTY(BlueprintReadWrite, Category = "Topic")
		bool bSpoken;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Topic")
		bool bHello; //mark if its a hello topic...should this be in info instead?
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Topic")
		bool bGoodByeAfterScript;
	
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Topic")
		//TArray<UTopicInfo* > TopicInfos;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Topic", meta = (AllowPrivateAccess = "true"))
		TArray<TSubclassOf<class UTopic>> ChildrenTopicClasses;

private:


	//
	
	
};
	
	
	
	
	
	
	
	
	
	
	

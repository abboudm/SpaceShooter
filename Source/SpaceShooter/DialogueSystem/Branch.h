// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
//#include "GameFramework/Pawn.h"
//#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#include "Runtime/CoreUObject/Public/UObject/UObject.h"
#include "DialogueSystem/Topic.h"
#include "Branch.generated.h"




UENUM(BlueprintType)
enum class EBranchType : uint8
{
	Normal,
	TopLevel,
	Blocking,
};

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

UCLASS(Blueprintable, BlueprintType, Abstract)
class SPACESHOOTER_API UBranch : public UObject
{
	GENERATED_BODY()

public:

	UBranch(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(BlueprintReadOnly, Category = "Branch")
		AActor* Owner;



	UFUNCTION(BlueprintCallable, Category = "Branch")
	void Construct(AActor* ActorOwner, UWorld* world);


	UTopic* SetupTopic(UObject* Outer, TSubclassOf<class UTopic> TopicClass);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Branch")
		FString ID;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Branch")
		EBranchType BranchType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Branch")
		bool bExclusive;
		
	UFUNCTION(BlueprintNativeEvent, meta = (DisplayName = "Branch - Is Active"))
		bool IsActive();

	FORCEINLINE bool IsActive_Implementation() { return true; }



	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Branch")
		UWorld* World;



	UPROPERTY(BlueprintReadOnly, Category = "Branch")
		TArray<UTopic* > Topics;

	

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Branch", meta = (AllowPrivateAccess = "true"))
		TArray<TSubclassOf<class UTopic>> TopicClasses;
	
	
	
	
	
	
	
	
	
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item List")
		//TArray<FResponse> ResponseList;

	
 /*
	FORCEINLINE const FRichCurve* GetAnalogCursorAccelerationCurve() const
	{
		return AnalogCursorAccelerationCurve.GetRichCurveConst();
	}
*/
	//UPROPERTY(config, EditAnywhere, Category = "Analog Cursor", meta=( XAxisName="Strength", YAxisName="Acceleration" ))
	//FRuntimeFloatCurve AnalogCursorAccelerationCurve;

	//UPROPERTY(config, EditAnywhere, Category = "Analog Cursor", meta = (ClampMin = "1.0"))
	//float MaxAnalogCursorSpeed;

	// Analog Cursor
	//TWeakPtr<FGameAnalogCursor> AnalogCursor;
};

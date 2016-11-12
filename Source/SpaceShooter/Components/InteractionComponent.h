// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "DialogueSystem/Branch.h"
#include "InteractionComponent.generated.h"




UENUM(BlueprintType)
enum class EButtonDamageHandle : uint8
{
	None,
	ButtonOnHit,
	DestroyOnHit,
	ButtonAndDestroyOnHit,
	ButtonOnDeath,
};


UENUM(BlueprintType)
enum class EInteractionType : uint8
{
	None,
	Button,
	Loot,
	Container,
	Sign,
	Terminal,
	Character
};





UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACESHOOTER_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	//-----------------------------------------------------------------------------------------------
	// Sets default values for this component's properties
	UInteractionComponent();

	UPROPERTY(EditDefaultsOnly)
	EInteractionType InteractionType;

	//-----------------------------------------------------------------------------------------------
	//Button Channel to broadcast
	UPROPERTY(EditDefaultsOnly, Category = Button)
		int BroadcastChannel;

	UPROPERTY(EditDefaultsOnly, Category = Button)
		EButtonDamageHandle DamageHandleType;

	//-----------------------------------------------------------------------------------------------
	//Dialogue
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Branch")
		TArray<TSubclassOf<class UBranch>> BranchClasses;


	UPROPERTY(BlueprintReadOnly, Category = "Branch")
		TArray<UBranch* > Branchs;

	/*
	*/




	void ConstructDialogueBranchs();
	void Action();
	EInteractionType GetInteractionType();


	//-----------------------------------------------------------------------------------------------
	/*
	UPROPERTY(Category = "Attributes", EditAnywhere, BlueprintReadWrite)
		float MaxHealth;
	UPROPERTY(Category = "Attributes", EditAnywhere, BlueprintReadWrite)
		float MaxShield;
	UPROPERTY(Category = "Attributes", BlueprintReadOnly)
		bool Alive;
	UPROPERTY(Category = "Attributes", BlueprintReadOnly)
		float Health;
	UPROPERTY(Category = "Attributes", BlueprintReadOnly)
		float Shield;
	*/
	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

//	UFUNCTION(BlueprintCallable, Category = "Health")
//		void TakeDamage(float damage);

private:

	
};

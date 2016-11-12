// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceShooter.h"
#include "InteractionComponent.h"
#include "DialogueSystem/Branch.h"
#include "Components/Interfaces/ButtonInterface.h"

// Sets default values for this component's properties
UInteractionComponent::UInteractionComponent() : Super()
{
	InteractionType = EInteractionType::None;
	BroadcastChannel = -1;
	DamageHandleType = EButtonDamageHandle::None;

	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	//bWantsBeginPlay = true;
	//PrimaryComponentTick.bCanEverTick = true;

}



// Called when the game starts
void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
	ConstructDialogueBranchs();
}


// Called every frame
void UInteractionComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, "Tickity tickidy tickaroo");

	// ...
}



void UInteractionComponent::ConstructDialogueBranchs()
{
	for (TSubclassOf<class UBranch> BranchClass : BranchClasses)
	{
		UObject* Outer = GetOwner();
		UBranch* out = NewObject<UBranch>(Outer, BranchClass);
		out->Construct(GetOwner(), GetWorld());
		Branchs.Add(out);
	}
}
void UInteractionComponent::Action()
{
	switch (InteractionType)
	{
	case EInteractionType::None:
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Yellow, "InteractionType is none, so nothings gonna happen!");
		break;
	case EInteractionType::Button:
		if (BroadcastChannel > 0)
		{
			for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
			{
				
				if(ActorItr->GetClass()->ImplementsInterface(UButtonInterface::StaticClass()))
				{
					IButtonInterface::Execute_RecieveButtonMsg(*ActorItr, BroadcastChannel);
					//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, "$$$$$$$$$$$$$$$$$$$$ok executing button");
					//Button->Execute_RecieveButtonMsg(*ActorItr, BroadcastChannel);
				}
				
			
			}
			/*
			*/


			/*
			TArray<AActor* > OutActors;
			UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UButtonInterface::StaticClass(),OutActors);
			for (AActor* Actor : OutActors)
			{
		    GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, "Checken them interfaces!");
				IButtonInterface* Button = Cast<IButtonInterface>(Actor);
				if (Button)
				{
          GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, "$$$$$$$$$$$$$$$$$$$$ok executing button");
					Button->Execute_RecieveButtonMsg(Actor, BroadcastChannel);
				}
			}
			*/
		}
		break;
	case EInteractionType::Container:
		break;
	case EInteractionType::Sign:
		break;
	case EInteractionType::Terminal:
		break;
	case EInteractionType::Character:
		break;
	default:
		break;
	}

}
EInteractionType UInteractionComponent::GetInteractionType()
{
	return InteractionType;

}



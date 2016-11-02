// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceShooter.h"
#include "InteractionComponent.h"
#include "Components/Interfaces/ButtonInterface.h"

// Sets default values for this component's properties
UInteractionComponent::UInteractionComponent() : Super()
{
	InteractionType = EInteractionType::None;
	BroadcastChannel = -1;
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	//bWantsBeginPlay = true;
	//PrimaryComponentTick.bCanEverTick = true;

}



// Called when the game starts
void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
	SetupAction();
}


// Called every frame
void UInteractionComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, "Tickity tickidy tickaroo");

	// ...
}



void UInteractionComponent::SetupAction()
{

}
void UInteractionComponent::Action()
{
	switch (InteractionType)
	{
	case EInteractionType::None:
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Yellow, "InteractionType is none, so nothings gonna happen!");
		break;
	case EInteractionType::Button:
		if (BroadcastChannel > -1)
		{
			TArray<AActor* > OutActors;
			UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UButtonInterface::StaticClass(),OutActors);
			for (AActor* Actor : OutActors)
			{
				IButtonInterface* Button = Cast<IButtonInterface>(Actor);
				if (Button)
				{
					Button->Execute_RecieveButtonMsg(Actor, BroadcastChannel);
				}
			}
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


// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceShooter.h"
#include "HealthComponent.h"


// Sets default values for this component's properties
UHealthComponent::UHealthComponent() : Super()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	//bWantsBeginPlay = true;
	//PrimaryComponentTick.bCanEverTick = true;
	Alive = true;
	MaxHealth = 100;
	MaxShield = 100;
	Health = MaxHealth;
	Shield = MaxShield;
	// ...

}



// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	//FString Message = "Hellow Orld!";
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, Message);
}


// Called every frame
void UHealthComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, "Tickity tickidy tickaroo");

	// ...
}


/*
	Take Damage - decrements damage from shield & health accordingly
					set alive=false if health < 0
*/
void UHealthComponent::TakeDamage(float damage){
	if(Shield >= damage)
	{
		Shield = Shield - damage;
	}
	else if(Shield > 0)
	{
		float remainderDamage = damage - Shield;
		Shield = 0;
		Health = Health - remainderDamage;
	}
	else
	{
		Health = Health - damage;
	}
	
	if (Health <= 0){
		Alive = false;
	}
}




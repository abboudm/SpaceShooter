// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceShooter.h"
#include "Items/Item.h"
#include "Items/Equipable.h"
#include "AmmoLoot.h"
#include "Characters/BaseTrainer.h"
#include "Components/ClimbingPawnMovementComponent.h"

AAmmoLoot::AAmmoLoot(const class FObjectInitializer& PCIP) : Super(PCIP)
{
	Name = "AmmoLoot";
	Description = "This is an AmmoLoot item, like a static gun or apple";
	Value = 10;
	Weight = 1.0;
	ItemType = EItemType::Ammo;
	
}
void AAmmoLoot::PostInitializeComponents()
{
	Super::PostInitializeComponents();


}


void AAmmoLoot::NotifyActorBeginOverlap(AActor* OtherActor) 
{
	ABaseTrainer* pt = Cast<ABaseTrainer>(OtherActor);
	if (pt)
	{

		Lib::Msg("-----------------");
		Lib::Msg(pt->GetAmmo(AmmoType));
		//Lib::Msg(AmmoAmmount);
		Lib::Msg("AmmoAmmount - Get Ammo Amount");



		int leftover = pt->AddAmmo(AmmoType, AmmoAmmount);
		
		Lib::Msg("-----------------");
		Lib::Msg(leftover);
		Lib::Msg("-----------------");

		AmmoAmmount = leftover;



		if (AmmoAmmount <= 0)
		{
			this->Destroy();
		}
	
	}

}

void AAmmoLoot::NotifyActorEndOverlap(AActor* OtherActor) 
{

}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Items/Lootable.h"
#include "Items/Item.h"
//#include "Items/Equipable.h"

#include "AmmoLoot.generated.h"


UCLASS(Blueprintable,BlueprintType)
class SPACESHOOTER_API AAmmoLoot : public ALootable
{
	GENERATED_BODY()
		//virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

		
protected:
	AAmmoLoot(const FObjectInitializer& ObjectInitializer);
	virtual void PostInitializeComponents() override;

	UPROPERTY(EditDefaultsOnly)
	EAmmoType AmmoType;

	UPROPERTY(EditDefaultsOnly)
	int AmmoAmmount;

public:	

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

private:

	
	
};

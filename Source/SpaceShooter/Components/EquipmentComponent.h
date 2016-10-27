// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Items/Item.h"
#include "EquipmentComponent.generated.h"




UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACESHOOTER_API UEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()
	class ABaseTrainer* PawnOwner;

public:	
	// Sets default values for this component's properties
	UEquipmentComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	//------------------------------------------------------------
	//Takes a AEquipable as input, sets CurrentItem
	//returns old current Item
	UFUNCTION(BlueprintCallable, Category = "Equipment")
		AEquipable* SwitchCurrentItem(AEquipable* newItem);
	
	UFUNCTION(BlueprintCallable, Category = "Equipment")
		void DropItem(FItem equipItem);
	
	UFUNCTION(BlueprintCallable, Category = "Equipment")
		FItem Equip(FItem equipItem);

	UFUNCTION(BlueprintCallable, Category = "Equipment")
		FItem UnEquip();

	UFUNCTION(BlueprintCallable, Category = "Equipment")
		FItem EquipBackpack(FItem equipItem);
	UFUNCTION(BlueprintCallable, Category = "Equipment")
		FItem UnEquipBackpack();
	
	
	//OLD TODO, clean this up//
	//------------------------------------------------------------
	//Get Current / Set Functions
	UFUNCTION(BlueprintCallable, Category = "Equipment")
		AEquipable* RemoveCurrentItem();
	UFUNCTION(BlueprintCallable, Category = "Equipment")
		AEquipable* RemoveBackpackItem();
	UFUNCTION(BlueprintCallable, Category = "Equipment")
		AEquipable* GetCurrentItem();
	UFUNCTION(BlueprintCallable, Category = "Equipment")
		void SetCurrentItem(AEquipable* item);
	UFUNCTION(BlueprintCallable, Category = "Equipment")
		AEquipable* GetBackpackItem();
	UFUNCTION(BlueprintCallable, Category = "Equipment")
		void SetBackpackItem(AEquipable* item);
	//------------------------------------------------------------
	//Switch the backpack item with current
	UFUNCTION(BlueprintCallable, Category = "Equipment")
		void SwapCurrentBackpackItem();



	//------------------------------------------------------------
		//Ammo Slots
	int PistolAmmo;
	UPROPERTY(EditDefaultsOnly)
	int MaxPistolAmmo;
	
	int RifleAmmo;
	UPROPERTY(EditDefaultsOnly)
	int MaxRifleAmmo;
	
	int SniperAmmo;
	UPROPERTY(EditDefaultsOnly)
	int MaxSniperAmmo;
	
	int RocketAmmo;
	UPROPERTY(EditDefaultsOnly)
	int MaxRocketAmmo;
	
	int GrenadeAmmo;
	UPROPERTY(EditDefaultsOnly)
	int MaxGrenadeAmmo;

	int GetMaxAmmo(EAmmoType ammotype);
	int GetAmmo(EAmmoType ammotype);
	int UseAmmo(EAmmoType ammotype, int ammount);
	int AddAmmo(EAmmoType ammotype, int ammount);
	//------------------------------------------------------------
		//Current Item Slot
		//Backpack Item Slot
	class AEquipable* CurrentItem;
	class AEquipable* BackpackItem;

private:
	

	
};

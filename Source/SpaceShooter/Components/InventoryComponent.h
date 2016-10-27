// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Items/Item.h"
#include "Items/Equipable.h"
#include "Items/Weapons/InstantHitWeapon.h"
#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACESHOOTER_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();
	//-----------------------------------------------------------------------------------------------
	//Blueprint Edit
	//UPROPERTY(Category = "Attributes", EditAnywhere, BlueprintReadWrite)
		//float MaxHealth;
	virtual void BeginPlay() override;
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	//UFUNCTION(BlueprintCallable, Category = "Health")
		//void TakeDamage(float damage);

	UFUNCTION(BlueprintCallable, Category = "Item")
		TArray<FString> GetNameList();
	UFUNCTION(BlueprintCallable, Category = "Item")
		TArray<FItem> GetInventory();

	AInstantHitWeapon* CreateInstantHitWeaponFromItem(FItem weaponitem);
	FItem CreateItemFromInstantHit(AInstantHitWeapon* weapon);


	FItem GetItem(int index);
	void AddItemToInventory(FItem item);
	void RemoveItemFromInventory(int index);
	void RemoveItemFromInventory(FItem item);
	int HasItemAlready(FItem item);
	int GetGold();

private:
	TArray<FItem> ItemInventory;
	float Gold;
	
};

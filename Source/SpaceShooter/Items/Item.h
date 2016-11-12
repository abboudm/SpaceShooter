// Fill out your copyright notice in the Description page of Project Settings.
#include "Item.generated.h"
#pragma once


/*
//UPROPERTY(EditAnywhere, BlueprintReadWrite)
//EItemType ItemType;
UENUM(BlueprintType)
enum class EItemType : uint8
{

	IT_RIFLE		UMETA(DisplayName = "Rifle"),
	IT_PISTOL		UMETA(DisplayName = "Pistol"),
	IT_MISSLE		UMETA(DisplayName = "Missle"),
	IT_MELEE		UMETA(DisplayName = "Melee"),
	IT_NONE		UMETA(DisplayName = "None")

};
*/


UENUM(BlueprintType)
enum class EItemSortType : uint8
{
	Name,
	Value,
	Weight,
	Quantity,
	ItemType,
	LootType,
	EquipType,
	WeaponType,
	AmmoType,
	Clip,
	Burst,
	Damage,
	FullAuto,
};

UENUM(BlueprintType)
enum class EInventoryCategory : uint8
{
	All,
	Weapons,
	Loot,
};


UENUM(BlueprintType)
enum class EItemType : uint8
{
	Equipable,
	Ammo,
	Loot,
	Upgrade,
	KeyItem,
};
UENUM(BlueprintType)
enum class EEquipableType : uint8
{
		Weapon,
		Ammo,
		Throwable,
		Special,
};
UENUM(BlueprintType)
enum class EWeaponType : uint8
{
		Rifle,
		Sniper,
		Pistol,
		Launcher,
		Melee,
};
UENUM(BlueprintType)
enum class EAmmoType : uint8
{
		Rifle,
		Sniper,
		Pistol,
		Launcher,
		Rocket,
		Grenade,
};
UENUM(BlueprintType)
enum class ELootType : uint8
{
		Equipable,
		Craftable,
		Junk,
};
UENUM(BlueprintType)
enum class EUpgradeType : uint8 {
		ShieldUpgrade,
		MovementUpgrade,
		OtherUnknownYet,
};
//If you want this to appear in BP, make sure to use this instead
//USTRUCT(BlueprintType)
USTRUCT(BlueprintType)
struct FItem
{
	GENERATED_USTRUCT_BODY()
	//------------------------------------
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EItemType ItemType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Quantity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Value;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Weight;
	//------------------------------------
	//Base Item Data
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		//TSubclassOf<class AEquipable> EquipableClass;
		FStringClassReference EquipableClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EEquipableType EquipType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FStringClassReference LootClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ELootType LootType;
	//------------------------------------
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//	bool isEquipped;

	//Following properties are item specific, so stuff like weapon data {ammo,damage,other ui required values}
	//------------------------------------
	//WeaponData
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EWeaponType WeaponType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EAmmoType AmmoType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int AmmoInClip;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int ClipSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float HitDamage;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//	bool bBurst;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//	bool bFullAuto;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//	float ShotsPerMinute;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//	float BurstDelay;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//	float BurstSize;
	//default item struct constructor
	//methods to create item from an equip or lootable class


	void Increment()
	{
		if (Quantity <= 0)
		{
			Quantity = 0;
			GEngine->AddOnScreenDebugMessage(1, 4, FColor::Red, "Item quantity is 0!");
		}
		else
		{
			Increment(1);
		}
	}
	void Increment(int inc)
	{
		Quantity += inc;
	}
	void Decrement()
	{
		if (Quantity <= 0)
		{
			Quantity = 0;
			GEngine->AddOnScreenDebugMessage(1, 4, FColor::Red, "Item quantity is 0!");
		}
		else
		{
			Decrement(1);
		}
	}
	void Decrement(int inc)
	{
		Quantity -= inc;
	}







};
	/*
	
	UPROPERTY()
		ESpaceItemType ItemType;
	

	UPROPERTY()
		UClass* DamageTypeClass;

	UPROPERTY()
		TWeakObjectPtr<class AShooterCharacter> PawnInstigator;

	UPROPERTY()
		TWeakObjectPtr<class AActor> DamageCauser;

		//Always make USTRUCT variables into UPROPERTY()
		//    any non-UPROPERTY() struct vars are not replicated

		// So to simplify your life for later debugging, always use UPROPERTY()
		UPROPERTY()
		int32 SampleInt32;

	UPROPERTY()
		AActor* TargetActor;

	//Set
	void SetInt(const int32 NewValue)
	{
		SampleInt32 = NewValue;
	}

	//Get
	AActor* GetActor()
	{
		return TargetActor;
	}

	//Check
	bool ActorIsValid() const
	{
		if (!TargetActor) return false;
		return TargetActor->IsValidLowLevel();
	}

	//Constructor
	FJoyStruct()
	{
		//Always initialize your USTRUCT variables!
		//   exception is if you know the variable type has its own default constructor
		SampleInt32 = 5;
		TargetActor = NULL;
	}
	*/

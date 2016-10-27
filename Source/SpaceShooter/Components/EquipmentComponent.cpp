// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceShooter.h"
#include "Characters/BaseTrainer.h"
#include "Items/Equipable.h"
#include "Items/Item.h"
#include "Components/ClimbingPawnMovementComponent.h"
#include "EquipmentComponent.h"


// Sets default values for this component's properties
UEquipmentComponent::UEquipmentComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
	PawnOwner = Cast<ABaseTrainer>(GetOwner());

	MaxPistolAmmo = 999;
	MaxRifleAmmo = 999;
	MaxSniperAmmo = 999;
	MaxRocketAmmo = 999;
	MaxGrenadeAmmo = 999;
	
	PistolAmmo = 0;
	RifleAmmo = 0;
	SniperAmmo = 0;
	RocketAmmo = 0;
	GrenadeAmmo = 0;


	// ...
}
// Called when the game starts
void UEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

FItem UEquipmentComponent::Equip(FItem equipItem)
{
	FItem ItemOut;
	ItemOut.Name = "null";
	FActorSpawnParameters SpawnParam;
	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParam.Instigator = PawnOwner;
	//testItem.EquipableClass = FString("/Game/Blueprints/TestWeapon/TestRifle.TestRifle_C");
	UClass* Iclass = equipItem.EquipableClass.ResolveClass();

	if (!Iclass)
	{
		Lib::Msg("God damnclass");
		return ItemOut;

	}
	else
	{
		auto newCurrent = GetWorld()->SpawnActor<AEquipable>(Iclass, SpawnParam);
		if (newCurrent)
		{
			if (CurrentItem)
			{
				ItemOut = UnEquip();
			}
			//CurrentItem->UpdateItem(equipItem);
			newCurrent->UpdateItem(equipItem);
			SetCurrentItem(newCurrent);

			/*
			Lib::Msg("------------3239423487239482---------");
			Lib::Msg(equipItem.AmmoInClip);
			Lib::Msg(CurrentItem->GetItem().AmmoInClip);
			Lib::Msg(equipItem.ClipSize);
			Lib::Msg(CurrentItem->GetItem().ClipSize);
			Lib::Msg("------------3239423487239482---------");
			*/

		}
		else
		{
			Lib::Msg("God damn, no spawn of item class");
		}
	}

	return ItemOut;
}
void UEquipmentComponent::DropItem(FItem item)
{
	

	FTransform transform;
	FVector forward = PawnOwner->GetActorForwardVector();
	forward.Normalize();
	forward *= 50;

	FVector loc = PawnOwner->GetActorLocation();
	loc.Z += 50;
	
	transform.SetLocation(forward + loc);
	FActorSpawnParameters SpawnParam;
	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParam.Instigator = PawnOwner;
	//testItem.EquipableClass = FString("/Game/Blueprints/TestWeapon/TestRifle.TestRifle_C");
	UClass* Iclass = item.LootClass.ResolveClass();

	if (!Iclass)
	{
		Lib::Msg("God damnclass");
	}
	else
	{
		auto Dropped = GetWorld()->SpawnActor<ALootable>(Iclass, transform, SpawnParam);
		if (Dropped)
		{
			if (PawnOwner->IsControlled())
			{
				FVector CamLoc;
				FRotator CamRot;
				PawnOwner->GetController()->GetPlayerViewPoint(CamLoc, CamRot);

				Dropped->GetMesh()->SetPhysicsLinearVelocity(CamRot.Vector() * 1000);
				//Lib::Msg("Yay it spawned");

				Dropped->UpdateItem(item);

			}
			else
			{
				Dropped->SetActorLocation(PawnOwner->GetActorLocation());
				Dropped->UpdateItem(item);

			}
		}
		else
		{
			Lib::Msg("Boooo");
		}
	}
}
FItem UEquipmentComponent::UnEquip()
{
	FItem ItemOut;
	ItemOut.Name = "null";

	if (CurrentItem)
	{
		AEquipable* removed = CurrentItem;
		CurrentItem->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		CurrentItem = nullptr;
		ItemOut = removed->GetItem();
		removed->Destroy();
		return ItemOut;
	}
	else
	{
		return ItemOut;
	}



}




FItem UEquipmentComponent::EquipBackpack(FItem equipItem)
{
	FItem ItemOut;
	ItemOut.Name = "null";
	FActorSpawnParameters SpawnParam;
	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParam.Instigator = PawnOwner;
	//testItem.EquipableClass = FString("/Game/Blueprints/TestWeapon/TestRifle.TestRifle_C");
	UClass* Iclass = equipItem.EquipableClass.ResolveClass();

	if (!Iclass)
	{
		Lib::Msg("God damnclass");
		return ItemOut;

	}
	else
	{
		auto newBackpack = GetWorld()->SpawnActor<AEquipable>(Iclass, SpawnParam);
		if (newBackpack)
		{
			if (BackpackItem)
			{
				ItemOut = UnEquip();
			}

			SetBackpackItem(newBackpack);
		}
		else
		{
			Lib::Msg("God damn, no spawn of item class");
		}
	}

	return ItemOut;
}

FItem UEquipmentComponent::UnEquipBackpack()
{
	FItem ItemOut;
	ItemOut.Name = "null";

	if (BackpackItem)
	{
		AEquipable* removed = BackpackItem;
		BackpackItem->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		BackpackItem = nullptr;
		ItemOut = removed->GetItem();
		removed->Destroy();
		return ItemOut;
	}
	else
	{
		return ItemOut;
	}
	


}

// Called every frame
void UEquipmentComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

AEquipable* UEquipmentComponent::SwitchCurrentItem(AEquipable* newItem)
{
	//...
	AEquipable* old = CurrentItem;
	CurrentItem = newItem;
	return old;
}
void UEquipmentComponent::SwapCurrentBackpackItem()
{
	AEquipable* temp = nullptr;
	if (CurrentItem && BackpackItem)
	{
		temp = CurrentItem;
		SetCurrentItem(BackpackItem);
		SetBackpackItem(temp);

	}
	else
	{
		if (CurrentItem && !BackpackItem)
		{
			SetBackpackItem(RemoveCurrentItem());
		}
		else if (BackpackItem && !CurrentItem)
		{
			SetCurrentItem(RemoveBackpackItem());
		}
		else
		{
			Lib::Msg("You got no weapons!");
		}
	}
}

AEquipable* UEquipmentComponent::GetCurrentItem()
{
	return CurrentItem;
}

AEquipable* UEquipmentComponent::RemoveCurrentItem()
{
	if (CurrentItem)
	{
		AEquipable* removed = CurrentItem;
		CurrentItem->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		CurrentItem = nullptr;
		return removed;
	}
	else
	{
		return nullptr;
	}
}

AEquipable* UEquipmentComponent::RemoveBackpackItem()
{
	if (BackpackItem)
	{
		AEquipable* removed = BackpackItem;
		BackpackItem->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		BackpackItem = nullptr;
		return removed;
	}
	else
	{
		return nullptr;
	}
}

void UEquipmentComponent::SetCurrentItem(AEquipable* item)
{
	CurrentItem = item;
	CurrentItem->SetOwningPawn(PawnOwner);
	CurrentItem->OnEquip(false);
	CurrentItem->AttachToComponent(Cast<ABaseTrainer>(GetOwner())->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "WeaponSocket");

	/*
	CurrentItem->AttachToComponent(
		Cast<ABaseTrainer>(GetOwner())->GetMesh(),
		FAttachmentTransformRules::FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true),
		"WeaponSocket");
	*/
}
AEquipable* UEquipmentComponent::GetBackpackItem()
{
	return BackpackItem;
}
void UEquipmentComponent::SetBackpackItem(AEquipable* item)
{
	BackpackItem = item;
	BackpackItem->SetOwningPawn(PawnOwner);
	BackpackItem->OnUnEquip();
	BackpackItem->AttachToComponent(Cast<ABaseTrainer>(GetOwner())->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "BackpackSocket");

	/*
	BackpackItem->AttachToComponent(
		Cast<ABaseTrainer>(GetOwner())->GetMesh(),
		FAttachmentTransformRules::FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true),
		"BackpackSocket");
	*/
	//BackpackItem->AttachToComponent(mesh, FTransform::FTransform(), "WeaponSocket");
}

int UEquipmentComponent::GetMaxAmmo(EAmmoType ammotype)
{
	//If doing a climb, switch over possibilites
	switch (ammotype)
	{
	case EAmmoType::Pistol:
	{
		return MaxPistolAmmo;
	}
	case EAmmoType::Rifle:
	{
		return MaxRifleAmmo;
	}
	case EAmmoType::Sniper:
	{
		return MaxSniperAmmo;
	}
	case EAmmoType::Rocket:
	{
		return MaxRocketAmmo;
	}
	case EAmmoType::Grenade:
	{
		return MaxGrenadeAmmo;
	}
	default:
		//ok
		break;
	}
			
	return 0;
}

int UEquipmentComponent::GetAmmo(EAmmoType ammotype)
{
	switch (ammotype)
	{
	case EAmmoType::Pistol:
	{
		return PistolAmmo;
	}
	case EAmmoType::Rifle:
	{
		return RifleAmmo;
	}
	case EAmmoType::Sniper:
	{
		return SniperAmmo;
	}
	case EAmmoType::Rocket:
	{
		return RocketAmmo;
	}
	case EAmmoType::Grenade:
	{
		return GrenadeAmmo;
	}
	default:
		//ok
		break;
	}
	return 0;
}
int UEquipmentComponent::UseAmmo(EAmmoType ammotype, int ammount)
{
	switch (ammotype)
	{
	case EAmmoType::Pistol:
	{
		Lib::Msg("AmmoType is Pistol!");
		int tmp = PistolAmmo - ammount;
		if (tmp < 0)
		{
			tmp = PistolAmmo;
			PistolAmmo = 0;
			return tmp;
		}
		else
		{
			PistolAmmo -= ammount;
			return ammount;
		}
	}
	case EAmmoType::Rifle:
	{
		Lib::Msg("AmmoType is Rifle!");
		int tmp = RifleAmmo - ammount;
		if (tmp < 0)
		{
			tmp = RifleAmmo;
			RifleAmmo = 0;
			return tmp;
		}
		else
		{
			RifleAmmo -= ammount;
			return ammount;
		}
		
	}
	case EAmmoType::Sniper:
	{
		int tmp = SniperAmmo - ammount;
		if (tmp < 0)
		{
			tmp = SniperAmmo;
			SniperAmmo = 0;
			return tmp;
		}
		else
		{
			SniperAmmo -= ammount;
			return ammount;
		}
		
	}
	case EAmmoType::Rocket:
	{
		int tmp = RocketAmmo - ammount;
		if (tmp < 0)
		{
			tmp = RocketAmmo;
			RocketAmmo = 0;
			return tmp;
		}
		else
		{
			RocketAmmo -= ammount;
			return ammount;
		}
		
	}
	case EAmmoType::Grenade:
	{
		int tmp = GrenadeAmmo - ammount;
		if (tmp < 0)
		{
			tmp = GrenadeAmmo;
			GrenadeAmmo = 0;
			return tmp;
		}
		else
		{
			GrenadeAmmo -= ammount;
			return ammount;
		}
		
	}
	default:
		//ok
		break;
	}
	return 0;
}
int UEquipmentComponent::AddAmmo(EAmmoType ammotype, int ammount)
{
	//returns the left over that wasn't added, like max sniper ammo = x;
	switch (ammotype)
	{
	case EAmmoType::Pistol:
	{
		if (MaxPistolAmmo < (PistolAmmo + ammount))
		{
			int old = PistolAmmo;
			PistolAmmo = MaxPistolAmmo;
			return ammount - (MaxPistolAmmo - old);
		}
		else
		{
			PistolAmmo += ammount;
			break;
		}
	}
	case EAmmoType::Rifle:
	{
		if (MaxRifleAmmo < (RifleAmmo + ammount))
		{
			int old = RifleAmmo;
			RifleAmmo = MaxRifleAmmo;
			return ammount - (MaxRifleAmmo - old);
			//return (RifleAmmo + ammount) - MaxRifleAmmo;
		}
		else
		{
			RifleAmmo += ammount;
			break;
		}
	}
	case EAmmoType::Sniper:
	{
		if (MaxSniperAmmo < (SniperAmmo + ammount))
		{
			int old = SniperAmmo;
			SniperAmmo = MaxSniperAmmo;
			return ammount - (MaxSniperAmmo - old);
			//return (SniperAmmo + ammount) - MaxSniperAmmo;
		}
		else
		{
			SniperAmmo += ammount;
			break;
		}

	}
	case EAmmoType::Rocket:
	{
		if (MaxRocketAmmo < (RocketAmmo + ammount))
		{
			int old = RocketAmmo;
			RocketAmmo = MaxRocketAmmo;
			return ammount - (MaxRocketAmmo - old);
			//return (RocketAmmo + ammount) - MaxRocketAmmo;
		}
		else
		{
			RocketAmmo += ammount;
			break;
		}
	}
	case EAmmoType::Grenade:
	{
		if (MaxGrenadeAmmo < (GrenadeAmmo + ammount))
		{
			int old = GrenadeAmmo;
			GrenadeAmmo = MaxGrenadeAmmo;
			return ammount - (MaxGrenadeAmmo - old);
			//return (GrenadeAmmo + ammount) - MaxGrenadeAmmo;
		}
		else
		{
			GrenadeAmmo += ammount;
			break;
		}
	}
	default:
		//ok
		break;
	}
	return 0;

}
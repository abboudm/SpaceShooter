// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceShooter.h"
#include "Characters/BaseTrainer.h"
#include "Components/ClimbingPawnMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Items/Item.h"
#include "Items/Lootable.h"
#include "Equipable.h"


// Sets default values
AEquipable::AEquipable(const class FObjectInitializer& PCIP) : Super(PCIP)
{
	Name = "Equipable";
	Description = "This is an equipable item, like a gun or item";
	Value = 0;
	Weight = 1.0;
	ItemType = EItemType::Equipable;

	
	//Mesh = CreateOptionalDefaultSubobject<USkeletalMeshComponent>("EquipableMesh0");
	Mesh = PCIP.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("EquipableMesh0"));
	if (Mesh)
	{
		/*
		Mesh->AlwaysLoadOnClient = true;
		Mesh->AlwaysLoadOnServer = true;
		Mesh->bOwnerNoSee = false;
		Mesh->MeshComponentUpdateFlag = EMeshComponentUpdateFlag::AlwaysTickPose;
		Mesh->bCastDynamicShadow = true;
		Mesh->bAffectDynamicIndirectLighting = true;
		Mesh->PrimaryComponentTick.TickGroup = TG_PrePhysics;
		static FName MeshCollisionProfileName(TEXT("WeaponMesh"));
		Mesh->SetCollisionProfileName(MeshCollisionProfileName);
		Mesh->bGenerateOverlapEvents = false;
		Mesh->SetCanEverAffectNavigation(false);
		*/


		Mesh->AlwaysLoadOnClient = true;
		Mesh->AlwaysLoadOnServer = true;
		Mesh->bOwnerNoSee = false;
		//Mesh->MeshComponentUpdateFlag = EMeshComponentUpdateFlag::OnlyTickPoseWhenRendered;
		Mesh->bReceivesDecals = true;
		Mesh->CastShadow = true;
		Mesh->bCastDynamicShadow = true;
		Mesh->bAffectDynamicIndirectLighting = true;
		//Mesh->PrimaryComponentTick.TickGroup = TG_PrePhysics;
		static FName MeshCollisionProfileName(TEXT("WeaponMesh"));
		Mesh->SetCollisionProfileName(MeshCollisionProfileName);
		Mesh->bGenerateOverlapEvents = false;
		Mesh->SetCanEverAffectNavigation(false);
		Mesh->SetCollisionObjectType(ECC_WorldDynamic);
		Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Mesh->SetCollisionResponseToAllChannels(ECR_Ignore);
		Mesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
		RootComponent = Mesh;

		SetReplicates(true);
		bNetUseOwnerRelevancy = true;

		bIsEquipped = false;
		//set Equipable state
	

	}

}
void AEquipable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEquipable::UpdateItem(FItem item)
{
	SelfItem = item;
	SelfItem.ItemType = ItemType;
}

void AEquipable::SetupSelfItem()
{
	SelfItem.Name = Name;
	SelfItem.Description = Description;
	SelfItem.Value = Value;
	SelfItem.Weight = Weight;
	SelfItem.ItemType = ItemType;
	if (LootClass)
	{
		SelfItem.LootClass = FStringClassReference::GetOrCreateIDForClass(LootClass->GetClass());
	}

	SelfItem.EquipableClass = FStringClassReference::GetOrCreateIDForClass(this->GetClass());


}

FItem AEquipable::SafeGetItem()
{
	SetupSelfItem();
	return SelfItem;
}

FItem AEquipable::GetItem()
{
	return SelfItem;
}
void AEquipable::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SelfItem.Name = Name;
	SelfItem.Description = Description;
	SelfItem.Value = Value;
	SelfItem.Weight = Weight;
	SelfItem.ItemType = ItemType;
	if (LootClass)
	{
		SelfItem.LootClass = FStringClassReference::GetOrCreateIDForClass(LootClass->GetClass());
	}

	SelfItem.EquipableClass = FStringClassReference::GetOrCreateIDForClass(this->GetClass());

	//TimeBetweenShots = 60.0f / ShotsPerMinute;
	//CurrentAmmo = FMath::Min(StartAmmo, MaxAmmo);
	//CurrentAmmoInClip = FMath::Min(MaxAmmoPerClip, StartAmmo);
}

void AEquipable::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	DetachMeshFromPawn();
	//StopSimulatingWeaponFire();
}

void AEquipable::OnRep_MyPawn()
{
	
}



void AEquipable::BeginPlay()
{
	Super::BeginPlay();
}

void AEquipable::OnEquip(bool bPlayAnimation){bIsEquipped = true;}
void AEquipable::OnUnEquip(){bIsEquipped = false;}


void AEquipable::OnAddToInventory(ABaseTrainer* NewOwner) 
{
	//TODO: Need to determine 
	//	-where the attach point is
	//	-wheter to set as current equipped/backpack/storage inventory
	//SetOwningPawn(NewOwner);
	//AttachMeshToPawn("WeaponSocket");
}
void AEquipable::OnRemoveFromInventory()
{
	/*
	if (Role == ROLE_Authority)
	{
		SetOwningPawn(nullptr);
	}

	if (IsAttachedToPawn())
	{
		OnUnEquip();
	}

	DetachMeshFromPawn();
	*/
}


void AEquipable::ReceiveOnPrimaryTrigger_Implementation(){this->OnPrimaryTrigger();}
void AEquipable::OnPrimaryTrigger(){}

void AEquipable::ReceiveOnStopPrimaryTrigger_Implementation() { this->OnStopPrimaryTrigger(); }
void AEquipable::OnStopPrimaryTrigger(){}

void AEquipable::ReceiveOnSecondaryTrigger_Implementation(){this->OnSecondaryTrigger();}
void AEquipable::OnSecondaryTrigger(){}





void AEquipable::AttachMeshToPawn(FName ItemSocket)
{
	if (PawnOwner)
	{
		// Remove and hide
		DetachMeshFromPawn();

		USkeletalMeshComponent* PawnMesh = PawnOwner->GetMesh();
		Mesh->SetHiddenInGame(false);
		Mesh->AttachToComponent(PawnMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, ItemSocket);
	}
}
class ABaseTrainer* AEquipable::GetPawnOwner() const
{
	return PawnOwner;

}
void AEquipable::SetOwningPawn(ABaseTrainer* NewOwner)
{
	if (PawnOwner != NewOwner)
	{
		PawnOwner = NewOwner;
	}

}
USkeletalMeshComponent* AEquipable::GetMesh() const
{
	return Mesh;

}
void AEquipable::DetachMeshFromPawn()
{
	Mesh->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	Mesh->SetHiddenInGame(true);
}

void AEquipable::OnEquipFinished()
{

}

bool AEquipable::IsEquipped() const
{
	return bIsEquipped;
}

bool AEquipable::IsAttachedToPawn() const
{
	return bIsEquipped || bPendingEquip;

}
float AEquipable::GetEquipStartedTime() const
{
	return EquipStartedTime;
}


float AEquipable::GetEquipDuration() const
{
	return EquipDuration;
}


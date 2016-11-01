// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "SpaceShooter.h"
#include "BaseTrainer.h"
#include "Items/Equipable.h"
#include "Items/Weapons/Weapon.h"
#include "Components/ClimbingPawnMovementComponent.h"
#include "Components/HealthComponent.h"
#include "Components/EquipmentComponent.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "Components/OverlapObject.h"
#include "Items/Item.h"
#include "Items/Lootable.h"
#include "Components/InventoryComponent.h"
#include "Components/InteractionComponent.h"
#include "ImageUtils.h"


 




// Sets default values
//ABaseTrainer::ABaseTrainer(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UClimbingPawnMovementComponent>(ACharacter::CharacterMovementComponentName))
ABaseTrainer::ABaseTrainer(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)

{

	TArray<USkeletalMeshComponent*> Components;
	GetComponents<USkeletalMeshComponent>(Components);
	ClimbMesh = Components[0];

	TArray<UCapsuleComponent*> ComponentsCaps;
	GetComponents<UCapsuleComponent>(ComponentsCaps);
	ClimbCapsule = ComponentsCaps[0];
	ClimbCapsule->SetCapsuleHalfHeight(107.0);
	ClimbCapsule->SetCapsuleRadius(45.5);
	


	Interaction = CreateDefaultSubobject<UInteractionComponent>(TEXT("Interaction"));
	AddOwnedComponent(Interaction);
	Interaction->InteractionType = EInteractionType::Character;


	Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
	AddOwnedComponent(Health);

	Equipment = CreateDefaultSubobject<UEquipmentComponent>(TEXT("Equipment"));
	AddOwnedComponent(Equipment);
	
	Inventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
	AddOwnedComponent(Inventory);
	
}
void ABaseTrainer::NotifyActorEndOverlap(AActor* OtherActor)
{
	
}
void ABaseTrainer::NotifyActorBeginOverlap(AActor* OtherActor)
{
	
}
// Called when the game starts or when spawned
void ABaseTrainer::BeginPlay()
{
	Super::BeginPlay();
	
	
}
// Called every frame
void ABaseTrainer::Tick( float DeltaTime )
{
	Super::Tick(DeltaTime);
	
}

TArray<FItem> ABaseTrainer::GetInventory()
{
	return Inventory->GetInventory();
}
bool ABaseTrainer::AddInventory(FItem item)
{
	//Inventory->AddItem(item);
	Inventory->AddItemToInventory(item);
	return true;
}



void ABaseTrainer::DropItem(FItem item)
{
	Equipment->DropItem(item);
}

bool ABaseTrainer::RemoveInventory(FItem item)
{
	//Inventory->RemoveItem(item.id)
	Inventory->RemoveItemFromInventory(item);
	return true;
}
bool ABaseTrainer::RemoveInventory(int id)
{
	Inventory->RemoveItemFromInventory(id);
	return true;
}
bool ABaseTrainer::hasCurrentItem()
{
	if (Equipment->CurrentItem)
		return true;
	else
		return false;
}
bool ABaseTrainer::hasBackpackItem()
{
	if (Equipment->BackpackItem)
		return true;
	else
		return false;

}
void ABaseTrainer::SetCurrentItem(FItem item)
{
	FItem outitem = Equipment->Equip(item);
	//try add outitem
	AddInventory(outitem);

}
void ABaseTrainer::SetBackpackItem(FItem item)
{
	FItem outitem = Equipment->EquipBackpack(item);
	AddInventory(outitem);
}
FItem ABaseTrainer::RemoveCurrentItem()
{
	return Equipment->UnEquip();
}
FItem ABaseTrainer::RemoveBackpackItem()
{
	return Equipment->UnEquipBackpack();
}
FItem ABaseTrainer::GetCurrentItem()
{
	return Equipment->CurrentItem->GetItem();
}
FItem ABaseTrainer::GetBackpackItem()
{
	return Equipment->BackpackItem->GetItem();
}
int ABaseTrainer::GetMaxAmmo(EAmmoType ammotype)
{
	return Equipment->GetMaxAmmo(ammotype);
}
int ABaseTrainer::GetAmmo(EAmmoType ammotype)
{
	return Equipment->GetAmmo(ammotype);
}
int ABaseTrainer::UseAmmo(EAmmoType ammotype, int ammount)
{
	return Equipment->UseAmmo(ammotype,ammount);
}
int ABaseTrainer::AddAmmo(EAmmoType ammotype, int ammount)
{
	return Equipment->AddAmmo(ammotype,ammount);
}
float ABaseTrainer::TakeDamage(float DamageAmount,struct FDamageEvent const & DamageEvent,class AController * EventInstigator,AActor * DamageCauser)
{
	// Call the base class - this will tell us how much damage to apply  
	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	Health->TakeDamage(ActualDamage);
	
	if (Health->Health <= 0)
	{
		OnDeath();
	}

	ApplyDamageMomentum(ActualDamage, DamageEvent, this, DamageCauser);
	return ActualDamage;

}

void ABaseTrainer::OnDeath()
{
	if (Equipment->CurrentItem)
	{
		Equipment->DropItem(Equipment->UnEquip());
	}
	if (Equipment->BackpackItem)
	{
		Equipment->DropItem(Equipment->UnEquipBackpack());
	}

	//kill behavior tree when ai is going

	//------------------//------------------//------------------
	//The following effectively "Ragdolls" the mesh
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);

	GetMesh()->SetCollisionProfileName(FName(TEXT("Ragdoll")));

	SetActorEnableCollision(true);


	GetMesh()->SetAllBodiesSimulatePhysics(true);
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->WakeAllRigidBodies();
	GetMesh()->bBlendPhysics = true;
	//------------------//------------------//------------------


	//This destroys the body after 5 seconds
	//FTimerHandle DeathHandle;
	//float delaytime = 5.0;
	//GetWorldTimerManager().SetTimer(DeathHandle, this, &ABaseTrainer::HandleDeath, delaytime, false);

}

void ABaseTrainer::HandleDeath()
{
	this->Destroy();
}

bool ABaseTrainer::IsFiring() {return false;}

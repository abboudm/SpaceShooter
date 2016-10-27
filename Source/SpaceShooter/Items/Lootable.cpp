// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceShooter.h"
#include "Items/Item.h"
#include "Items/Equipable.h"
#include "Lootable.h"

UStaticMeshComponent* ALootable::GetMesh()
{
	return Mesh;
}
// Sets default values


ALootable::ALootable(const class FObjectInitializer& PCIP) : Super(PCIP)
{
	Name = "Lootable";
	Description = "This is an Lootable item, like a static gun or apple";
	Quantity = 1;
	Value = 10;
	Weight = 1.0;
	ItemType = EItemType::Loot;
	/*
	Sphere = CreateOptionalDefaultSubobject<USphereComponent>("SphereTrigger0");
	Mesh = CreateOptionalDefaultSubobject<UStaticMeshComponent>("LootableMesh0");

	RootComponent = Sphere;
	Mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	*/
	
	Sphere = CreateOptionalDefaultSubobject<USphereComponent>(TEXT("SphereTrigger0"));
	if (Sphere)
	{
		RootComponent = Sphere;
		Sphere->SetSimulatePhysics(true);
		Sphere->bGenerateOverlapEvents = true;
		Sphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		Sphere->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
		Sphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	
		Sphere->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Block);
		Sphere->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Block);
		Sphere->SetCollisionResponseToChannel(ECC_Visibility, ECR_Overlap);
		Sphere->SetCollisionResponseToChannel(ECC_Camera, ECR_Overlap);
		Sphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	
	}
	
	
	
	Mesh = CreateOptionalDefaultSubobject<UStaticMeshComponent>(TEXT("LootableMesh0"));
	if (Mesh)
	{
		Mesh->AlwaysLoadOnClient = true;
		Mesh->AlwaysLoadOnServer = true;
		Mesh->bOwnerNoSee = false;
		//Mesh->MeshComponentUpdateFlag = EMeshComponentUpdateFlag::OnlyTickPoseWhenRendered;
		Mesh->bReceivesDecals = true;
		Mesh->CastShadow = true;
		Mesh->bCastDynamicShadow = true;
		Mesh->bAffectDynamicIndirectLighting = true;
		Mesh->PrimaryComponentTick.TickGroup = TG_PrePhysics;
		
		static FName MeshCollisionProfileName(TEXT("ItemMesh"));
		Mesh->SetCollisionProfileName(MeshCollisionProfileName);
		
		Mesh->SetSimulatePhysics(false);
		Mesh->bGenerateOverlapEvents = true;
		Mesh->SetCanEverAffectNavigation(true);

		Mesh->SetCollisionObjectType(ECC_WorldDynamic);
		Mesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
		Mesh->SetCollisionResponseToAllChannels(ECR_Block);
		//Mesh->SetCollisionResponseToAllChannels(ECR_Ignore);
		//Mesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
		
		
		SetReplicates(true);
		bNetUseOwnerRelevancy = true;
		Mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	}
	
	
}

void ALootable::BeginPlay()
{
	SelfItem.Name = Name;
	SelfItem.Description = Description;
	SelfItem.Value = Value;
	SelfItem.Weight = Weight;
	SelfItem.ItemType = ItemType;
	SelfItem.LootType = LootType;
	SelfItem.Quantity = Quantity;
	if (EquipClass)
	{
		SelfItem.EquipableClass = FStringClassReference::GetOrCreateIDForClass(EquipClass);
	}
	else
	{
		//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, TEXT("NO EQUIP CLASS?!?!?!"));

	}
	SelfItem.LootClass = FStringClassReference::GetOrCreateIDForClass(this->GetClass());



}


FItem ALootable::GetItem()
{
	return SelfItem;
}
void ALootable::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SelfItem.ItemType = ItemType;
	
	/*
	*/


}

void ALootable::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

}

void ALootable::UpdateItem(FItem item)
{
	SelfItem = item;
	SelfItem.ItemType = ItemType;
}

float ALootable::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	// Call the base class - this will tell us how much damage to apply  
	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	GEngine->AddOnScreenDebugMessage(0, 10, FColor::Red, "HITLOOOOOOOT");
	if (Mesh->IsSimulatingPhysics())
	{
		//Mesh->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
		//Destroy();
	}


	//ApplyDamageMomentum(ActualDamage, DamageEvent, this, DamageCauser);
	return ActualDamage;

}

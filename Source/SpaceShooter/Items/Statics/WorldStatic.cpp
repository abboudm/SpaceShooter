// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceShooter.h"
#include "WorldStatic.h"
#include "Components/InteractionComponent.h"
#include "Components/HealthComponent.h"

UStaticMeshComponent* AWorldStatic::GetMesh()
{
	return Mesh;
}
// Sets default values


AWorldStatic::AWorldStatic(const class FObjectInitializer& PCIP) : Super(PCIP)
{
	

	Sphere = CreateOptionalDefaultSubobject<USphereComponent>(TEXT("SphereTrigger0"));
	if (Sphere)
	{
		RootComponent = Sphere;
		Sphere->SetSimulatePhysics(false);
		Sphere->bGenerateOverlapEvents = true;
		Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		Sphere->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
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



	Interaction = CreateDefaultSubobject<UInteractionComponent>(TEXT("Interaction"));
	AddOwnedComponent(Interaction);
	Interaction->InteractionType = EInteractionType::None;



}
void AWorldStatic::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AWorldStatic::BeginPlay()
{
  /*
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
  */



}


void AWorldStatic::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

}

float AWorldStatic::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
  /*
	// Call the base class - this will tell us how much damage to apply  
	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	GEngine->AddOnScreenDebugMessage(0, 10, FColor::Red, "HITLOOOOOOOT");
	if (Mesh->IsSimulatingPhysics())
	{
		//Mesh->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
		//Destroy();
	}


	//ApplyDamageMomentum(ActualDamage, DamageEvent, this, DamageCauser);
  Destroy();
  return ActualDamage;
  */

	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	/*
	Health->TakeDamage(ActualDamage);
	if (Health->Health <= 0)
	{
		OnDeath();
	}
	*/
	UHealthComponent* Health = this->FindComponentByClass<class UHealthComponent>();
	if (Interaction->InteractionType == EInteractionType::Button)
	{
		switch (Interaction->DamageHandleType)
		{
		case EButtonDamageHandle::None:
			break;
		case EButtonDamageHandle::ButtonOnHit:
			Interaction->Action();
			break;
		case EButtonDamageHandle::DestroyOnHit:
			Destroy();
			break;
		case EButtonDamageHandle::ButtonAndDestroyOnHit:
			Interaction->Action();
			Destroy();
			break;
		case EButtonDamageHandle::ButtonOnDeath:
			if (Health)
			{
				Health->TakeDamage(ActualDamage);
				if (Health->Health <= 0)
				{
					Interaction->Action();
					Destroy();
				}
			}
			else
			{
				Interaction->Action();
				Destroy();
			}
			break;
		default:
			break;
		}
	}
	else if (Health)
	{
		Health->TakeDamage(ActualDamage);
		if (Health->Health <= 0)
		{
			Destroy();
		}
	}
	
	
	
	
	
	return ActualDamage;

}
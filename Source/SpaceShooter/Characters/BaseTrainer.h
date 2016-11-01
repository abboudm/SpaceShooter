// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Pawn.h"
#include "Items/Item.h"
#include "Items/Lootable.h"

#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#include "BaseTrainer.generated.h"




UCLASS()
class SPACESHOOTER_API ABaseTrainer : public ACharacter
{
	GENERATED_BODY()
public:
	//
	ABaseTrainer(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	//
	//class UEquipmentComponent* GetEquipment();
	//---------------------------------------------------------
	//This is used in weapon.cpp - in liu of bFireButtonDown, this function exists
	//its blank in basetrainer,overrides in trainer, idk how ai will use weapons yet
	virtual bool IsFiring();
	
	
	//---------------------------------------------------------
	//Getters,Setters,Sorters,Etcers,Modifiers way to interact with
	//	-Equipment,Inventory,Health & Shields, Movement
	TArray<FItem> GetInventory();
	bool AddInventory(FItem item);
	bool RemoveInventory(FItem item);
	bool RemoveInventory(int id);
	void DropItem(FItem item);


	//UEquipmentComponent* GetEquipment();
	FItem GetCurrentItem();
	FItem GetBackpackItem();
	bool hasCurrentItem();
	bool hasBackpackItem();
	void SetCurrentItem(FItem item);
	void SetBackpackItem(FItem item);
	FItem RemoveCurrentItem();
	FItem RemoveBackpackItem();



	//------------------------------------------------------------------------
	//Overrides
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	//------------------------------------------------------------------------
	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;


	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
	
		USkeletalMeshComponent* ClimbMesh;

		UCapsuleComponent* ClimbCapsule;

public:

	virtual void OnDeath();
	//	friend class UClimbingPawnMovementComponent;
		
		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character", meta = (AllowPrivateAccess = "true"))
			class UHealthComponent* Health;

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character", meta = (AllowPrivateAccess = "true"))
			class UEquipmentComponent* Equipment;
		
		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character", meta = (AllowPrivateAccess = "true"))
			class UInventoryComponent* Inventory;

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character", meta = (AllowPrivateAccess = "true"))
			class UInteractionComponent* Interaction;

			/*
			UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character", meta = (AllowPrivateAccess = "true"))
			class UInteractionComponent* Interaction;

			Interaction = CreateDefaultSubobject<UInteractionComponent>(TEXT("Interaction"));
			AddOwnedComponent(Interaction);
			Interaction->InteractionType = EInteractionType::Character;
			*/



		virtual float TakeDamage(
			float DamageAmount, 
			struct FDamageEvent const & DamageEvent, 
			class AController * EventInstigator, 
			AActor * DamageCauser) override;

		int GetMaxAmmo(EAmmoType ammotype);
		int GetAmmo(EAmmoType ammotype);
		int UseAmmo(EAmmoType ammotype, int ammount);
		int AddAmmo(EAmmoType ammotype, int ammount);

protected:

	void HandleDeath();




};

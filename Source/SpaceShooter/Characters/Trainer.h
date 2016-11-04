// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "Characters/BaseTrainer.h"
//#include "GameFramework/Pawn.h"
#include "Items/Item.h"
#include "Items/Lootable.h"

#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#include "Trainer.generated.h"




UCLASS()
class SPACESHOOTER_API ATrainer : public ABaseTrainer
{
	GENERATED_BODY()
public:

	//---------------------------------------------------------
	//Spring arm and Camera inherited variables in blueprint
	//
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly)
		USpringArmComponent* CameraSpringArm;
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly)
		UCameraComponent* Camera;
	
		bool bSprinting;
		bool bJumpButtonDown;
		bool bSprintButtonDown;
		bool bCrouchButtonDown;
		bool bFireButtonDown;
		bool bSecondaryButtonDown;
		bool bActionButtonDown;
	ATrainer(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	bool PickupLoot(ALootable* Loot);

	bool InReach(AActor* actor);
	AActor* GetActorInReach();
	//------------------------------------------------------------------------
	//Overrides
	//------------------------------------------------------------------------
	virtual bool IsFiring() override; //called in weapon.cpp, is looking for bFireButtonDown


	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

	//------------------------------------------------------------------------
	//PLAYER SPECIC
	//------------------------------------------------------------------------
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void CameraPitch(float AxisValue);
	void CameraYaw(float AxisValue);
	void GamePadPitch(float AxisValue);
	void GamePadYaw(float AxisValue);
	/*Gamepad Right Thumbstick Sensitivity*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float LookXSensitivity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float LookYSensitivity;

	//A Button		
	virtual void Jump();
	virtual void StopJumping();	
	//X
	virtual void ActionX();
	virtual void ActionXReleased();
	//RB
	virtual void ActionRB();
	//LB
	virtual void ActionLB();
	//Y
	virtual void ActionY();
	virtual void SwitchItem();
	//B
	virtual void ActionB();
	virtual void Thruster();


	virtual void Sprint();
	virtual void StopSprinting();

	virtual void PrimaryTriggerUp();
	virtual void PrimaryTriggerDown();
	virtual void SecondaryTrigger();

	UFUNCTION(BlueprintCallable, Category = "Trainer")
		void ChangeView(bool FistPirson);

	void SwitchView();


	void CrouchFunk();
	void UnCrouchFunk();
	AActor* GetReachable();
	AActor* ReachableActor;
private:
		

		bool bFistPirsonView;
		float LastMoveForwardAxisValue;
		float LastMoveRightAxisValue;

	//------------------------------------------------------------------------
	//------------------------------------------------------------------------

	ALootable* OverlappedLoot;

	
	/** Pointer to climbing movement component*/
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class  UClimbingPawnMovementComponent* ClimbingMovement;

		class AOverlapObject* OverlopObject;

		class AZipLine* ZipLine;
		


		//USkeletalMeshComponent* ClimbMesh;

		//UCapsuleComponent* ClimbCapsule;

public:
		virtual void OnDeath() override;
		friend class UClimbingPawnMovementComponent;
		
		/*
		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character", meta = (AllowPrivateAccess = "true"))
			class UHealthComponent* Health;

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character", meta = (AllowPrivateAccess = "true"))
			class UEquipmentComponent* Equipment;
		
		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character", meta = (AllowPrivateAccess = "true"))
			class UInventoryComponent* Inventory;
		



		virtual float TakeDamage(
			float DamageAmount, 
			struct FDamageEvent const & DamageEvent, 
			class AController * EventInstigator, 
			AActor * DamageCauser) override;

		int GetMaxAmmo(EAmmoType ammotype);
		int GetAmmo(EAmmoType ammotype);
		int UseAmmo(EAmmoType ammotype, int ammount);
		int AddAmmo(EAmmoType ammotype, int ammount);
		*/



};

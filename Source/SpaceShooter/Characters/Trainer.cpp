// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "SpaceShooter.h"
#include "Trainer.h"
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
#include "ImageUtils.h"
#include "Items/Weapons/AmmoLoot.h"
#include "Characters/PlayerCharacterController.h"

 




// Sets default values
ATrainer::ATrainer(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UClimbingPawnMovementComponent>(ACharacter::CharacterMovementComponentName))
{

	ClimbingMovement = Cast<UClimbingPawnMovementComponent>(Super::GetMovementComponent());

	/*
	TArray<USkeletalMeshComponent*> Components;
	GetComponents<USkeletalMeshComponent>(Components);
	ClimbMesh = Components[0];

	
	TArray<UCapsuleComponent*> ComponentsCaps;
	GetComponents<UCapsuleComponent>(ComponentsCaps);
	ClimbCapsule = ComponentsCaps[0];
	ClimbCapsule->SetCapsuleHalfHeight(107.0);
	ClimbCapsule->SetCapsuleRadius(45.5);
	*/

	//Add Camera
	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	CameraSpringArm->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	CameraSpringArm->SetRelativeLocationAndRotation(FVector(50.0f, 50.0f, 80.0f), FRotator(0.0f, 0.0f, 0.0f));
	CameraSpringArm->TargetArmLength = 180.f;
	CameraSpringArm->bUsePawnControlRotation = true;
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CharacterCamera"));
	Camera->AttachToComponent(CameraSpringArm, FAttachmentTransformRules::KeepRelativeTransform, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = true;
	bUseControllerRotationYaw = false;
	Camera->SetFieldOfView(75);


	/*
	Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
	AddOwnedComponent(Health);

	Equipment = CreateDefaultSubobject<UEquipmentComponent>(TEXT("Equipment"));
	AddOwnedComponent(Equipment);
	
	Inventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
	AddOwnedComponent(Inventory);
	*/
	bSprinting = false;
	LookYSensitivity = 45;
	LookXSensitivity = 90;
}
void ATrainer::NotifyActorEndOverlap(AActor* OtherActor)
{
	/*
	if (Cast<ALootable>(OtherActor) && OverlappedLoot && OverlappedLoot == Cast<ALootable>(OtherActor))
	{
		OverlappedLoot = nullptr;
	}
	*/


}
void ATrainer::NotifyActorBeginOverlap(AActor* OtherActor)
{
	
	/*
	ALootable* overlappedLoot = Cast<ALootable>(OtherActor);
	if (overlappedLoot)
	{
		if (bActionButtonDown)
		{
			//Lib::Msg("HI");
			PickupLoot(overlappedLoot);
		}
		
		else if (!OverlappedLoot)
		{
			//Lib::Msg("Action Button Better be UP god dam");
			OverlappedLoot = overlappedLoot;
		}
	}
	else
	{
		Lib::Msg("No Overlap of LOOT!");
	}
	*/
	/*
	{
		if(ActionButton Down && LineOfSight?)
		{
			//handle fancier action button handling here, like if you have to hold to pick it up or not

			AddInventory->(OtherActor->Pickup());
		}
	}
	
	
	*/
	if (ClimbingMovement->GetClimbingMode() == EClimbingMode::CLIMB_None && Cast<AOverlapObject>(OtherActor))
	{
		
		OverlopObject = Cast<AOverlapObject>(OtherActor);
		
		if (ClimbingMovement->CanSetClimbMode(OverlopObject->GetObjectType()))
		{
			ClimbingMovement->SetClimbMode(OverlopObject->GetObjectType());
		}
		
		
	}
	
}
// Called when the game starts or when spawned
void ATrainer::BeginPlay()
{
	Super::BeginPlay();
	ChangeView(true);
	AddAmmo(EAmmoType::Pistol, 999);
	AddAmmo(EAmmoType::Rifle, 999);
	AddAmmo(EAmmoType::Sniper, 999);
	AddAmmo(EAmmoType::Rocket, 999);
	AddAmmo(EAmmoType::Grenade, 999);
	/*
	if (DefaultCurrentWeapon)
	{
		Equipment->SetCurrentItem(DefaultCurrentWeapon);
	}
	if (DefaultBackpackWeapon)
	{
		Equipment->SetBackpackItem(DefaultBackpackWeapon);
	}
	*/
	
}

AActor* ATrainer::GetActorInReach()
{
	FHitResult hit;
	FVector Eyeball = FVector::ZeroVector;
	float ArmLength = 200;
	FRotator EyeballRot;
	//FVector Eyeball = 
	GetController()->GetPlayerViewPoint(Eyeball, EyeballRot);
	AActor* out = nullptr;

	FVector CamLoc;
	FRotator CamRot;
	GetController()->GetPlayerViewPoint(CamLoc, CamRot);

	FVector AimDir = CamRot.Vector();


	Eyeball = Eyeball + AimDir * (FVector::DotProduct((GetActorLocation() - Eyeball), AimDir));

	//Lib::TraceLine(GetWorld(), this, Eyeball, (Eyeball + (AimDir * ArmLength)), hit, EDrawDebugTrace::ForDuration, ECollisionChannel::ECC_GameTraceChannel1);
	Lib::TraceLine(GetWorld(), this, Eyeball, (Eyeball + (AimDir * ArmLength)), hit, EDrawDebugTrace::None, ECollisionChannel::ECC_GameTraceChannel1);
	
	/*
	*/
	if (hit.Actor.IsValid())
	{
		out = hit.GetActor();
	}
	else
	{
		//
	}
	/*
	*/
	return out;
}

// Called every frame
void ATrainer::Tick( float DeltaTime )
{
	Super::Tick(DeltaTime);
	AActor* hit = GetActorInReach();
	if (hit)
	{
		ReachableActor = hit;
		/*
		ALootable* overlappedLoot = Cast<ALootable>(hit);
		if (overlappedLoot)
		{
			if (bActionButtonDown)
			{
				//Lib::Msg("HI");
				PickupLoot(overlappedLoot);
			}

			else if (!OverlappedLoot)
			{
				//Lib::Msg("Action Button Better be UP god dam");
				OverlappedLoot = overlappedLoot;
			}
		}
		else
		{
			Lib::Msg("No Overlap of LOOT!");
		}
		*/
		/*
		*/
	}
	else
	{
		ReachableActor = nullptr;
	}

	
	/*
	if (OverlappedLoot)
	{
		bool check = InReach(OverlappedLoot);
		Lib::Msg(check);
	}
	*/
	
	/*
	int width = 100;
	int height = 100;
	FName name = "Image";
	TArray<FColor> src;
	FCreateTexture2DParameters params;
	params.bSRGB = true;
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			src.Add(FColor(i, j, i + j, 1));
		}
	}
	
	UTexture2D *billy = FImageUtils::CreateTexture2D(width, height, src, this,"bob", EObjectFlags::RF_Dynamic, params);




	*/
}
// Called to bind functionality to input
void ATrainer::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	
	//LB
	InputComponent->BindAction("ActionLB", IE_Pressed, this, &ATrainer::ActionLB);
	//RB
	InputComponent->BindAction("ActionRB", IE_Pressed, this, &ATrainer::ActionRB);
	
	//L
	InputComponent->BindAction("SecondaryTrigger", IE_Pressed, this, &ATrainer::SecondaryTrigger);
	//R
	InputComponent->BindAction("PrimaryTrigger", IE_Pressed, this, &ATrainer::PrimaryTriggerDown);
	InputComponent->BindAction("PrimaryTrigger", IE_Released, this, &ATrainer::PrimaryTriggerUp);
	
	//Y
	InputComponent->BindAction("ActionY", IE_Pressed, this, &ATrainer::ActionY);
	//B
	InputComponent->BindAction("ActionB", IE_Pressed, this, &ATrainer::ActionB);
	//A
	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	//X
	InputComponent->BindAction("ActionX", IE_Pressed, this, &ATrainer::ActionX);
	InputComponent->BindAction("ActionX", IE_Released, this, &ATrainer::ActionXReleased);
	//Right Click
	InputComponent->BindAction("Sprint", IE_Pressed, this, &ATrainer::Sprint);
	InputComponent->BindAction("Sprint", IE_Released, this, &ATrainer::StopSprinting);
	//LeftClick
	InputComponent->BindAction("Crouch", IE_Pressed, this, &ATrainer::CrouchFunk);
	InputComponent->BindAction("Crouch", IE_Released, this, &ATrainer::UnCrouchFunk);
	
	//Back
	InputComponent->BindAction("SwitchView", IE_Pressed, this, &ATrainer::SwitchView);
	//Start
	//InputComponent->BindAction("SwitchView", IE_Pressed, this, &ATrainer::SwitchView);


	//RightStick/LeftStick/Mouse
	InputComponent->BindAxis("CameraPitch", this, &ATrainer::CameraPitch);
	InputComponent->BindAxis("CameraYaw", this, &ATrainer::CameraYaw);
	InputComponent->BindAxis("GamePadPitch", this, &ATrainer::GamePadPitch);
	InputComponent->BindAxis("GamePadYaw", this, &ATrainer::GamePadYaw);
	InputComponent->BindAxis("MoveForward", this, &ATrainer::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ATrainer::MoveRight);
}
void ATrainer::PrimaryTriggerDown()
{	
	bFireButtonDown = true;
	
	if (Equipment->CurrentItem)
	{
		Equipment->CurrentItem->ReceiveOnPrimaryTrigger();
	}
	else
	{
		Lib::Msg("CurrentItem in equipment is null bro");
	}
	//Equipment->CurrentItem->OnPrimaryTrigger();
}
void ATrainer::PrimaryTriggerUp()
{
	bFireButtonDown = false;

	if (Equipment->CurrentItem)
	{
		Equipment->CurrentItem->ReceiveOnStopPrimaryTrigger();
	}
	
	//E
}
void ATrainer::SecondaryTrigger()
{
	//this is calling event SecondaryTrigger
	
	if (Equipment->CurrentItem)
	{
		Equipment->CurrentItem->ReceiveOnSecondaryTrigger();
	}
	
	//Equipment->CurrentItem->OnSecondaryTrigger();
}
void ATrainer::ActionLB()
{
	//Lib::Msg("ActionLB!");
	FItem out = Equipment->UnEquip();
	/*
	Lib::Msg("DroppingItem!!!!!!!!!!!!!!");
	Lib::Msg(out.AmmoInClip);
	Lib::Msg(out.ClipSize);
	Lib::Msg("=======================");
	*/
	Equipment->DropItem(out);
	if (Equipment->BackpackItem)
	{
		Equipment->SwapCurrentBackpackItem();
	}
}
void ATrainer::ActionRB()
{
	//Lib::Msg("ActionRB!");
	//If Equipped Item, remove and add it to the inventory
	if (Equipment->CurrentItem && Inventory)
	{
			Inventory->AddItemToInventory(Equipment->UnEquip());
		//currentItem->Destroy();
	}
	else
	{
		//print size of inventory
		//print slot number 1 if theres more than one
		Lib::Msg("No Equipped to turn into item");
	}

}
void ATrainer::ActionXReleased()
{
	bActionButtonDown = false;
}
bool ATrainer::PickupLoot(ALootable* Loot)
{
	FItem lootitem = Loot->GetItem();
	switch (lootitem.ItemType)
	{
	case EItemType::Ammo:
		//do fucking nothing, god damn this class
		break;
	case EItemType::Equipable:
		//If Backpack is empty, switch out current
		//else, unequip current and add it to inventory
		if (Equipment->CurrentItem && !Equipment->BackpackItem)
		{
			Equipment->SwapCurrentBackpackItem();
		}
		else if (Equipment->CurrentItem && Equipment->BackpackItem)
		{
			Inventory->AddItemToInventory(Equipment->UnEquip());
		}
		
		Equipment->Equip(lootitem);
		Loot->Destroy();
		return true;
		break;
	case EItemType::Loot:
		Inventory->AddItemToInventory(lootitem);
		Loot->Destroy();
		return true;
		break;
	case EItemType::KeyItem:
		break;
	case EItemType::Upgrade:
		break;

	default:
		break;
	}
	return false;



	/*
	if (!Loot || Cast<AAmmoLoot>(Loot))
	{
		Lib::Msg("AmmoLoot cant be pickup like that!");
		return false;
	}

	FItem loot = Loot->GetItem();
	

	if (loot.ItemType == EItemType::Equipable)
	{
		//check if owned OR holding
		//if owned, add ammo or do nothing
		//else, equip and destroy loot
		//equip

		if (Equipment->CurrentItem && !Equipment->BackpackItem)
		{
			Equipment->SwapCurrentBackpackItem();
		}
		else if (Equipment->CurrentItem && Equipment->BackpackItem)
		{
			Inventory->AddItemToInventory(Equipment->UnEquip());
		}
		Equipment->Equip(loot);
		Loot->Destroy();
		return true;
	}
	else if (loot.ItemType == EItemType::Junk || loot.ItemType == EItemType::Craftable)
	{
		if (!Inventory->HasItemAlready(loot))
		{
			Inventory->AddItemToInventory(loot);
			Loot->Destroy();
			//OverlappedLoot->Destroy();
			return true;
		}
		else
		{
			Lib::Msg("You already have this item in inventory");
			return false;
		}
	}
	else
	{
		return false;
	}

	return false;
	*/

}

AActor* ATrainer::GetReachable()
{
	return ReachableActor;
}
void ATrainer::ActionX()
{
	bActionButtonDown = true;
	
	if (ReachableActor)
	{
		ALootable* overlappedLoot = Cast<ALootable>(ReachableActor);
		if (overlappedLoot)
		{
			PickupLoot(overlappedLoot);
		}
		else if (Cast<ABaseTrainer>(ReachableActor))
		{
			Cast<APlayerCharacterController>(GetController())->ConstructAndShowTradeMenu(ReachableActor);
		}
		else
		{
			Lib::Msg("No Overlap of LOOT!");
		}
	}
	//else if (ReachableActor->FindComponentByClass<class UInventoryComponent>())
	/*
	*/
	else
	{
		if (Equipment->CurrentItem && Cast<AWeapon>(Equipment->CurrentItem))
		{
			Cast<AWeapon>(Equipment->CurrentItem)->TriggerReload();
		}
	}
	
	
	/*
	if (OverlappedLoot)
	{

		//must have line of sight
		//if (InReach(OverlappedLoot))
		
			//if pickup is successful, null out OverlappedLoot, 
			//otherwise, you leave it be as end overlap will do that later
			if (PickupLoot(OverlappedLoot))
			{
				OverlappedLoot = nullptr;
			}
		
	}
	*/
	/*
	*/

}
	/*
	else
	{
		if (Inventory)
		{
			FItem testItem = Inventory->GetItem(0);
			FActorSpawnParameters SpawnParam;
			SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			SpawnParam.Instigator = this;

			//testItem.EquipableClass = FString("/Game/Blueprints/TestWeapon/TestRifle.TestRifle_C");
			UClass* Iclass = testItem.EquipableClass.ResolveClass();
		
			if (!Iclass)
			{
				Lib::Msg("God damnclass");
				return;

			}
			else
			{

				auto newCurrent = GetWorld()->SpawnActor<AEquipable>(Iclass,SpawnParam);
				if (newCurrent)
				{
					Equipment->SetCurrentItem(newCurrent);
				}
				else
				{
					Lib::Msg("God damn, no spawn of item class");
				}
			}
		}
	}
	*/
void ATrainer::ActionY()
{
	SwitchItem();
}
void ATrainer::SwitchItem()
{	
	if (Equipment->CurrentItem && Equipment->BackpackItem)
	{
		Equipment->SwapCurrentBackpackItem();
	}
	//if (Equipment->CurrentItem && Equipment->BackpackItem)
	//Lib::Msg("Inventory & Equipment not implemented yet!");

}

void ATrainer::ActionB()
{
	Thruster();
}
void ATrainer::Thruster() 
{
	ClimbingMovement->Thruster();
}
void ATrainer::Sprint()
{
	bSprintButtonDown = true;
}
void ATrainer::StopSprinting()
{
	bSprintButtonDown = false;
}
void ATrainer::MoveForward(float AxisValue)
{
	LastMoveForwardAxisValue = AxisValue;
	if (!bSprinting)
	{
		//If Stick is less than 0.25, so close but not  half way if strafing
		if (AxisValue >= 0.25 && bSprintButtonDown)
		{
			bSprinting = true;
		}
	}
	if (AxisValue < 0.6 && bSprinting)
	{
		bSprinting = false;
		
	}

	if (ClimbingMovement && (ClimbingMovement->UpdatedComponent == RootComponent))
	{
		switch (ClimbingMovement->GetClimbingMode())
		{
		
		
		case EClimbingMode::CLIMB_LeftWallRun:
			ClimbingMovement->AddInputVector(GetActorForwardVector() * AxisValue);
			break;

		case EClimbingMode::CLIMB_RightWallRun:
			ClimbingMovement->AddInputVector(GetActorForwardVector() * AxisValue);
			break;

		case EClimbingMode::CLIMB_Climb:
			if(AxisValue<0){
				ClimbingMovement->SetClimbMode(EClimbingMode::CLIMB_None);	
			}
			
		case EClimbingMode::CLIMB_InclinedSlide:
		case EClimbingMode::CLIMB_Slide:
			break;

		default:
			ClimbingMovement->AddInputVector(UKismetMathLibrary::GetForwardVector(FRotator(0, GetControlRotation().Yaw, 0)) * AxisValue);
			break;
		}
	}
}

void ATrainer::MoveRight(float AxisValue)
{
	LastMoveRightAxisValue = AxisValue;
	if (ClimbingMovement && (ClimbingMovement->UpdatedComponent == RootComponent))
	{

		switch (ClimbingMovement->GetClimbingMode())
		{
		
		case EClimbingMode::CLIMB_Climb:
		case EClimbingMode::CLIMB_InclinedSlide:
						
			ClimbingMovement->AddInputVector(GetActorRightVector() * AxisValue);
			break;

		case EClimbingMode::CLIMB_LeftWallRun:
		case EClimbingMode::CLIMB_RightWallRun:
		case EClimbingMode::CLIMB_Slide:
			break;

		default:
			ClimbingMovement->AddInputVector(UKismetMathLibrary::GetRightVector(FRotator(0, GetControlRotation().Yaw, 0)) * AxisValue);
			break;

		}
	}
}

void ATrainer::GamePadPitch(float AxisValue)
{
	float value = AxisValue * LookYSensitivity * GetWorld()->GetDeltaSeconds();
	AddControllerPitchInput(value);
}

void ATrainer::GamePadYaw(float AxisValue)
{
	float value = AxisValue * LookXSensitivity * GetWorld()->GetDeltaSeconds();
	AddControllerYawInput(value);
}


void ATrainer::CameraPitch(float AxisValue)
{
	AddControllerPitchInput(AxisValue);
}

void ATrainer::CameraYaw(float AxisValue)
{
	AddControllerYawInput(AxisValue);
}

void ATrainer::Jump()
{
	bJumpButtonDown = true;
	if (ClimbingMovement->GetClimbingMode() == EClimbingMode::CLIMB_None)
	{
		//Cant jump while crouched, this doesn't fix it
		//if (bIsCrouched) { UnCrouch();}
		Super::Jump();
	}
	else
	{
		ClimbingMovement->DoJump(false);
	}
}
void ATrainer::StopJumping()
{
	bJumpButtonDown = false;
	Super::StopJumping();
}


void ATrainer::CrouchFunk()
{
	bCrouchButtonDown = true;
	if (bSprinting)
	{
		bSprinting = false;
	}
	
	switch (ClimbingMovement->GetClimbingMode())
	{
	case EClimbingMode::CLIMB_None:
		if (ClimbingMovement->CanSetClimbMode(EClimbingMode::CLIMB_Slide))
		{
			
			//Crouch();
			ClimbingMovement->SetClimbMode(EClimbingMode::CLIMB_Slide);
		}
		else
		{
			Crouch();
		}

		break;
	
	case EClimbingMode::CLIMB_Climb:
	case EClimbingMode::CLIMB_LeftWallRun:
	case EClimbingMode::CLIMB_RightWallRun:
	case EClimbingMode::CLIMB_ZipLine:
		
		ClimbingMovement->SetClimbMode(EClimbingMode::CLIMB_None);

		break;

	}
}

void ATrainer::UnCrouchFunk()
{
	bCrouchButtonDown = false;
	switch (ClimbingMovement->GetClimbingMode())
	{
	case EClimbingMode::CLIMB_None:
		UnCrouch();
		break;
	case EClimbingMode::CLIMB_Slide:
		UnCrouch();
		ClimbingMovement->SetClimbMode(EClimbingMode::CLIMB_None);
		break;
		
	}
	
}

void ATrainer::SwitchView()
{
	ChangeView(!bFistPirsonView);
}

void ATrainer::ChangeView(bool FistPirson)
{
	if (FistPirson == bFistPirsonView) return;

	if (FistPirson)
	{
		Camera->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		
		
		//Camera->AttachToComponent(ClimbMesh, FAttachmentTransformRules::KeepRelativeTransform, FName("head"));
		//bip01-head is bone name for master chief - nead to generic rename in maya or whatever later
		//Camera->AttachToComponent(ClimbMesh, FAttachmentTransformRules::KeepRelativeTransform, FName("CameraSocket"));
		//Just set it in blueprints, parent socket the camera
		Camera->AttachToComponent(ClimbMesh, FAttachmentTransformRules::KeepRelativeTransform, FName("CameraSocket"));
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetControlRotation(GetActorRotation());
		Camera->SetRelativeLocation(FVector(0, 0, 0));
		bFistPirsonView = true;
		
		if (ClimbingMovement->GetClimbingMode() != EClimbingMode::CLIMB_Climb)
		{
			bUseControllerRotationYaw = true;
			ClimbingMovement->bOrientRotationToMovement = false;
			
		}
	}
	else
	{
		Camera->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		Camera->AttachToComponent(CameraSpringArm, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("SpringEndpoint"));
		bFistPirsonView = false;
		if (ClimbingMovement->GetClimbingMode() != EClimbingMode::CLIMB_Climb)
		{
			bUseControllerRotationYaw = true;
			ClimbingMovement->bOrientRotationToMovement = false;
			//bUseControllerRotationYaw = false;
			//ClimbingMovement->bOrientRotationToMovement = true;
		}
	}

}

void ATrainer::OnDeath()
{
	Lib::Msg("I should die");
	//Destroy();
}



bool ATrainer::InReach(AActor* actor)
{
	FHitResult hit;
	FVector Eyeball = FVector::ZeroVector;
	float ArmLength = 200;
	FRotator DummyRot;

	//FVector Eyeball = 
	GetController()->GetPlayerViewPoint(Eyeball, DummyRot);
	
	
	FVector CamLoc;
	FRotator CamRot;
	GetController()->GetPlayerViewPoint(CamLoc, CamRot);

	FVector AimDir = CamRot.Vector();
	
	
	Eyeball = Eyeball + AimDir * (FVector::DotProduct((GetActorLocation() - Eyeball), AimDir));
	Lib::TraceLine(GetWorld(), this, Eyeball, (Eyeball + (AimDir * ArmLength)), hit, EDrawDebugTrace::ForDuration, ECollisionChannel::ECC_GameTraceChannel1);
	
	if (hit.Actor == actor)
	{
		return true;
	}
	else
	{
		return false;
	}
	
	return false;
}

bool ATrainer::IsFiring() { return bFireButtonDown; }



/*
TArray<FItem> ATrainer::GetInventory()
{
	return Inventory->GetInventory();
}
bool ATrainer::AddInventory(FItem item)
{
	//Inventory->AddItem(item);
	Inventory->AddItemToInventory(item);
	return true;
}
bool ATrainer::RemoveInventory(FItem item)
{
	//Inventory->RemoveItem(item.id)
	Inventory->RemoveItemFromInventory(item);
	return true;
}
bool ATrainer::RemoveInventory(int id)
{
	Inventory->RemoveItemFromInventory(id);
	return true;
}
bool ATrainer::hasCurrentItem()
{
	if (Equipment->CurrentItem)
		return true;
	else
		return false;
}
bool ATrainer::hasBackpackItem()
{
	if (Equipment->BackpackItem)
		return true;
	else
		return false;

}
void ATrainer::SetCurrentItem(FItem item)
{
	FItem outitem = Equipment->Equip(item);
	//try add outitem
	AddInventory(outitem);

}
void ATrainer::SetBackpackItem(FItem item)
{
	FItem outitem = Equipment->EquipBackpack(item);
	AddInventory(outitem);
}
FItem ATrainer::RemoveCurrentItem()
{
	return Equipment->UnEquip();
}
FItem ATrainer::RemoveBackpackItem()
{
	return Equipment->UnEquipBackpack();
}
FItem ATrainer::GetCurrentItem()
{
	return Equipment->CurrentItem->GetItem();
}
FItem ATrainer::GetBackpackItem()
{
	return Equipment->BackpackItem->GetItem();
}
int ATrainer::GetMaxAmmo(EAmmoType ammotype)
{
	return Equipment->GetMaxAmmo(ammotype);
}
int ATrainer::GetAmmo(EAmmoType ammotype)
{
	return Equipment->GetAmmo(ammotype);
}
int ATrainer::UseAmmo(EAmmoType ammotype, int ammount)
{
	return Equipment->UseAmmo(ammotype,ammount);
}
int ATrainer::AddAmmo(EAmmoType ammotype, int ammount)
{
	return Equipment->AddAmmo(ammotype,ammount);
}
float ATrainer::TakeDamage(float DamageAmount,struct FDamageEvent const & DamageEvent,class AController * EventInstigator,AActor * DamageCauser)
{
	// Call the base class - this will tell us how much damage to apply  
	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	Health->TakeDamage(ActualDamage);
	Lib::Msg(Health->Health);
	Lib::Msg("OW!");
	return ActualDamage;

}
*/
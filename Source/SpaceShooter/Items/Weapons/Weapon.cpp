// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceShooter.h"
#include "Components/ClimbingPawnMovementComponent.h"
#include "Characters/BaseTrainer.h"
#include "Weapon.h"
#include "Items/Item.h"
AWeapon::AWeapon(const class FObjectInitializer& PCIP) : Super(PCIP)
{
	Name = "Weapon";
	//ItemType = EItemType::IT_NONE;
	CurrentState = EWeaponState::Idle;
	MuzzleSocket = "MuzzleSocket";
	ShotsPerMinute = 120;
	BurstSize = 3;
	bBurst = true;
	BurstDelay = 0.085;

	//StartAmmo = 999;
	//MaxAmmo = 999;
	MaxAmmoPerClip = 30;
	NoAnimReloadDuration = 1.5f;
	NoEquipAnimDuration = 0.5f;

	bBottomlessClip = false;
	bFullAuto = true;
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> DefualtMeshOb(TEXT("SkeletalMesh'/Game/SkelatalMesh_and_Animations/Weapons/BaseRifle/Interstel_BaseRifle.Interstel_BaseRifle'"));
	//static ConstructorHelpers::FObjectFinder<USkeletalMesh> DefualtMeshOb(TEXT("SkeletalMesh'/Game/SkeletalMeshs/Character/Mesh/SK_Mannequin.SK_Mannequin'"));

	DefaultMesh = DefualtMeshOb.Object;

	SelfItem.WeaponType = WeaponType;
	SelfItem.AmmoType = AmmoType;
	//SelfItem.AmmoInClip = CurrentAmmoInClip;
	SelfItem.ClipSize = MaxAmmoPerClip;
	SelfItem.bBurst = bBurst;
	SelfItem.bFullAuto = bFullAuto;
	SelfItem.ShotsPerMinute = ShotsPerMinute;
	SelfItem.BurstDelay = BurstDelay;
	SelfItem.BurstSize = BurstSize;

	PrimaryActorTick.bCanEverTick = true;
	SetActorTickEnabled(true);
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AWeapon::UpdateItem(FItem item)
{
	SelfItem = item;
	SelfItem.WeaponType = WeaponType;
	SelfItem.AmmoType	= AmmoType ;
	SelfItem.ItemType = ItemType;
	//CurrentAmmoInClip = SelfItem.AmmoInClip;
	if (SelfItem.ClipSize != 0){MaxAmmoPerClip = SelfItem.ClipSize;}
	//ShotsPerMinute = SelfItem.ShotsPerMinute;
	//BurstDelay = SelfItem.BurstDelay;
	//BurstSize = SelfItem.BurstSize;

}

FItem AWeapon::GetItem()
{
	SelfItem.WeaponType = WeaponType;
	SelfItem.AmmoType = AmmoType;
	//SelfItem.AmmoInClip = CurrentAmmoInClip;
	SelfItem.ClipSize = MaxAmmoPerClip;
	SelfItem.bBurst = bBurst;
	SelfItem.bFullAuto = bFullAuto;
	SelfItem.ShotsPerMinute = ShotsPerMinute;
	SelfItem.BurstDelay = BurstDelay;
	SelfItem.BurstSize = BurstSize;

	//SelfItem.EquipableClass = this->GetClass();
	return SelfItem;
}
void AWeapon::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	TimeBetweenShots = 60.0f / ShotsPerMinute;
	if (bBurst)
	{
		//BurstDelay = TimeBetweenShots * BurstDelayFactor;
		//TimeBetweenShots = TimeBetweenShots + (BurstDelay * BurstSize);
		float bursttime = BurstDelay * BurstSize;
		if (bursttime > TimeBetweenShots)
		{
			TimeBetweenShots = bursttime;
		}
		else 
		{
			//Burst time fits into Shots Per Minute


		}
	}

	//CurrentAmmo = FMath::Min(StartAmmo, MaxAmmo);
	//CurrentAmmoInClip = FMath::Min(MaxAmmoPerClip, MaxAmmoPerClip);
	
	
	//CurrentAmmoInClip = SelfItem.AmmoInClip;

	

	if (!Mesh->SkeletalMesh)
	{
		Mesh->SetSkeletalMesh(DefaultMesh);
	}
}
/*	==============================================================================
							Overrides from AItem
	==============================================================================*/

void AWeapon::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	//Super::EndPlay(EndPlayReason);
	DetachMeshFromPawn();
	StopSimulatingWeaponFire();
}
void AWeapon::OnEquipFinished()
{
	AttachMeshToPawn("WeaponSocket");

	bIsEquipped = true;
	bPendingEquip = false;

	DetermineWeaponState();

	if (PawnOwner)
	{
		// Try to reload empty clip
		//if (PawnOwner->IsLocallyControlled() && CurrentAmmoInClip <= 0 &&CanReload())
		if (PawnOwner->IsLocallyControlled() && SelfItem.AmmoInClip <= 0 &&CanReload())
		{


			//Lib::Msg(SelfItem.AmmoInClip);
			//Lib::Msg("OK HERE EQUIP");
			StartReload();
		}
	}
}
void AWeapon::OnEquip(bool bPlayAnimation)
{
	bPendingEquip = true;
	DetermineWeaponState();
	if (bPlayAnimation)
	{
		float Duration = PlayWeaponAnimation(EquipAnim);
		if (Duration <= 0.0f)
		{
			// Failsafe in case animation is missing
			Duration = NoEquipAnimDuration;
		}
		EquipStartedTime = GetWorld()->TimeSeconds;
		EquipDuration = Duration;

		GetWorldTimerManager().SetTimer(EquipFinishedTimerHandle, this, &AWeapon::OnEquipFinished, Duration, false);
	}
	else
	{
		OnEquipFinished();
	}

	if (PawnOwner && PawnOwner->IsLocallyControlled())
	{

		PlayWeaponSound(EquipSound);
	}
	

}
void AWeapon::OnUnEquip()
{
	bIsEquipped = false;
	StopFire();

	if (bPendingEquip)
	{
		StopWeaponAnimation(EquipAnim);
		bPendingEquip = false;

		GetWorldTimerManager().ClearTimer(EquipFinishedTimerHandle);
	}
	if (bPendingReload)
	{
		StopWeaponAnimation(ReloadAnim);
		bPendingReload = false;

		GetWorldTimerManager().ClearTimer(TimerHandle_ReloadWeapon);
	}

	DetermineWeaponState();
}
/*
		Sets & Determines
			-Reloading
			-Equipping
			-Firing
*/
void AWeapon::DetermineWeaponState()
{
	EWeaponState NewState = EWeaponState::Idle;
	if (bIsEquipped)
	{
		if (bPendingReload)
		{
			if (CanReload())
			{
				NewState = EWeaponState::Reloading;
			}
			else
			{
				NewState = CurrentState;
			}
		}
		else if (!bPendingReload && bWantsToFire && CanFire())
		{
			NewState = EWeaponState::Firing;
		}
	}
	else if (bPendingEquip)
	{
		NewState = EWeaponState::Equipping;
	}

	SetWeaponState(NewState);
}

//This Calls TriggerDown/Up --- TriggerDown calls handlefiring, which calls fireweapon
void AWeapon::SetWeaponState(EWeaponState NewState)
{
	const EWeaponState PrevState = CurrentState;

	if (PrevState == EWeaponState::Firing && NewState != EWeaponState::Firing)
	{
		OnTriggerUp();
	}

	CurrentState = NewState;

	if (PrevState != EWeaponState::Firing && NewState == EWeaponState::Firing)
	{
		OnTriggerDown();
	}
}
float AWeapon::PlayWeaponAnimation(UAnimMontage* Animation, float InPlayRate, FName StartSectionName)
{
	float Duration = 0.0f;
	if (PawnOwner)
	{
		if (Animation)
		{
			Duration = PawnOwner->PlayAnimMontage(Animation, InPlayRate, StartSectionName);
		}
	}

	return Duration;
}
void AWeapon::StopWeaponAnimation(UAnimMontage* Animation)
{
	if (PawnOwner)
	{
		if (Animation)
		{
			PawnOwner->StopAnimMontage(Animation);
		}
	}
}
UAudioComponent* AWeapon::PlayWeaponSound(USoundCue* SoundToPlay)
{
	UAudioComponent* AC = nullptr;
	if (SoundToPlay && PawnOwner)
	{
		AC = UGameplayStatics::SpawnSoundAttached(SoundToPlay, PawnOwner->GetRootComponent());
	}

	return AC;
}
/*
	SimulateWeaponFire()
			This handles the MuzzleFlash, FireSound, etc FXFXFXFXFXFX
*/
void AWeapon::SimulateWeaponFire()
{
	if (MuzzleFlash)
	{
		//Lib::Msg("MuzzleFlash!");
		//GetMuzzleLocation();
		//MuzzlePSC = UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, MuzzleAttachPoint);
		//MuzzlePSC = UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, MuzzleSocket);
		//MuzzlePSC = UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, MuzzleSocket,GetMuzzleLocation(),FRotator::ZeroRotator,EAttachLocation::SnapToTarget,true);
		
		FVector loc = GetMuzzleLocation();
		FRotator rot = Mesh->GetSocketRotation(MuzzleSocket);
		MuzzlePSC = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MuzzleFlash, loc, rot, true);
		//MuzzlePSC = UGameplayStatics::SpawnEmitterAttached(MuzzleFlash,Mesh,MuzzleSocket,FVector(0,0,0),FRotator(0,0,0),EAttachLocation::KeepRelativeOffset,true);
	}
	else
	{
		//Lib::Msg("WHTF");
	}

	if (!bPlayingFireAnim)
	{
		PlayWeaponAnimation(FireAnim);
		bPlayingFireAnim = true;
	}

	PlayWeaponSound(FireSound);
}
void AWeapon::StopSimulatingWeaponFire()
{
	if (bPlayingFireAnim)
	{
		StopWeaponAnimation(FireAnim);
		bPlayingFireAnim = false;
	}
}
void AWeapon::StartReload(bool bFromReplication)
{
	// Push the request to server
	if (!bFromReplication && Role < ROLE_Authority)
	{
		ServerStartReload();
	}

	// If local execute requested or we are running on the server //
	if (bFromReplication || CanReload())
	{
		bPendingReload = true;
		DetermineWeaponState();

		float AnimDuration = PlayWeaponAnimation(ReloadAnim);
		if (AnimDuration <= 0.0f)
		{
			AnimDuration = NoAnimReloadDuration;
		}

		GetWorldTimerManager().SetTimer(TimerHandle_StopReload, this, &AWeapon::StopSimulateReload, AnimDuration, false);
		if (Role == ROLE_Authority)
		{
			GetWorldTimerManager().SetTimer(TimerHandle_ReloadWeapon, this, &AWeapon::ReloadWeapon, FMath::Max(0.1f, AnimDuration - 0.1f), false);
		}

		if (PawnOwner && PawnOwner->IsLocallyControlled())
		{
			PlayWeaponSound(ReloadSound);
		}
	}
	/*
	*/
}
bool AWeapon::CanReload()
{
	//----------------------------------------------------TODO:FIXTHIS-------------------------------------------------------------------
	//bool bCanReload = (!PawnOwner || PawnOwner->CanReload());
	//!PawnOwner || canreload = PawnOwner->HealthComponent->bAlive;
	//----------------------------------------------------TODO:FIXTHIS-------------------------------------------------------------------
	//bool bGotAmmo = (CurrentAmmoInClip < MaxAmmoPerClip) && ((CurrentAmmo - CurrentAmmoInClip) > 0);
	//bool bGotAmmo = (CurrentAmmoInClip < MaxAmmoPerClip) && ((GetCurrentAmmo() - CurrentAmmoInClip) > 0);

	bool bCanReload = (!PawnOwner || true);
	bool bGotAmmo = (SelfItem.AmmoInClip < MaxAmmoPerClip) && ((GetCurrentAmmo() - SelfItem.AmmoInClip) > 0);
	bool bStateOKToReload = ((CurrentState == EWeaponState::Idle) || (CurrentState == EWeaponState::Firing));
	/*
	
	
	int a = CurrentAmmoInClip;
	int b = MaxAmmoPerClip;
	int c = GetCurrentAmmo();
	Lib::Msg("----------------_________------------");
	Lib::Msg(a);
	Lib::Msg(b);
	Lib::Msg(c);
	Lib::Msg("8888888888888888888888888888888888888");
	
	*/
	
	return (bCanReload && bGotAmmo && bStateOKToReload);
}
void AWeapon::ServerStartReload_Implementation()
{
	StartReload();
}
bool AWeapon::ServerStartReload_Validate()
{
	return true;
}
void AWeapon::StopSimulateReload()
{
	if (CurrentState == EWeaponState::Reloading)
	{
		bPendingReload = false;
		DetermineWeaponState();
		StopWeaponAnimation(ReloadAnim);
	}
}
void AWeapon::ReloadWeapon()
{
	//int32 ClipDelta = FMath::Min(MaxAmmoPerClip - CurrentAmmoInClip, GetCurrentAmmo() - CurrentAmmoInClip);
	int32 ClipDelta = FMath::Min(MaxAmmoPerClip - SelfItem.AmmoInClip, GetCurrentAmmo() - SelfItem.AmmoInClip);

	int newammo = PawnOwner->UseAmmo(SelfItem.AmmoType, ClipDelta);


	if (newammo > 0)
	{
		SelfItem.AmmoInClip += newammo;
		//CurrentAmmoInClip += newammo;
	}

	
}
void AWeapon::UseAmmo()
{
	/*
	Lib::Msg("----------------");
	Lib::Msg(GetCurrentAmmo());
	Lib::Msg(CurrentAmmoInClip);
	*/
	SelfItem.AmmoInClip--;
	//CurrentAmmoInClip--;
	//CurrentAmmo--;
}
bool AWeapon::CanFire() const
{
	//----------------------------------------------------TODO:FIXTHIS-------------------------------------------------------------------
	//samedeal as reload, pawnowner->canfire = pawnowner->healthcomponent->isalive
	//bool bPawnCanFire = PawnOwner && PawnOwner->CanFire();
	//----------------------------------------------------TODO:FIXTHIS-------------------------------------------------------------------
	bool bPawnCanFire = PawnOwner && true;
	bool bStateOK = CurrentState == EWeaponState::Idle || CurrentState == EWeaponState::Firing;
	return bPawnCanFire && bStateOK && !bPendingReload;
}

void AWeapon::StartFire()
{
	if (Role < ROLE_Authority)
	{
		ServerStartFire();
	}

	if (!bWantsToFire && PawnOwner->IsFiring())
	{
		bWantsToFire = true;
		DetermineWeaponState();
	}
}
bool AWeapon::ServerStartFire_Validate()
{
	return true;
}
void AWeapon::ServerStartFire_Implementation()
{
	StartFire();
}
void AWeapon::StopFire()
{
	if (Role < ROLE_Authority)
	{
		ServerStopFire();
	}

	if (bWantsToFire && !PawnOwner->IsFiring())
	{
		bWantsToFire = false;
		DetermineWeaponState();
	}
}
bool AWeapon::ServerStopFire_Validate()
{
	return true;
}
void AWeapon::ServerStopFire_Implementation()
{
	StopFire();
}
FVector AWeapon::GetAdjustedAim() const
{
	APlayerController* const PC = Instigator ? Cast<APlayerController>(Instigator->Controller) : nullptr;
	FVector FinalAim = FVector::ZeroVector;
	if (PC)
	{
		FVector CamLoc;
		FRotator CamRot;
		PC->GetPlayerViewPoint(CamLoc, CamRot);

		FinalAim = CamRot.Vector();
	}
	else if (Instigator)
	{
		FinalAim = Instigator->GetBaseAimRotation().Vector();
	}

	return FinalAim;
}
FVector AWeapon::GetCameraDamageStartLocation(const FVector& AimDir) const
{
	APlayerController* PC = PawnOwner ? Cast<APlayerController>(PawnOwner->Controller) : nullptr;
	FVector OutStartTrace = FVector::ZeroVector;

	if (PC)
	{
		FRotator DummyRot;
		PC->GetPlayerViewPoint(OutStartTrace, DummyRot);

		// Adjust trace so there is nothing blocking the ray between the camera and the pawn, and calculate distance from adjusted start
		///For some reason Instigator->GetActorLocation() crashes engine, if firing a gun created from Equipment->SetCurrentItem(Inventory->CreateInstantHitFromItem(WeaponItem));
		///OutStartTrace = OutStartTrace + AimDir * (FVector::DotProduct((Instigator->GetActorLocation() - OutStartTrace), AimDir));
		OutStartTrace = OutStartTrace + AimDir * (FVector::DotProduct((PawnOwner->GetActorLocation() - OutStartTrace), AimDir));
	}
	
	return OutStartTrace;
}
FHitResult AWeapon::WeaponTrace(const FVector& TraceFrom, const FVector& TraceTo) const
{

	FCollisionQueryParams TraceParams(TEXT("WeaponTrace"), true, Instigator);
	/*
	const FName TraceTag("MyTraceTag");
	GetWorld()->DebugDrawTraceTag = TraceTag;
	TraceParams.TraceTag = TraceTag;
	*/
	
	TraceParams.bTraceAsyncScene = true;
	TraceParams.bReturnPhysicalMaterial = true;
	FHitResult Hit(ForceInit);
	//GetWorld()->LineTraceSingleByChannel(Hit, TraceFrom, TraceTo, COLLISION_WEAPON, TraceParams);
	GetWorld()->LineTraceSingleByChannel(Hit, TraceFrom, TraceTo, ECollisionChannel::ECC_GameTraceChannel1, TraceParams);
	
	return Hit;
}

void AWeapon::HandleFiring()
{
	//Lib::Msg("WHWHWHWHWHWHWH");
	if (SelfItem.AmmoInClip > 0 && CanFire())
	{
		if (GetNetMode() != NM_DedicatedServer)
		{
			SimulateWeaponFire();	//this does the sounds * animations
		}

		if (PawnOwner && PawnOwner->IsLocallyControlled())
		{
			if (!bBottomlessClip)
			{
				UseAmmo();
			}
			FireWeapon();
			// Update firing FX on remote clients if this is called on server
			BurstCounter++;

		}
	}
	else if (CanReload())
	{
		Lib::Msg("else if reload in handle firing");
		StartReload();
	}
	else if (PawnOwner && PawnOwner->IsLocallyControlled())
	{
		if (GetCurrentAmmo() == 0 && !bRefiring)
		{
			PlayWeaponSound(OutOfAmmoSound);
		}

		// Reload after firing last round //
		//if (CurrentAmmoInClip <= 0 && CanReload())
		if (SelfItem.AmmoInClip <= 0 && CanReload())
		{
			StartReload();
		}

		//if (BurstCounter > 0){OnTriggerUp();}

	}


	//Shot was fired, burstcounter incremented now....
	if (PawnOwner && PawnOwner->IsLocallyControlled())
	{
		if (Role < ROLE_Authority)
		{
			ServerHandleFiring();
		}

		/* Retrigger if burst to burst count
		*/
		if (bBurst && BurstCounter < BurstSize)
		{
			GetWorldTimerManager().SetTimer(TimerHandle_HandleBurst, this, &AWeapon::HandleFiring, BurstDelay, false);
		}


		/* Retrigger HandleFiring on a delay for automatic weapons */
		bRefiring = (CurrentState == EWeaponState::Firing && TimeBetweenShots > 0.0f && bFullAuto && PawnOwner->IsFiring());
		if (bRefiring)
		{
			if (bBurst)
			{
				if (BurstCounter >= BurstSize)
				{
					BurstCounter = 0;
					GetWorldTimerManager().SetTimer(TimerHandle_HandleFiring, this, &AWeapon::HandleFiring, TimeBetweenShots, false);
				}
			}
			else
			{
				GetWorldTimerManager().SetTimer(TimerHandle_HandleFiring, this, &AWeapon::HandleFiring, TimeBetweenShots, false);

			}
		}
	}

	if (PawnOwner)
	{
		//PawnOwner->MakePawnNoise(1.0f);
	}
	if (!bBurst)
	{
		LastFireTime = GetWorld()->GetTimeSeconds();

	}
	
	if (bBurst && BurstCounter >= BurstSize)
	{
		LastFireTime = GetWorld()->GetTimeSeconds();
	}

	if (CanReload() && SelfItem.AmmoInClip <= 0)
	{
		Lib::Msg("RanOut! firing");
		StartReload();
	}
	//if (CurrentAmmoInClip > 0 && CanFire())
	


}
bool AWeapon::ServerHandleFiring_Validate(){return true;}
void AWeapon::ServerHandleFiring_Implementation()
{
	//const bool bShouldUpdateAmmo = (CurrentAmmoInClip > 0 && CanFire());
	const bool bShouldUpdateAmmo = (SelfItem.AmmoInClip > 0 && CanFire());

	HandleFiring();

	if (bShouldUpdateAmmo)
	{
		UseAmmo();

		// Update firing FX on remote clients
		BurstCounter++;
	}
}
void AWeapon::OnTriggerDown()
{

	// Start firing, can be delayed to satisfy TimeBetweenShots
	const float GameTime = GetWorld()->GetTimeSeconds();

	//if lastfiretime + timebetween shots > GameTime
		//Then we need to wait the difference, so call handlefiring when done
	if (LastFireTime > 0 && TimeBetweenShots > 0.0f && LastFireTime + TimeBetweenShots > GameTime)
	{
		//GetWorldTimerManager().SetTimer(TimerHandle_HandleFiring, this, &AWeapon::HandleFiring, LastFireTime + TimeBetweenShots - GameTime, false);
	}
	else if (bBurst && BurstCounter < BurstSize && BurstCounter > 0)
	{
		//Magic Conch shell do nothing 
	}
	else
	{
		BurstCounter = 0;
		HandleFiring();
	}
}
void AWeapon::OnTriggerUp()
{
	
	/* Retrigger if burst to burst count*/
	if (GetNetMode() != NM_DedicatedServer)
	{
		StopSimulatingWeaponFire();
	}

	if (bRefiring)
	{
		GetWorldTimerManager().ClearTimer(TimerHandle_HandleFiring);
		bRefiring = false;
	}

	//GetWorldTimerManager().ClearTimer(TimerHandle_HandleFiring);
	//bRefiring = false;
	//GetWorldTimerManager().ClearTimer(TimerHandle_HandleBurst);
}



int32 AWeapon::GetCurrentAmmo() const{

	return PawnOwner->GetAmmo(SelfItem.AmmoType);
}
int32 AWeapon::GiveAmmo(int32 AddAmount)
{
	/*
	const int32 MissingAmmo = FMath::Max(0, MaxAmmo - GetCurrentAmmo());
	AddAmount = FMath::Min(AddAmount, MissingAmmo);
	//CurrentAmmo += AddAmount;
	PawnOwner->AddAmmo(SelfItem.AmmoType, AddAmount);
	// Push reload request to client 
	if (GetCurrentAmmoInClip() <= 0 && CanReload() && PawnOwner->GetCurrentWeapon() == this)
	{
		ClientStartReload();
	}

	//return unused ammo
	return FMath::Max(0, AddAmount - MissingAmmo);
	*/
	return 0;
}

FVector AWeapon::GetMuzzleLocation() const
{
	return Mesh->GetSocketLocation(MuzzleSocket);
}
FRotator AWeapon::GetMuzzleRotation() const
{
	return Mesh->GetSocketRotation(MuzzleSocket);
}

//-------------------------------------------------------------------------------------

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
}
void AWeapon::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, "tickidytickdiytickctickdicdjicj");
	WeaponTick(DeltaSeconds);
}

void AWeapon::WeaponTick_Implementation(float DeltaSeconds)
{
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, "weapontick c++");
}

void AWeapon::TriggerReload(){	if (CanReload()){	StartReload();	}	}

void AWeapon::OnPrimaryTrigger()
{
	//Lib::Msg("PRIMARY Trigger Down WEAPON");
	StartFire();
}
void AWeapon::OnStopPrimaryTrigger()
{
	//Lib::Msg("PRIMARY Trigger Down WEAPON");
	StopFire();

}
void AWeapon::OnSecondaryTrigger()
{
	//Super::OnSecondaryTrigger();
	Lib::Msg("SECONDARY WEAPON");








}

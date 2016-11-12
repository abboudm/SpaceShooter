// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Items/Equipable.h"
#include "Items/Item.h"
#include "Weapon.generated.h"
#define COLLISION_WEAPON ECC_GameTraceChannel1
UENUM()
enum class EWeaponState
{
	Idle,
	Firing,
	Equipping,
	Reloading,
	Meleeing
};


UCLASS(Blueprintable, BlueprintType, Abstract)
class SPACESHOOTER_API AWeapon : public AEquipable
{
	GENERATED_BODY()

	virtual void PostInitializeComponents() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void OnEquipFinished() override;
	virtual void OnUnEquip() override;
	virtual void OnEquip(bool bPlayAnimation) override;
	
	//UPROPERTY(Transient, ReplicatedUsing = OnRep_Reload)
	bool bPendingReload;


public:

	virtual FItem GetItem() override;

	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly, Category = "Item")
		EWeaponType WeaponType;
	UPROPERTY(EditDefaultsOnly, Category = "Item")
		EAmmoType AmmoType;
	UPROPERTY(EditDefaultsOnly, Category = "Item")
		bool bFullAuto;
	UPROPERTY(EditDefaultsOnly, Category = "Item")
		bool bBurst;
	UPROPERTY(EditDefaultsOnly, Category = "Item")
		int32 BurstSize;
	UPROPERTY(EditDefaultsOnly, Category = "Item")
		float BurstDelay;
		//float BurstDelayFactor;
	UPROPERTY(EditDefaultsOnly, Category = "Item")
		float ShotsPerMinute;
	//-------------------------------------------------------------
	//Initializer & Overrides from Equipable.h
	AWeapon(const FObjectInitializer& ObjectInitializer);
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaSeconds) override;
	virtual void OnPrimaryTrigger() override;
	virtual void OnStopPrimaryTrigger() override;
	virtual void OnSecondaryTrigger() override;

	void TriggerReload();

	/*-----------------------------------------------------------------
						OnFire & Damage Handling
	-------------------------------------------------------------------*/
	FTimerHandle TimerHandle_HandleFiring;
	FTimerHandle TimerHandle_HandleBurst;
	void StartFire();
	void StopFire();
	//EWeaponState GetCurrentState() const;
	//FName WeaponSocket = "RifleSOcket"; // | "PistolSocket"
	//void AttachMeshToPawn(FName WeaponSocket);
	FVector GetMuzzleLocation() const;
	FRotator GetMuzzleRotation() const;

	UPROPERTY()
		FCanvasIcon Crosshair[5];

protected:
	bool CanFire() const;
	FVector GetAdjustedAim() const;
	FVector GetCameraDamageStartLocation(const FVector& AimDir) const;
	FHitResult WeaponTrace(const FVector& TraceFrom, const FVector& TraceTo) const;

	//PURE_VIRTUAL lets us skip making function in weapon.cpp, but will overwrite in instanthit.cpp
	virtual void FireWeapon() PURE_VIRTUAL(AWeapon::FireWeapon, );
	//virtual void FireWeapon();


private:

	void SetWeaponState(EWeaponState NewState);
	void DetermineWeaponState();
	virtual void HandleFiring();
	void OnTriggerDown();
	void OnTriggerUp();
	bool bWantsToFire;
	EWeaponState CurrentState;
	bool bRefiring;
	float LastFireTime;
	float TimeBetweenShots;
	UPROPERTY(EditDefaultsOnly, Category = "Item")
		bool bBottomlessClip;
	
	UPROPERTY(EditDefaultsOnly)
		FName MuzzleSocket;

	UFUNCTION(Reliable, Server, WithValidation)
	void ServerStopFire();
	
	void ServerStopFire_Implementation();

	bool ServerStopFire_Validate();


	UFUNCTION(Reliable, Server, WithValidation)
	void ServerStartFire();

	void ServerStartFire_Implementation();

	bool ServerStartFire_Validate();


	UFUNCTION(Reliable, Server, WithValidation)
	void ServerHandleFiring();

	void ServerHandleFiring_Implementation();

	bool ServerHandleFiring_Validate();
	/* SERVER STUFF
	*/

	/*-----------------------------------------------------------------
					FX - Sounds, Animations, Particle Systems
	-------------------------------------------------------------------*/
private:
	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundCue* FireSound;

	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundCue* EquipSound;

	UPROPERTY(EditDefaultsOnly)
	UParticleSystem* MuzzleFlash;

	UPROPERTY(EditDefaultsOnly)
		UAnimMontage* EquipAnim;

	UPROPERTY(EditDefaultsOnly)
		UAnimMontage* FireAnim;

	UPROPERTY(Transient)
	UParticleSystemComponent* MuzzlePSC;

	/*
	*/

	bool bPlayingFireAnim;
public:
	//UPROPERTY(Transient, ReplicatedUsing = OnRep_BurstCounter)
	int32 BurstCounter;

protected:
	virtual void SimulateWeaponFire();
	virtual void StopSimulatingWeaponFire();

	//FVector GetMuzzleLocation() const;
	//FVector GetMuzzleDirection() const;
	UAudioComponent* PlayWeaponSound(USoundCue* SoundToPlay);
	float PlayWeaponAnimation(UAnimMontage* Animation, float InPlayRate = 1.f, FName StartSectionName = NAME_None);
	void StopWeaponAnimation(UAnimMontage* Animation);

/*
=====================================================================
					AMMO
=====================================================================
*/

private:
	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
		USoundCue* OutOfAmmoSound;

	FTimerHandle TimerHandle_ReloadWeapon;

	FTimerHandle TimerHandle_StopReload;
protected:

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
		float NoAnimReloadDuration;
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
		float NoEquipAnimDuration;

	void UseAmmo();
	virtual void ReloadWeapon();
	bool CanReload();

	//UPROPERTY(Transient, Replicated)
	//UPROPERTY(Transient, Replicated)
		int32 CurrentAmmoInClip;
	UPROPERTY(EditDefaultsOnly)
		int32 MaxAmmoPerClip;
	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
		USoundCue* ReloadSound;
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
		UAnimMontage* ReloadAnim;

public:
	virtual void StartReload(bool bFromReplication = false);
	UFUNCTION(reliable, server, WithValidation)
		void ServerStartReload();
	void ServerStartReload_Implementation();

	bool ServerStartReload_Validate();

	virtual void StopSimulateReload();

	UFUNCTION(BlueprintCallable, Category = "Ammo")
		int32 GetCurrentAmmo() const;
	UFUNCTION(BlueprintCallable, Category = "Ammo")
		int32 GetCurrentAmmoInClip() const;

	
	int32 GiveAmmo(int32 AddAmount);

	virtual void UpdateItem(FItem item) override;
	/*
	void SetAmmoCount(int32 NewTotalAmount);


	UFUNCTION(BlueprintCallable, Category = "Ammo")
		int32 GetMaxAmmoPerClip() const;

	UFUNCTION(BlueprintCallable, Category = "Ammo")
		int32 GetMaxAmmo() const;
	*/
	
	/*
	****************SERVER****************
protected:
	UFUNCTION(Reliable, Client)
		void ClientStartReload();

	void ClientStartReload_Implementation();

	UFUNCTION()
		void OnRep_Reload();

	



	UFUNCTION(reliable, server, WithValidation)
		void ServerStopReload();

	void ServerStopReload_Implementation();

	bool ServerStopReload_Validate();
		*/


























};













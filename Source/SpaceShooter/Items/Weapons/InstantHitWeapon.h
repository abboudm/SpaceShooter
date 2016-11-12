// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Items/Weapons/Weapon.h"
#include "InstantHitWeapon.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, Abstract)
class SPACESHOOTER_API AInstantHitWeapon : public AWeapon
{
	GENERATED_BODY()


		//virtual void BeginPlay() override;
		//virtual void Tick(float DeltaSeconds) override;

		//virtual void OnPrimaryTrigger() override;
		//virtual void OnStopPrimaryTrigger() override;
		//virtual void OnSecondaryTrigger() override;


		
		//virtual FItem GetItem() override;
	/************************************************************************/
	/* Visual Handlers                                                      */
	/************************************************************************/
	void SimulateInstantHit(const FVector& ImpactPoint);
	void SpawnImpactEffects(const FHitResult& Impact);
	void SpawnTrailEffects(const FVector& EndPoint);



	/* Particle FX played when a surface is hit. */
	
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class AImpactEffect> ImpactTemplate;

	UPROPERTY(EditDefaultsOnly)
		FName TrailSourceParam;
	UPROPERTY(EditDefaultsOnly)
		FName TrailTargetParam;

	UPROPERTY(EditDefaultsOnly)
		UParticleSystem* TrailFX;

	UPROPERTY(EditDefaultsOnly)
		UParticleSystem* TracerFX;

	/* Minimum firing distance before spawning tracers or trails. */
	UPROPERTY(EditDefaultsOnly)
		float MinimumProjectileSpawnDistance;

	UPROPERTY(EditDefaultsOnly)
		int32 TracerRoundInterval;

	/* Keeps track of number of shots fired */
	//int32 BulletsShotCount;
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
protected:

	AInstantHitWeapon(const FObjectInitializer& ObjectInitializer);


	float CurrentSpread;
	UPROPERTY(EditDefaultsOnly, Category = "Item")
		float WeaponSpread;
	float GetCurrentSpread() const;

	UPROPERTY(EditDefaultsOnly, Category = "Item")
		int ShotTraces;
	/************************************************************************/
	/* Damage Processing                                                    */
	/************************************************************************/
	virtual void FireWeapon() override;
	bool ShouldDealDamage(AActor* TestActor) const;
	void DealDamage(const FHitResult& Impact, const FVector& ShootDir);
	void ProcessInstantHit(const FHitResult& Impact, const FVector& Origin, const FVector& ShootDir);
	void ProcessInstantHitConfirmed(const FHitResult& Impact, const FVector& Origin, const FVector& ShootDir);




	UFUNCTION(Reliable, Server, WithValidation)
		void ServerNotifyHit(const FHitResult Impact, FVector_NetQuantizeNormal ShootDir);

	void ServerNotifyHit_Implementation(const FHitResult Impact, FVector_NetQuantizeNormal ShootDir);

	bool ServerNotifyHit_Validate(const FHitResult Impact, FVector_NetQuantizeNormal ShootDir);

	UFUNCTION(Reliable, Server, WithValidation)
		void ServerNotifyMiss(FVector_NetQuantizeNormal ShootDir);

	void ServerNotifyMiss_Implementation(FVector_NetQuantizeNormal ShootDir);

	bool ServerNotifyMiss_Validate(FVector_NetQuantizeNormal ShootDir);

	UFUNCTION()
		void OnRep_HitLocation();
	/*

	*/

	//UPROPERTY(Transient, ReplicatedUsing = OnRep_HitLocation)
		FVector HitImpactNotify;

	/************************************************************************/
	/* Weapon Configuration                                                 */
	/************************************************************************/
	
	UPROPERTY(EditDefaultsOnly)
		float HitDamage;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UHDamageType> DamageType;

	UPROPERTY(EditDefaultsOnly)
		float WeaponRange;

	UPROPERTY(EditDefaultsOnly)
		float AllowedViewDotHitDir;

	UPROPERTY(EditDefaultsOnly)
		float ClientSideHitLeeway;
	

	virtual void UpdateItem(FItem item) override;
	



};


/*
	----------------------------------------------------------------
		InstantHit Weapon BP 

		Event_OnFire(FVector crosshairTargeted)
		{
			if(bTriggerDown){return;}
			else{
				bTriggerDown = true;
				//=--=-=-=-=-===-=-=-=-=-=-=-=-=-//=--=-=-=-=-===-=-=-=-=-=-=-=-=-//=--=-=-=-=-===-=-=-=-=-=-=-=-=-
				if(bBurst)
				{
					for(i=1,i<BurstSize;i++)
					{
						TryFireBullet(crosshairTargeted);
						crosshairTargeted = Cast<AHaloCCharacter>(GetOwner())->GetCrosshairLocation();
						Delay(BurstDelay);

				}
				else
				{
					TryFireBullet(crosshairTargeted);

				}
				//=--=-=-=-=-===-=-=-=-=-=-=-=-=-//=--=-=-=-=-===-=-=-=-=-=-=-=-=-//=--=-=-=-=-===-=-=-=-=-=-=-=-=-
				Delay(FireRate + (BurstDelay*BurstSize));
				bTriggerDown = false;
				bFiring = false;
				if(Cast<AHaloCCharacter>(GetOwner())->FireButtonDown && bFullAuto)
				{
					this->Event_OnFire(
						Cast<AHaloCCharacter>(GetOwner())->GetCrosshairWorldSpace()
					);

			}
		}

		Event_NewClipReloaded()
		{
			this->Reload();
		}






*/
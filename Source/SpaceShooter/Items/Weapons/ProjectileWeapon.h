// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Items/Weapons/Weapon.h"
#include "ProjectileWeapon.generated.h"

/**
 * 
 */
UCLASS()
class SPACESHOOTER_API AProjectileWeapon : public AWeapon
{
	GENERATED_BODY()




protected:

	AProjectileWeapon(const FObjectInitializer& ObjectInitializer);


	float CurrentSpread;
	UPROPERTY(EditDefaultsOnly, Category = "Item")
		float WeaponSpread;
	UPROPERTY(EditDefaultsOnly, Category = "Item")
		float LauncherAngle;
	
	float GetCurrentSpread() const;

	UPROPERTY(EditDefaultsOnly, Category = "Item")
		int ShotTraces;
	/************************************************************************/
	/* Damage Processing                                                    */
	/************************************************************************/
	virtual void FireWeapon() override;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class AProjectile> Projectile;
};
// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceShooter.h"
#include "Components/ChildActorComponent.h"
#include "Items/Weapons/HDamageType.h"
#include "Items/Weapons/ImpactEffect.h"
#include "Components/ClimbingPawnMovementComponent.h"
#include "ProjectileWeapon.h"
#include "Items/Item.h"
#include "Items/Weapons/Projectile.h"

AProjectileWeapon::AProjectileWeapon(const class FObjectInitializer& PCIP) : Super(PCIP)
{
	Name = "Projectile Weapon";
	AmmoType = EAmmoType::Rocket;
	//ItemType = EItemType::IT_RIFLE;
	CurrentSpread = 0;
	WeaponSpread = 1;
	ShotTraces = 1;
}

float AProjectileWeapon::GetCurrentSpread() const
{
	//float FinalSpread = InstantConfig.WeaponSpread + CurrentFiringSpread;
	float FinalSpread = WeaponSpread + CurrentSpread;
	
	/*
	if (PawnOwner && PawnOwner->IsTargeting())
	{
		FinalSpread *= InstantConfig.TargetingSpreadMod;
	}
	*/

	return FinalSpread;

}

void AProjectileWeapon::FireWeapon()
{
	for (int i = 0; i < ShotTraces; i++)
	{
		const int32 RandomSeed = FMath::Rand();
		FRandomStream WeaponRandomStream(RandomSeed);
		const float CurrentSpread = GetCurrentSpread();
		const float ConeHalfAngle = FMath::DegreesToRadians(CurrentSpread * 0.5f);
		const FVector AimDir = GetAdjustedAim();
		
		//StartTrace
		const FVector StartTrace = GetCameraDamageStartLocation(AimDir);
		//Trace Direction
		const FVector ShootDir = WeaponRandomStream.VRandCone(AimDir, ConeHalfAngle, ConeHalfAngle);
		//End Point
		//const FVector EndTrace = StartTrace + ShootDir * WeaponRange;
		const FVector MuzzleLocation = GetMuzzleLocation();
		const FRotator MuzzleRotation = GetMuzzleRotation();
		//return Mesh->GetSocketLocation(MuzzleSocket);

		UWorld* const World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;
			FRotator rotation = ShootDir.Rotation();
			rotation.Pitch += LauncherAngle;
			// spawn the projectile at the muzzle
			//AProjectile* projectile = World->SpawnActor<AProjectile>(Projectile->StaticClass(), MuzzleLocation, MuzzleRotation, SpawnParams);

			AProjectile* projectile = World->SpawnActor<AProjectile>(Projectile, MuzzleLocation, rotation, SpawnParams);
			if (projectile)
			{
				
				// find launch direction
				//FVector const LaunchDir = MuzzleRotation.Vector();
				//projectile->InitVelocity(ShootDir);
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(0, 4, FColor::Red, "NOSPAWN");
			}
		}
		
		//Spawn the projectile
		
		//TODO: Add Dynamic Spread
		//Just gonna have a fixed spread for now, no differences in aiming or holding down trigger
		//CurrentFiringSpread = FMath::Min(InstantConfig.FiringSpreadMax, CurrentFiringSpread + InstantConfig.FiringSpreadIncrement);
	}
}

/*
FItem AProjectileWeapon::GetItem()
{
	//SelfItem.WeaponType = WeaponType;
	//SelfItem.AmmoType = AmmoType;
	//SelfItem.AmmoInClip = AmmoInClip;
	//SelfItem.ClipSize = ClipSize;
	SelfItem.bBurst = bBurst;
	SelfItem.bFullAuto = bFullAuto;
	SelfItem.ShotsPerMinute = ShotsPerMinute;
	SelfItem.BurstDelay = BurstDelay;
	SelfItem.BurstSize = BurstSize;

	//SelfItem.EquipableClass = this->GetClass();
	return SelfItem;
}
*/
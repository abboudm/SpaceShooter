// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceShooter.h"
#include "Components/ChildActorComponent.h"
#include "Items/Weapons/HDamageType.h"
#include "Items/Weapons/ImpactEffect.h"
#include "Components/ClimbingPawnMovementComponent.h"
#include "InstantHitWeapon.h"

AInstantHitWeapon::AInstantHitWeapon(const class FObjectInitializer& PCIP) : Super(PCIP)
{
	Name = "Instant Hit Weapon";
	//ItemType = EItemType::IT_RIFLE;

	HitDamage = 25;
	WeaponRange = 15000;

	AllowedViewDotHitDir = -1.0f;
	ClientSideHitLeeway = 200.0f;
	MinimumProjectileSpawnDistance = 800;
	TracerRoundInterval = 3;

	CurrentSpread = 0;
	WeaponSpread = 1;
	ShotTraces = 1;


	SelfItem.HitDamage = HitDamage;
}

float AInstantHitWeapon::GetCurrentSpread() const
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

void AInstantHitWeapon::FireWeapon()
{
	for (int i = 0; i < ShotTraces; i++)
	{
		const int32 RandomSeed = FMath::Rand();
		FRandomStream WeaponRandomStream(RandomSeed);
		const float CurrentSpread = GetCurrentSpread();
		const float ConeHalfAngle = FMath::DegreesToRadians(CurrentSpread * 0.5f);

		/*
		const FVector AimDir = GetAdjustedAim();
		const FVector StartTrace = GetCameraDamageStartLocation(AimDir);
		const FVector ShootDir = WeaponRandomStream.VRandCone(AimDir, ConeHalfAngle, ConeHalfAngle);
		const FVector EndTrace = StartTrace + ShootDir * InstantConfig.WeaponRange;

		const FHitResult Impact = WeaponTrace(StartTrace, EndTrace);
		ProcessInstantHit(Impact, StartTrace, ShootDir, RandomSeed, CurrentSpread);

		CurrentFiringSpread = FMath::Min(InstantConfig.FiringSpreadMax, CurrentFiringSpread + InstantConfig.FiringSpreadIncrement);
		*/




		const FVector AimDir = GetAdjustedAim();
		const FVector StartTrace = GetCameraDamageStartLocation(AimDir);
		const FVector ShootDir = WeaponRandomStream.VRandCone(AimDir, ConeHalfAngle, ConeHalfAngle);
		const FVector EndTrace = StartTrace + ShootDir * WeaponRange;
		//const FVector EndTrace = StartTrace + (AimDir * WeaponRange);
		//trace along camera, check if blocking hit
		FHitResult Impact = WeaponTrace(StartTrace, EndTrace);
		const FVector MuzzleOrigin = GetMuzzleLocation();
		FVector AdjustedAimDir = AimDir;


		if (Impact.bBlockingHit)
		{
			// Adjust the shoot direction to hit at the crosshair.
			AdjustedAimDir = (Impact.ImpactPoint - MuzzleOrigin).GetSafeNormal();

			// Re-trace with the new aim direction coming out of the weapon muzzle //
			Impact = WeaponTrace(MuzzleOrigin, MuzzleOrigin + (AdjustedAimDir * WeaponRange));
		}
		else
		{
			// Use the maximum distance as the adjust direction /
			Impact.ImpactPoint = FVector_NetQuantize(EndTrace);
		}
		ProcessInstantHit(Impact, MuzzleOrigin, AdjustedAimDir);

		//TODO: Add Dynamic Spread
		//Just gonna have a fixed spread for now, no differences in aiming or holding down trigger
		//CurrentFiringSpread = FMath::Min(InstantConfig.FiringSpreadMax, CurrentFiringSpread + InstantConfig.FiringSpreadIncrement);
	}
}

/*
FItem AInstantHitWeapon::GetItem()
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


bool AInstantHitWeapon::ShouldDealDamage(AActor* TestActor) const
{
	// If we are an actor on the server, or the local client has authoritative control over actor, we should register damage.
	if (TestActor)
	{
		if (GetNetMode() != NM_Client ||
			TestActor->Role == ROLE_Authority ||
			TestActor->bTearOff)
		{
			return true;
		}
	}

	return false;
}

void AInstantHitWeapon::UpdateItem(FItem item)
{
	SelfItem = item;
	SelfItem.WeaponType = WeaponType;
	SelfItem.AmmoType = AmmoType;
	SelfItem.ItemType = ItemType;
	if (SelfItem.ClipSize != 0) { MaxAmmoPerClip = SelfItem.ClipSize; }
	SelfItem.HitDamage = HitDamage;

}


void AInstantHitWeapon::DealDamage(const FHitResult& Impact, const FVector& ShootDir)
{
	float ActualHitDamage = HitDamage;

	/* Handle special damage location on the zombie body (types are setup in the Physics Asset of the zombie */
	UHDamageType* DmgType = Cast<UHDamageType>(DamageType->GetDefaultObject());
	UPhysicalMaterial * PhysMat = Impact.PhysMaterial.Get();
	if (PhysMat && DmgType)
	{
		//always hitting "body" for now
		/*
		if (PhysMat->SurfaceType == SURFACE_ZOMBIEHEAD)
		{
			ActualHitDamage *= DmgType->GetHeadDamageModifier();
		}
		else if (PhysMat->SurfaceType == SURFACE_ZOMBIELIMB)
		{
			ActualHitDamage *= DmgType->GetLimbDamageModifier();
		}
		*/
	}

	FPointDamageEvent PointDmg;
	PointDmg.DamageTypeClass = DamageType;
	PointDmg.HitInfo = Impact;
	PointDmg.ShotDirection = ShootDir;
	PointDmg.Damage = ActualHitDamage;

	Impact.GetActor()->TakeDamage(PointDmg.Damage, PointDmg, PawnOwner->GetController(), this);
}

void AInstantHitWeapon::ProcessInstantHit(const FHitResult& Impact, const FVector& Origin, const FVector& ShootDir)
{
	if (PawnOwner && PawnOwner->IsLocallyControlled() && GetNetMode() == NM_Client)
	{
		// If we are a client and hit something that is controlled by server
		if (Impact.GetActor() && Impact.GetActor()->GetRemoteRole() == ROLE_Authority)
		{
			// Notify the server of our local hit to validate and apply actual hit damage.
			ServerNotifyHit(Impact, ShootDir);
		}
		else if (Impact.GetActor() == nullptr)
		{
			if (Impact.bBlockingHit)
			{
				ServerNotifyHit(Impact, ShootDir);
			}
			else
			{
				ServerNotifyMiss(ShootDir);
			}
		}
	}

	// Process a confirmed hit.
	ProcessInstantHitConfirmed(Impact, Origin, ShootDir);
}

void AInstantHitWeapon::ProcessInstantHitConfirmed(const FHitResult& Impact, const FVector& Origin, const FVector& ShootDir)
{
	// Handle damage
	if (ShouldDealDamage(Impact.GetActor()))
	{
		DealDamage(Impact, ShootDir);
	}

	// Play FX on remote clients
	if (Role == ROLE_Authority)
	{
		HitImpactNotify = Impact.ImpactPoint;
	}

	// Play FX locally
	if (GetNetMode() != NM_DedicatedServer)
	{
		SimulateInstantHit(Impact.ImpactPoint);
	}
}


void AInstantHitWeapon::SimulateInstantHit(const FVector& ImpactPoint)
{
	const FVector MuzzleOrigin = GetMuzzleLocation();

	/* Adjust direction based on desired crosshair impact point and muzzle location */
	const FVector AimDir = (ImpactPoint - MuzzleOrigin).GetSafeNormal();

	//const FVector EndTrace = MuzzleOrigin + (AimDir * WeaponRange);
	const FVector EndTrace = GetActorLocation() + (AimDir * WeaponRange);
	const FHitResult Impact = WeaponTrace(MuzzleOrigin, EndTrace);

	if (Impact.bBlockingHit)
	{
		SpawnImpactEffects(Impact);
		SpawnTrailEffects(Impact.ImpactPoint);
	}
	else
	{
		SpawnTrailEffects(EndTrace);
	}
}


bool AInstantHitWeapon::ServerNotifyHit_Validate(const FHitResult Impact, FVector_NetQuantizeNormal ShootDir)
{
	return true;
}


void AInstantHitWeapon::ServerNotifyHit_Implementation(const FHitResult Impact, FVector_NetQuantizeNormal ShootDir)
{
	// If we have an instigator, calculate the dot between the view and the shot
	if (Instigator && (Impact.GetActor() || Impact.bBlockingHit))
	{
		const FVector Origin = GetMuzzleLocation();
		const FVector ViewDir = (Impact.Location - Origin).GetSafeNormal();

		const float ViewDotHitDir = FVector::DotProduct(Instigator->GetViewRotation().Vector(), ViewDir);
		if (ViewDotHitDir > AllowedViewDotHitDir)
		{
			// TODO: Check for weapon state

			if (Impact.GetActor() == nullptr)
			{
				if (Impact.bBlockingHit)
				{
					ProcessInstantHitConfirmed(Impact, Origin, ShootDir);
				}
			}
			// Assume it told the truth about static things because we don't move and the hit
			// usually doesn't have significant gameplay implications
			else if (Impact.GetActor()->IsRootComponentStatic() || Impact.GetActor()->IsRootComponentStationary())
			{
				ProcessInstantHitConfirmed(Impact, Origin, ShootDir);
			}
			else
			{
				const FBox HitBox = Impact.GetActor()->GetComponentsBoundingBox();

				FVector BoxExtent = 0.5 * (HitBox.Max - HitBox.Min);
				BoxExtent *= ClientSideHitLeeway;

				BoxExtent.X = FMath::Max(20.0f, BoxExtent.X);
				BoxExtent.Y = FMath::Max(20.0f, BoxExtent.Y);
				BoxExtent.Z = FMath::Max(20.0f, BoxExtent.Z);

				const FVector BoxCenter = (HitBox.Min + HitBox.Max) * 0.5;

				// If we are within client tolerance
				if (FMath::Abs(Impact.Location.Z - BoxCenter.Z) < BoxExtent.Z &&
					FMath::Abs(Impact.Location.X - BoxCenter.X) < BoxExtent.X &&
					FMath::Abs(Impact.Location.Y - BoxCenter.Y) < BoxExtent.Y)
				{
					ProcessInstantHitConfirmed(Impact, Origin, ShootDir);
				}
			}
		}
	}

	// TODO: UE_LOG on failures & rejection
}

bool AInstantHitWeapon::ServerNotifyMiss_Validate(FVector_NetQuantizeNormal ShootDir)
{
	return true;
}


void AInstantHitWeapon::ServerNotifyMiss_Implementation(FVector_NetQuantizeNormal ShootDir)
{
	const FVector Origin = GetMuzzleLocation();
	const FVector EndTrace = Origin + (ShootDir * WeaponRange);

	// Play on remote clients
	HitImpactNotify = EndTrace;

	if (GetNetMode() != NM_DedicatedServer)
	{
		SpawnTrailEffects(EndTrace);
	}
}
void AInstantHitWeapon::OnRep_HitLocation()
{
	// Played on all remote clients
	SimulateInstantHit(HitImpactNotify);
}

/*
void AInstantHitWeapon::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(AInstantHitWeapon, HitImpactNotify, COND_SkipOwner);
}
*/


void AInstantHitWeapon::SpawnImpactEffects(const FHitResult& Impact)
{
	if (ImpactTemplate && Impact.bBlockingHit)
	{
		// TODO: Possible re-trace to get hit component that is lost during replication.

		/* This function prepares an actor to spawn, but requires another call to finish the actual spawn progress. This allows manipulation of properties before entering into the level */
		AImpactEffect* EffectActor = GetWorld()->SpawnActorDeferred<AImpactEffect>(ImpactTemplate, FTransform(Impact.ImpactPoint.Rotation(), Impact.ImpactPoint));
		if (EffectActor)
		{
			EffectActor->SurfaceHit = Impact;
			UGameplayStatics::FinishSpawningActor(EffectActor, FTransform(Impact.ImpactNormal.Rotation(), Impact.ImpactPoint));
		}
	}
}


void AInstantHitWeapon::SpawnTrailEffects(const FVector& EndPoint)
{
	// Keep local count for effects
	//BulletsShotCount++;

	const FVector Origin = GetMuzzleLocation();
	FVector ShootDir = EndPoint - Origin;

	// Only spawn if a minimum distance is satisfied.
	if (ShootDir.Size() < MinimumProjectileSpawnDistance)
	{
		return;
	}

	if (TracerFX)
	{
		ShootDir.Normalize();
		UGameplayStatics::SpawnEmitterAtLocation(this, TracerFX, Origin, ShootDir.Rotation());
	}

	// Only create trails FX by other players.
	//if (PawnOwner && PawnOwner->IsLocallyControlled()){return;}

	if (TrailFX)
	{
		UParticleSystemComponent* TrailPSC = UGameplayStatics::SpawnEmitterAtLocation(this, TrailFX, Origin);
		if (TrailPSC)
		{
			TrailPSC->SetVectorParameter(TrailSourceParam, Origin);
			TrailPSC->SetVectorParameter(TrailTargetParam, EndPoint);
		}
	}
}





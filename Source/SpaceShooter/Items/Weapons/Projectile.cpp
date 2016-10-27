
#include "SpaceShooter.h"
#include "Items/Weapons/HDamageType.h"
#include "Characters/BaseTrainer.h"
#include "Projectile.h"
#include "Items/Weapons/ImpactEffect.h"
#include "GameFramework/ProjectileMovementComponent.h"

AProjectile::AProjectile() 
{

	HitDamage = 1.0;
	DamageRadius = 500;
	HitImpulseStrength = 100;
	bSticky = false;
	bBounce = false;
	BounceLimit = 1;
	CurrentBounce = 0;
	bStuck = false;
	bExplosive = false;

	TrailScale = FVector(1,1,1);

	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;

	Mesh = CreateOptionalDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh0"));
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


}

void AProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SpawnTrailEffects();

}

//UGameplayStatics::SpawnEmitterAtLocation(this, TracerFX, Origin, ShootDir.Rotation());
void AProjectile::SpawnTrailEffects()
{
	if (TrailFX)
	{
		//UGameplayStatics::SpawnEmitterAtLocation(this, TracerFX, Origin, ShootDir.Rotation());
		UParticleSystemComponent* trails = UGameplayStatics::SpawnEmitterAttached(TrailFX, Mesh);
		trails->SetWorldScale3D(TrailScale);
	}

}

void AProjectile::Stick(UPrimitiveComponent* OtherComp)
{
	this->AttachToComponent(OtherComp, FAttachmentTransformRules::KeepRelativeTransform);
}

void AProjectile::SpawnImpactEffects()
{
	if (ExplosionFX)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionFX, FTransform(GetActorRotation(), GetActorLocation()));
	}
	if (ExplosionSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ExplosionSound, GetActorLocation());
	}


	/*
	if (Impact.IsValidBlockingHit())
	{
		if (ImpactTemplate && Impact.bBlockingHit && ImpactTemplate)
		{
			// TODO: Possible re-trace to get hit component that is lost during replication.

			// This function prepares an actor to spawn, but requires another call to finish the actual spawn progress. This allows manipulation of properties before entering into the level
			AImpactEffect* EffectActor = GetWorld()->SpawnActorDeferred<AImpactEffect>(ImpactTemplate, FTransform(Impact.ImpactPoint.Rotation(), Impact.ImpactPoint));
			if (EffectActor)
			{
				EffectActor->SurfaceHit = Impact;
				UGameplayStatics::FinishSpawningActor(EffectActor, FTransform(Impact.ImpactNormal.Rotation(), Impact.ImpactPoint));
			}

		}
	}
	else
	{
		//GEngine->AddOnScreenDebugMessage(0, 1, FColor::Red, "Spawn impact in projectile, no blocking hit?!?");

	}
	*/

}

void AProjectile::Detonate()
{
	SpawnImpactEffects();
	UGameplayStatics::ApplyRadialDamage(GetWorld(), HitDamage, GetActorLocation(), DamageRadius, DamageType, IgnoreDamageActors, this, Instigator->GetController(), false, ECC_GameTraceChannel2);


}
void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && Cast<ABaseTrainer>(OtherActor))
	{
		if (bSticky)
		{
			GEngine->AddOnScreenDebugMessage(0, 1, FColor::Yellow, "stick projectile hit base trainer, should stick then start fuse to detonate, plasma!");
			//
			//Stick(HitComp);
		}
		
		if (!bExplosive)
		{
			if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp->IsSimulatingPhysics())
			{
				OtherComp->AddImpulseAtLocation(GetVelocity() * HitImpulseStrength, GetActorLocation());
			}

			SpawnImpactEffects();
			float ActualHitDamage = HitDamage;

			/* Handle special damage location on the zombie body (types are setup in the Physics Asset of the zombie */
			UHDamageType* DmgType = Cast<UHDamageType>(DamageType->GetDefaultObject());
			UPhysicalMaterial * PhysMat = Hit.PhysMaterial.Get();
			FPointDamageEvent PointDmg;
			PointDmg.DamageTypeClass = DamageType;
			PointDmg.HitInfo = Hit;
			PointDmg.ShotDirection = GetVelocity().GetSafeNormal();
			PointDmg.Damage = ActualHitDamage;

			Hit.GetActor()->TakeDamage(PointDmg.Damage, PointDmg, Instigator->GetController(), this);
		}
		else
		{
			Detonate();
		}
		
		Destroy();

	}


	if (bBounce)
	{
		CurrentBounce++;
	}




	if (bSticky)
	{
		//	UPhysicalMaterial * PhysMat = Hit.PhysMaterial.Get();
		// if (stickylist.has(physmat){ sticky}
		//else
		if (!bStuck)
		{
			Stick(OtherComp);
		}
	}
	else if ((CurrentBounce >= BounceLimit || !bBounce) && !bSticky)
	{
		//apply impulse if physics if NOT gonna explode
		if (!bExplosive)
		{
			if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp->IsSimulatingPhysics())
			{
				OtherComp->AddImpulseAtLocation(GetVelocity() * HitImpulseStrength, GetActorLocation());
			}
			SpawnImpactEffects();
		}
		else
		{
			Detonate();
		}
		
		Destroy();

	}
	else if (CurrentBounce <= BounceLimit && bBounce)
	{
		//apply impulse and keep on chuggin
	}

	/*
	UGameplayStatics::ApplyRadialDamage(GetWorld(), HitDamage, GetActorLocation(), DamageRadius, DamageType, IgnoreDamageActors, this, Instigator->GetController(), false, ECC_GameTraceChannel2);
	Destroy();
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
		if (Cast<ABaseTrainer>(OtherActor))
		{
			// Handle special damage location on the zombie body (types are setup in the Physics Asset of the zombie/
			UHDamageType* DmgType = Cast<UHDamageType>(DamageType->GetDefaultObject());
			UPhysicalMaterial * PhysMat = Hit.PhysMaterial.Get();
			if (PhysMat && DmgType)
			{
				//always hitting "body" for now
				//if (PhysMat->SurfaceType == SURFACE_ZOMBIEHEAD)
				//{
				//ActualHitDamage *= DmgType->GetHeadDamageModifier();
				//}
				//else if (PhysMat->SurfaceType == SURFACE_ZOMBIELIMB)
				//{
				//ActualHitDamage *= DmgType->GetLimbDamageModifier();
				//}
				
			}
			
			
		}
	}
	*/
}

void AProjectile::OnDestroy()
{
	Destroy();
}

float AProjectile::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	// Call the base class - this will tell us how much damage to apply  
	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	/*
	if (bExplosive)
	{
		Detonate();
	}
	Destroy();
	*/
	
	
	//ApplyDamageMomentum(ActualDamage, DamageEvent, this, DamageCauser);
	return ActualDamage;

}
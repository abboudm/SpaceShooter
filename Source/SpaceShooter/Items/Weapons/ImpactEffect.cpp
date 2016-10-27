// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceShooter.h"
#include "Components/ClimbingPawnMovementComponent.h"
#include "ImpactEffect.h"

// Sets default values
AImpactEffect::AImpactEffect()
{
	bAutoDestroyWhenFinished = true;
	/* Can ever tick is required to trigger bAutoDestroyWhenFinished, which is checked in AActor::Tick */
	PrimaryActorTick.bCanEverTick = true;

	DecalLifeSpan = 0.0f;
	DecalSize = 5.0f;

	/*
	static ConstructorHelpers::FObjectFinder<UParticleSystem> DefaultImpactParticleOb(TEXT("ParticleSystem'/Game/Effects/P_AssaultRifle_IH.P_AssaultRifle_IH'"));
	if (!MetalFX)
	{
		MetalFX = DefaultImpactParticleOb.Object;
	}
	*/
}

void AImpactEffect::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	/* Figure out what we hit (SurfaceHit is setting during actor instantiation in weapon class) */
	UPhysicalMaterial* HitPhysMat = SurfaceHit.PhysMaterial.Get();
	EPhysicalSurface HitSurfaceType = UPhysicalMaterial::DetermineSurfaceType(HitPhysMat);

	UParticleSystem* ImpactFX = GetImpactFX(HitSurfaceType);
	if (ImpactFX)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, ImpactFX, GetActorLocation(), GetActorRotation());
	}

	USoundCue* ImpactSound = GetImpactSound(HitSurfaceType);
	if (ImpactSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation());
	}

	if (DecalMaterial && HitPhysMat)
	{

		
		FRotator RandomDecalRotation = SurfaceHit.ImpactNormal.Rotation();
		RandomDecalRotation.Roll = FMath::FRandRange(-180.0f, 180.0f);
		//RandomDecalRotation.Yaw = FMath::FRandRange(-180.0f, 180.0f);

		//UGameplayStatics::SpawnDecalAttached(DecalMaterial, FVector(DecalSize, DecalSize, 1.0f),
		UDecalComponent* dd = UGameplayStatics::SpawnDecalAttached(DecalMaterial, FVector(DecalSize, DecalSize, DecalSize),
			SurfaceHit.Component.Get(), SurfaceHit.BoneName,
			SurfaceHit.ImpactPoint, RandomDecalRotation, EAttachLocation::KeepWorldPosition,
			DecalLifeSpan);

		//dd->FadeScreenSize = 0.1;	//default
		dd->FadeScreenSize = 0.0;	//10,000  idk big, but fuck it for now
		
	}

}


UParticleSystem* AImpactEffect::GetImpactFX(EPhysicalSurface SurfaceType) const
{
	return MetalFX;
	/*
	switch (SurfaceType)
	{
	case SURFACE_DEFAULT:
		return DefaultFX;
	case SURFACE_FLESH:
		return PlayerFleshFX;
	case SURFACE_ZOMBIEBODY:
	case SURFACE_ZOMBIEHEAD:
	case SURFACE_ZOMBIELIMB:
		return ZombieFleshFX;
	default:
		return nullptr;
	}
	*/
}


USoundCue* AImpactEffect::GetImpactSound(EPhysicalSurface SurfaceType) const
{
	return MetalSound;
	/*
	switch (SurfaceType)
	{
	case SURFACE_DEFAULT:
		return DefaultSound;
	case SURFACE_FLESH:
		return PlayerFleshSound;
	case SURFACE_ZOMBIEBODY:
	case SURFACE_ZOMBIEHEAD:
	case SURFACE_ZOMBIELIMB:
		return ZombieFleshSound;
	default:
		return nullptr;
	}
	*/
}














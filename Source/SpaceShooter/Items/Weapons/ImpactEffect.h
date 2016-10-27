// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ImpactEffect.generated.h"

UCLASS(ABSTRACT, BlueprintAble)
class SPACESHOOTER_API AImpactEffect : public AActor
{
	GENERATED_BODY()
	
public:	
	
	UParticleSystem* GetImpactFX(EPhysicalSurface SurfaceType) const;

	USoundCue* GetImpactSound(EPhysicalSurface SurfaceType) const;
	AImpactEffect();
	virtual void PostInitializeComponents() override;

	/* FX spawned on standard materials */
	UPROPERTY(EditDefaultsOnly)
		UParticleSystem* MetalFX;

	UPROPERTY(EditDefaultsOnly)
		UParticleSystem* WoodFX;

	UPROPERTY(EditDefaultsOnly)
		UParticleSystem* PlayerFX;

	UPROPERTY(EditDefaultsOnly)
		USoundCue* MetalSound;

	UPROPERTY(EditDefaultsOnly)
		USoundCue* WoodSound;

	UPROPERTY(EditDefaultsOnly)
		USoundCue* PlayerSound;

	UPROPERTY(EditDefaultsOnly, Category = "Decal")
		UMaterial* DecalMaterial;

	UPROPERTY(EditDefaultsOnly, Category = "Decal")
		float DecalSize;

	UPROPERTY(EditDefaultsOnly, Category = "Decal")
		float DecalLifeSpan;

	FHitResult SurfaceHit;


	
	
};

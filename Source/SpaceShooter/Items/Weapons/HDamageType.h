// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/DamageType.h"
#include "HDamageType.generated.h"

/**
 * 
 */
UCLASS()
class SPACESHOOTER_API UHDamageType : public UDamageType
{
	GENERATED_BODY()
		UHDamageType(const FObjectInitializer& ObjectInitializer);

	/* Can player die from this damage type (eg. players don't die from hunger) */
	UPROPERTY(EditDefaultsOnly)
		bool bCanDieFrom;

	/* Damage modifier for headshot damage */
	UPROPERTY(EditDefaultsOnly)
		float HeadDmgModifier;

	UPROPERTY(EditDefaultsOnly)
		float LimbDmgModifier;
	
public:
	bool GetCanDieFrom();

	float GetHeadDamageModifier();

	float GetLimbDamageModifier();
	
};

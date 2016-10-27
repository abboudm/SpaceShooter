// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceShooter.h"
#include "HDamageType.h"



UHDamageType::UHDamageType(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	/* We apply this modifier based on the physics material setup to the head of the enemy PhysAsset */
	HeadDmgModifier = 2.0f;
	LimbDmgModifier = 0.5f;
	bCanDieFrom = true;
}

bool UHDamageType::GetCanDieFrom()
{
	return bCanDieFrom;
}


float UHDamageType::GetHeadDamageModifier()
{
	return HeadDmgModifier;
}

float UHDamageType::GetLimbDamageModifier()
{
	return LimbDmgModifier;
}

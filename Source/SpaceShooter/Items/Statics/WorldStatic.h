// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GameFramework/Actor.h"
#include "WorldStatic.generated.h"





UCLASS(Blueprintable,BlueprintType)
class SPACESHOOTER_API AWorldStatic : public AActor
{
	GENERATED_BODY()
		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	
protected:
	AWorldStatic(const FObjectInitializer& ObjectInitializer);
	virtual void PostInitializeComponents() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USphereComponent* Sphere;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
	class UInteractionComponent* Interaction;
	/*

	Interaction = CreateDefaultSubobject<UInteractionComponent>(TEXT("Interaction"));
	AddOwnedComponent(Interaction);
	Interaction->InteractionType = EInteractionType::Character;
	*/


	//UPROPERTY(EditDefaultsOnly, Category = "Item")
		//FName Name;

	UStaticMeshComponent* GetMesh();

	virtual void BeginPlay() override;
	
	virtual float TakeDamage(
		float DamageAmount,
	struct FDamageEvent const & DamageEvent,
	class AController * EventInstigator,
		AActor * DamageCauser) override;

private:

	
	
};

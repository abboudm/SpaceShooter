// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Items/Item.h"
//#include "Items/Equipable.h"

#include "Lootable.generated.h"


UCLASS(Blueprintable,BlueprintType,Abstract)
class SPACESHOOTER_API ALootable : public AActor
{
	GENERATED_BODY()
		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

		
protected:
	ALootable(const FObjectInitializer& ObjectInitializer);
	virtual void PostInitializeComponents() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USphereComponent* Sphere;
	/*
	*/


public:	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
	class UInteractionComponent* Interaction;
	/*

	Interaction = CreateDefaultSubobject<UInteractionComponent>(TEXT("Interaction"));
	AddOwnedComponent(Interaction);
	Interaction->InteractionType = EInteractionType::Character;
	*/


	UPROPERTY(EditDefaultsOnly, Category = "Item")
		FName Name;
	UPROPERTY(EditDefaultsOnly, Category = "Item")
		FString Description;
	UPROPERTY(EditDefaultsOnly, Category = "Item")
		int Value;
	UPROPERTY(EditDefaultsOnly, Category = "Item")
		float Weight;
	UPROPERTY(EditDefaultsOnly, Category = "Item")
		EItemType ItemType;
	UPROPERTY(EditDefaultsOnly, Category = "Item")
		ELootType LootType;
	UPROPERTY(EditDefaultsOnly, Category = "Item")
	   TSubclassOf<class AEquipable> EquipClass;
	UPROPERTY(EditDefaultsOnly, Category = "Item")
		int Quantity;
	virtual void UpdateItem(FItem item);
	/*
	*/
	/*
	*/
	UPROPERTY()
	FItem SelfItem;
	UFUNCTION(BlueprintCallable, Category = "Item")
	virtual FItem GetItem();
	FItem SafeGetItem();
	UStaticMeshComponent* GetMesh();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser);


private:

	
	
};

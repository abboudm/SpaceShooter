// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Items/Item.h"
//#include "Items/Lootable.h
#include "Equipable.generated.h"


/*
//UPROPERTY(EditAnywhere, BlueprintReadWrite)
//EItemType ItemType;
UENUM(BlueprintType)
enum class EItemType : uint8
{

	IT_RIFLE		UMETA(DisplayName = "Rifle"),
	IT_PISTOL		UMETA(DisplayName = "Pistol"),
	IT_MISSLE		UMETA(DisplayName = "Missle"),
	IT_MELEE		UMETA(DisplayName = "Melee"),
	IT_NONE		UMETA(DisplayName = "None")

};
*/


UCLASS(Blueprintable,BlueprintType, Abstract)
class SPACESHOOTER_API AEquipable : public AActor
{
	GENERATED_BODY()
		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

		
protected:
	AEquipable(const FObjectInitializer& ObjectInitializer);
	virtual void PostInitializeComponents() override;

	/*Owner as ABaseTrainer*/
	//UPROPERTY(Transient, ReplicatedUsing OnRep_MyPawn)
	class ABaseTrainer* PawnOwner;

	/** The main skeletal mesh associated with this Character (optional sub-object). */
	//UPROPERTY(VisibleDefaultsOnly, Cateory = Mesh)
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* Mesh;

	USkeletalMesh* DefaultMesh;
	//UFUNCTION()
	void OnRep_MyPawn();

	void DetachMeshFromPawn();
	virtual void OnEquipFinished();
	bool IsEquipped() const;
	bool IsAttachedToPawn() const;
	TSubclassOf<class ALootable> LootClass;


public:	
	virtual void Tick(float DeltaSeconds) override;
	
	void SetupSelfItem();


	UPROPERTY(EditDefaultsOnly, Category = "Item")
		FName Name;
	UPROPERTY(EditDefaultsOnly, Category = "Item")
		FString Description;
	UPROPERTY(EditDefaultsOnly, Category = "Item")
		int Value;
	UPROPERTY(EditDefaultsOnly, Category = "Item")
		float Weight;
	UPROPERTY(EditDefaultsOnly, Category = "Item")
		EEquipableType EquipType;
	UPROPERTY(EditDefaultsOnly, Category = "Item")
		EItemType ItemType;
	//UPROPERTY(EditDefaultsOnly, Category = "Item")

	FTimerHandle EquipFinishedTimerHandle;
	void AttachMeshToPawn(FName ItemSocket);

	UFUNCTION(BlueprintCallable, Category = "Equipable")
		USkeletalMeshComponent* GetMesh() const;

	virtual void OnUnEquip();
	virtual void OnEquip(bool bPlayAnimation);
	
	void SetOwningPawn(ABaseTrainer* NewOwner);
	UFUNCTION(BlueprintCallable, Category = "Equipable")
		class ABaseTrainer* GetPawnOwner() const;

	virtual void OnAddToInventory(ABaseTrainer* NewOwner);
	virtual void OnRemoveFromInventory();

	//UPROPERTY(EditDefaultsOnly, Category "Item")
	//TSubclassOf<class AEquipablePickup> LootCompanion; //this is the Item->Loot class that would drop from the final product class aka BattleRifle_instanthit <-> BattleRifle_loot

	

	UFUNCTION(BlueprintNativeEvent, meta = (DisplayName = "OnPrimaryTrigger"))
		void ReceiveOnPrimaryTrigger();
	UFUNCTION(BlueprintNativeEvent, meta = (DisplayName = "OnPrimaryTrigger"))
		void ReceiveOnStopPrimaryTrigger();
	
	UFUNCTION(BlueprintNativeEvent, meta = (DisplayName = "OnSecondaryTrigger"))
		void ReceiveOnSecondaryTrigger();

	virtual void BeginPlay() override;
	virtual void OnPrimaryTrigger();
	virtual void OnStopPrimaryTrigger();
	virtual void OnSecondaryTrigger();

	float GetEquipStartedTime() const;
	float GetEquipDuration() const;
	float EquipStartedTime;
	float EquipDuration;
	bool bIsEquipped;
	bool bPendingEquip;
	
	//-------------------------------------
	//Self Item is the item thats created / sent out
	//Some Equipables will fill out Self Item in construction and just return it on getitem
	//weapons with clip sizes then might only fill out half, with the rest during the getitem function
	UPROPERTY()
	FItem SelfItem;
	UFUNCTION(BlueprintCallable, Category = "Item")
	virtual FItem GetItem();
	FItem SafeGetItem();
	virtual void UpdateItem(FItem item);


private:

	
	
};

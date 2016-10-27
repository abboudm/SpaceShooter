// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACESHOOTER_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();
	//-----------------------------------------------------------------------------------------------
	//Blueprint Edit
	UPROPERTY(Category = "Attributes", EditAnywhere, BlueprintReadWrite)
		float MaxHealth;
	UPROPERTY(Category = "Attributes", EditAnywhere, BlueprintReadWrite)
		float MaxShield;
	UPROPERTY(Category = "Attributes", BlueprintReadOnly)
		bool Alive;
	UPROPERTY(Category = "Attributes", BlueprintReadOnly)
		float Health;
	UPROPERTY(Category = "Attributes", BlueprintReadOnly)
		float Shield;
	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	UFUNCTION(BlueprintCallable, Category = "Health")
		void TakeDamage(float damage);

private:

	
};

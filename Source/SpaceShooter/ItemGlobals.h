
#pragma once

#include "Engine/DeveloperSettings.h"

#include "Items/Equipable.h"
#include "Items/Lootable.h"
#include "Items/Item.h"
#include "ItemGlobals.generated.h"





USTRUCT(BlueprintType)
struct FMetaItem
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EItemType ItemType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Quantity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Value;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Weight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class AEquipable> EquipClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class ALootable> LootClass;
	
};

UCLASS(config=Game, defaultconfig)
class SPACESHOOTER_API UItemGlobals : public UDeveloperSettings
{
	GENERATED_BODY()

public:

	UItemGlobals(const FObjectInitializer& ObjectInitializer);
	UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Item List")
		TArray<FMetaItem> ItemList;

	

  /*
	FORCEINLINE const FRichCurve* GetAnalogCursorAccelerationCurve() const
	{
		return AnalogCursorAccelerationCurve.GetRichCurveConst();
	}
	
	FORCEINLINE float GetMaxAnalogCursorSpeed() const
	{
		return MaxAnalogCursorSpeed;
	}

	FORCEINLINE float GetMaxAnalogCursorSpeedWhenHovered() const
	{
		return MaxAnalogCursorSpeedWhenHovered;
	}

	FORCEINLINE float GetAnalogCursorDragCoefficient() const
	{
		return FMath::Min<float>(AnalogCursorDragCoefficientWhenHovered, AnalogCursorDragCoefficient);
	}

	FORCEINLINE float GetAnalogCursorDragCoefficientWhenHovered() const
	{
		return FMath::Max<float>(AnalogCursorDragCoefficientWhenHovered, AnalogCursorDragCoefficient);
	}

	FORCEINLINE float GetMinAnalogCursorSpeed() const
	{
		return MinAnalogCursorSpeed;
	}

	FORCEINLINE float GetAnalogCursorAccelerationMultiplier() const
	{
		return AnalogCursorAccelerationMultiplier;
	}

	FORCEINLINE float GetAnalogCursorDeadZone() const
	{
		return AnalogCursorDeadZone;
	}

	FORCEINLINE float GetAnalogCursorSize() const
	{
		return FMath::Max<float>(AnalogCursorSize, 1.0f);
	}

	FORCEINLINE FVector2D GetAnalogCursorSizeVector() const
	{
		return FVector2D(GetAnalogCursorSize(), GetAnalogCursorSize());
	}

	FORCEINLINE float GetAnalogCursorRadius() const
	{
		return GetAnalogCursorSize() / 2.0f;
	}

	FORCEINLINE bool GetUseEngineAnalogCursor() const
	{
		return bUseEngineAnalogCursor;
	}

	FORCEINLINE bool GetAnalogCursorNoAcceleration() const
	{
		return bAnalogCursorNoAcceleration;
	}

	FORCEINLINE void SetAnalogCursor(TSharedPtr<FGameAnalogCursor> InAnalogCursor)
	{
		AnalogCursor = InAnalogCursor;
	}

	FORCEINLINE TSharedPtr<FGameAnalogCursor> GetAnalogCursor() const
	{
		return AnalogCursor.Pin();
	}

  */
private:
	//UPROPERTY(config, EditAnywhere, Category = "Analog Cursor", meta=( XAxisName="Strength", YAxisName="Acceleration" ))
	//FRuntimeFloatCurve AnalogCursorAccelerationCurve;

	//UPROPERTY(config, EditAnywhere, Category = "Analog Cursor", meta = (ClampMin = "1.0"))
	//float MaxAnalogCursorSpeed;

	// Analog Cursor
	//TWeakPtr<FGameAnalogCursor> AnalogCursor;
};

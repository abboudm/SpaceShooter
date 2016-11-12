#pragma once

#include "Engine/GameInstance.h"
#include "ItemGlobals.h"
#include "Items/Item.h"
#include "SpaceGameInstance.generated.h" 

UCLASS()
class SPACESHOOTER_API USpaceGameInstance : public UGameInstance
{
  GENERATED_BODY()

public:
    USpaceGameInstance(const FObjectInitializer& ObjectInitializer);
	UFUNCTION(BlueprintCallable, Category = "Item List")
		TArray<FMetaItem> GetItemList() const;
	UFUNCTION(BlueprintCallable, Category = "Item List")
		FItem GetItem(FMetaItem MetaItem);
private:
	TArray<FMetaItem> MasterItemList;
    //uprops
};

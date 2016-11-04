#pragma once

#include "Runtime/Engine/Classes/Engine/LevelScriptActor.h"

#include "BaseLevel.generated.h"

UCLASS()
class ABaseLevel : public ALevelScriptActor
{
	GENERATED_UCLASS_BODY()

		//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = SolusLevel)
		//FName SolusLevelName;

public:
	UFUNCTION(exec)
		void TestCommand();
	
	//UFUNCTION(BlueprintCallable, Category = "Solus Level Save System")
		//void SolusLevel__UpdateLevelSaveData();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void Tick(float DeltaSeconds) override;
	/*
	*/

};
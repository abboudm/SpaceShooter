//Copyright (c) 2016 Artem A. Mavrin and other contributors

#pragma once
#include "BehaviorTree/BTTaskNode.h"
#include "WidgetComponent.h"
#include "DialogueSystem/BTDialogueTypes.h"
#include "Camera/CameraComponent.h"
#include "BTTask_WaitAnswer.generated.h"



/**
* Wait dialogue task node.
*/
UCLASS()
class SPACESHOOTER_API UBTTask_WaitAnswer : public UBTTaskNode
{
	GENERATED_UCLASS_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual FString GetStaticDescription() const override;

	void SaveDefaultCameraDataForAll(UBTNode* Node);
	void SaveDefaultCameraData(UCameraComponent* PlayerCamera);
	void SetAnswer(FText Text);
	void ClearAnswer();
	FText GetAnswer();

	UFUNCTION(BlueprintCallable, Category = "DialogueSystem|Dialogue")
	void SetAnswer(UDialogueButton* DialogueButton);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "DialogueSystem|Dialogue")
	float GetTimer();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "DialogueSystem|Dialogue")
	bool HasTimer();

	/** Dialogue widget */
	UPROPERTY(EditInstanceOnly, Category = Widget)
	FBlackboardKeySelector DialogueWidget;

	/** Input Mode */
	UPROPERTY(EditInstanceOnly, Category = Widget)
	EWidggetInputMode InputMode;

	/** Time to make a choice, -1 is off */
	UPROPERTY(EditInstanceOnly, Category = Widget)
	float Timer;

	/** Name of Widget where will be show questions */
	UPROPERTY(EditInstanceOnly, Category = Widget)
	FName DialogueQuestionsSlotName;

	/** Enable to navigate using a gamepad or keyboard */
	UPROPERTY(EditInstanceOnly, Category = Widget)
	bool bUseGamepad;

	/** Dialogue camera options */
	UPROPERTY(EditInstanceOnly, Category = Dialogue)
	FBTDialogueCameraOptions DialogueCameraOptions;

	/** Dialogue cinematic options */
	UPROPERTY(EditInstanceOnly, Category = Dialogue)
	FBTDialogueCinematicOptions DialogueCinematicOptions;

	FVector DefaultCameraLocation;
	FRotator DefaultCameraRotation;

private:
	FText SelectedAnswer;
	bool bAnswerDone;
	UCameraComponent* PlayerCamera;
	UBlackboardComponent* BlackboardComp;
	UWidgetTree* WidgetTree;
	UWidgetComponent* WidgetComp;
	float TimerCount;
	bool bIsUserWidget;
	UUserWidget* Widget;
	AMatineeActor* MatineeActor;

public:
	APlayerController* PlayerController;

#if WITH_EDITOR
	virtual FName GetNodeIconName() const override;
#endif // WITH_EDITOR

protected:

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};

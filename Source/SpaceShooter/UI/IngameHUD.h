
#pragma once

#include "SlateBasics.h"
#include "Items/Item.h"
#include "Characters/PlayerCharacterController.h"
#include "Characters/Trainer.h"
#include "UI/SpaceHUD.h"
// Lays out and controls the Main Menu UI for our tutorial.
class SPACESHOOTER_API SIngameHUD : public SCompoundWidget
{

public:
	SLATE_BEGIN_ARGS(SIngameHUD)
	{}
	SLATE_ARGUMENT(TWeakObjectPtr<class ASpaceHUD>, ParentHUD)
	SLATE_ARGUMENT(APlayerCharacterController*, PC)
	SLATE_ARGUMENT(ATrainer*, PT)
		SLATE_END_ARGS()

		void Construct(const FArguments& args);
	const struct FGlobalStyle* MenuStyle;
	APlayerCharacterController* PC;
	ATrainer*					PT;
	//Can use this to store reference to children widgets
	//TSharedPtr<SVerticalBox> VBox;

	TAttribute<FText> ClipCount;
	TAttribute<FText> AmmoCount;

	FText GetAmmoCount() const;
	FText GetClipCount() const;

	//TWeakObjectPtr<class ASpaceHUD> ParentHUD;




};
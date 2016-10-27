
#include "SpaceShooter.h"
#include "IngameHUD.h"
#include "Components/ClimbingPawnMovementComponent.h"
#include "UI/Styles/GlobalMenuStyle.h"
#include "UI/Styles/MenuStyles.h"
#include "Engine.h"
#include "Characters/Trainer.h"
#include "Characters/PlayerCharacterController.h"
#include "Items/Item.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SIngameHUD::Construct(const FArguments& args)
{
	PC = args._PC;
	PT = args._PT;
	//PC = Cast<APlayerCharacterController>(GEngine->GetWorld()->GetFirstPlayerController());
	//PC = Cast<APlayerCharacterController>(UGameplayStatics::GetPlayerController();
	//PT = Cast<ATrainer>(PC->GetPawn());
	//ParentHUD = args._ParentHUD;
	MenuStyle = &FMenuStyles::Get().GetWidgetStyle<FGlobalStyle>("Global");
	ClipCount.Bind(this, &SIngameHUD::GetClipCount);
	AmmoCount.Bind(this, &SIngameHUD::GetAmmoCount);

	/*
	
	*/
	
	ChildSlot
	[
		SNew(SOverlay)
		+ SOverlay::Slot()
		.HAlign(HAlign_Right)
		.VAlign(VAlign_Bottom)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			[
				SNew(STextBlock)
				.TextStyle(&MenuStyle->HUDTextStyle)
				.Text(ClipCount)
			]
			+ SVerticalBox::Slot()
			[
				SNew(STextBlock)
				.TextStyle(&MenuStyle->HUDTextStyle)
				.Text(AmmoCount)
			]
		]
	];
		/*
		+ SOverlay::Slot()
		.HAlign(HAlign_Left)
		.VAlign(VAlign_Top)
		[
			SNew(STextBlock)
			.TextStyle(&MenuStyle->MenuTitleStyle)
			.Text(FText::FromString("HEALTH: 100"))
		]
	/*
		*/

}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION




FText SIngameHUD::GetAmmoCount() const
{
	//ATrainer* PT = Cast<ATrainer>(ParentHUD->GetOwningPawn());
	ATrainer* pt = Cast<ATrainer>(PC->GetPawn());
	if (pt)
	{

		if (pt->hasCurrentItem())
		{
			FString out = "::";
			out.Append(FString::FromInt(pt->GetAmmo(pt->GetCurrentItem().AmmoType)));
			out.Append("::");
			//out.Append(pt->GetCurrentItem().Name.ToString());
			return FText::FromString(out);
		}
		else
		{
			FString out = "::";
			return FText::FromString(out);
		}
	}
	else
	{
		FString out = "NOPT";
		return FText::FromString(out);
	}
}

FText SIngameHUD::GetClipCount() const 
{ 
	//ATrainer* PT = Cast<ATrainer>(ParentHUD->GetOwningPawn());
	ATrainer* pt = Cast<ATrainer>(PC->GetPawn());
	if (pt)
	{

		if (pt->hasCurrentItem())
		{
			FString out = "::";
			out.Append(FString::FromInt(pt->GetCurrentItem().AmmoInClip));
			out.Append("::");
			out.Append(pt->GetCurrentItem().Name.ToString());
			return FText::FromString(out); 
		}
		else
		{
			FString out = "::";
			return FText::FromString(out);
		}
	}
	else 
	{
		FString out = "NOPT";
		return FText::FromString(out);
	}
}


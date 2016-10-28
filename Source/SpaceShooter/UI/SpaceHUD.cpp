// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
 
#include "SpaceShooter.h"
#include "SpaceHUD.h"
#include "UI/IngameHUD.h"
 #include "Engine.h"
#include "Components/InventoryComponent.h"
#include "Characters/PlayerCharacterController.h"
#include "Characters/Trainer.h"
#include "Items/Lootable.h"
#include "UI/Styles/GlobalMenuStyle.h"
#include "UI/Styles/MenuStyles.h"
const float ASpaceHUD::MinHudScale = 0.5f;


ASpaceHUD::ASpaceHUD(const class FObjectInitializer& PCIP) : Super(PCIP)
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> HUDMainTextureOb(TEXT("/Game/UI/HUD/HUDMain"));
	HUDMainTexture = HUDMainTextureOb.Object;
	Crosshair[0] = UCanvas::MakeIcon(HUDMainTexture, 43, 402, 25, 9); // left
	Crosshair[1] = UCanvas::MakeIcon(HUDMainTexture, 88, 402, 25, 9); // right
	Crosshair[2] = UCanvas::MakeIcon(HUDMainTexture, 74, 371, 9, 25); // top
	Crosshair[3] = UCanvas::MakeIcon(HUDMainTexture, 74, 415, 9, 25); // bottom
	Crosshair[4] = UCanvas::MakeIcon(HUDMainTexture, 75, 403, 7, 7); // center
	
	static ConstructorHelpers::FObjectFinder<UFont> NormalFontOb(TEXT("/Game/UI/Styles/Raleway-Light.Raleway-Light"));
	NormalFont = NormalFontOb.Object;
	HUDDark = FColor(250, 180, 250, 255);
}






void ASpaceHUD::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	//SAssignNew(GameHUD, SIngameHUD).PC((PlayerCharacterController*) GetOwningPlayerController());
	SAssignNew(GameHUD, SIngameHUD)
		.PC((APlayerCharacterController*)GetOwningPlayerController())
		.PT(Cast<ATrainer>(GetOwningPawn()));


	MenuStyle = &FMenuStyles::Get().GetWidgetStyle<FGlobalStyle>("Global");




	if (GEngine->IsValidLowLevel())
	{
		GEngine->GameViewport->AddViewportWidgetContent(SNew(SWeakWidget).PossiblyNullContent(GameHUD.ToSharedRef()));
	}
}


void ASpaceHUD::DrawHUD()
{
	if (!Cast<APlayerCharacterController>(GetOwningPlayerController())->IsGameMenuUp())
	{

		Super::DrawHUD();
		if (Canvas == nullptr)
		{
			return;
		}
		/*
		*/
		ScaleUI = Canvas->ClipY / 1080.0f;
		float TextScale = 1.0f;
		// enforce min
		ScaleUI = FMath::Max(ScaleUI, MinHudScale);
		DrawCrosshair();
		DrawActionIcon();
	}

		

}

	
void ASpaceHUD::DrawActionIcon()
{
	ATrainer* pt = Cast<ATrainer>(GetOwningPlayerController()->GetPawn());
	if (pt)
	{
		AActor* reachable = pt->GetReachable();
		
		
		if (Cast<ALootable>(reachable))
		{
			FItem item = Cast<ALootable>(reachable)->GetItem();

			FCanvasTextItem TextItem(FVector2D::ZeroVector, FText::GetEmpty(), NormalFont, HUDDark);
			TextItem.EnableShadow(FLinearColor::Black);


			TextItem.Text = FText::FromName(item.Name);
			TextItem.Scale = FVector2D(2, 2);
			float CenterX = Canvas->ClipX / 2;
			float CenterY = Canvas->ClipY / 2;

			Canvas->DrawItem(TextItem, CenterX - 50, CenterY + 50);

		}
		else if (Cast<ABaseTrainer>(reachable))
		{
			FCanvasTextItem TextItem(FVector2D::ZeroVector, FText::GetEmpty(), NormalFont, HUDDark);
			TextItem.EnableShadow(FLinearColor::Black);


			TextItem.Text = FText::FromString("TradeItems!");
			TextItem.Scale = FVector2D(2, 2);
			float CenterX = Canvas->ClipX / 2;
			float CenterY = Canvas->ClipY / 2;

			Canvas->DrawItem(TextItem, CenterX - 50, CenterY + 50);

		}


	}

	/*
	FCanvasTextItem TextItem(FVector2D::ZeroVector, FText::GetEmpty(), BigFont, HUDDark);
	TextItem.EnableShadow(FLinearColor::Black);

	//PRIMARY WEAPON
	{
		const float PriWeapOffsetY = 65;
		const float PriWeaponBoxWidth = 150;

		Canvas->SetDrawColor(FColor::White);
		const float PriWeapBgPosY = Canvas->ClipY - Canvas->OrgY - (PriWeapOffsetY + PrimaryWeapBg.VL + Offset) * ScaleUI;

		//Weapon draw position
		const float PriWeapPosX = Canvas->ClipX - Canvas->OrgX - ((PriWeaponBoxWidth + MyWeapon->PrimaryIcon.UL) / 2.0f + 2 * Offset) * ScaleUI;
		const float PriWeapPosY = Canvas->ClipY - Canvas->OrgY - (PriWeapOffsetY + (PrimaryWeapBg.VL + MyWeapon->PrimaryIcon.VL) / 2 + Offset) * ScaleUI;

		//Clip draw position
		const float ClipWidth = MyWeapon->PrimaryClipIcon.UL + MyWeapon->PrimaryClipIconOffset * (MyWeapon->AmmoIconsCount - 1);
		const float BoxWidth = 65.0f;
		const float PriClipPosX = PriWeapPosX - (BoxWidth + ClipWidth) * ScaleUI;
		const float PriClipPosY = Canvas->ClipY - Canvas->OrgY - (PriWeapOffsetY + (PrimaryWeapBg.VL + MyWeapon->PrimaryClipIcon.VL) / 2 + Offset) * ScaleUI;

		const float LeftCornerWidth = 60;

		FCanvasTileItem TileItem(FVector2D(PriClipPosX - Offset * ScaleUI, PriWeapBgPosY), PrimaryWeapBg.Texture->Resource,
			FVector2D(LeftCornerWidth * ScaleUI, PrimaryWeapBg.VL * ScaleUI), FLinearColor::White);
		MakeUV(PrimaryWeapBg, TileItem.UV0, TileItem.UV1, PrimaryWeapBg.U, PrimaryWeapBg.V, LeftCornerWidth, PrimaryWeapBg.VL);
		TileItem.BlendMode = SE_BLEND_Translucent;
		Canvas->DrawItem(TileItem);

		const float RestWidth = Canvas->ClipX - PriClipPosX - LeftCornerWidth * ScaleUI;
		TileItem.Position = FVector2D(PriClipPosX - (Offset - LeftCornerWidth) * ScaleUI, PriWeapBgPosY);
		TileItem.Size = FVector2D(RestWidth, PrimaryWeapBg.VL * ScaleUI);
		MakeUV(PrimaryWeapBg, TileItem.UV0, TileItem.UV1, PrimaryWeapBg.U + PrimaryWeapBg.UL - RestWidth / ScaleUI, PrimaryWeapBg.V, RestWidth / ScaleUI, PrimaryWeapBg.VL);
		Canvas->DrawItem(TileItem);

		//Drawing primary weapon icon, ammo in the clip and total spare ammo numbers
		Canvas->DrawIcon(MyWeapon->PrimaryIcon, PriWeapPosX, PriWeapPosY, ScaleUI);

		const float TextOffset = 12;
		float SizeX, SizeY;
		float TopTextHeight;
		FString Text = FString::FromInt(MyWeapon->GetCurrentAmmoInClip());

		Canvas->StrLen(BigFont, Text, SizeX, SizeY);

		const float TopTextScale = 0.73f; // of 51pt font
		const float TopTextPosX = Canvas->ClipX - Canvas->OrgX - (PriWeaponBoxWidth + Offset * 2 + (BoxWidth + SizeX * TopTextScale) / 2.0f)  * ScaleUI;
		const float TopTextPosY = Canvas->ClipY - Canvas->OrgY - (PriWeapOffsetY + PrimaryWeapBg.VL + Offset - TextOffset / 2.0f) * ScaleUI;
		TextItem.Text = FText::FromString(Text);
		TextItem.Scale = FVector2D(TopTextScale * ScaleUI, TopTextScale * ScaleUI);
		TextItem.FontRenderInfo = ShadowedFont;
		Canvas->DrawItem(TextItem, TopTextPosX, TopTextPosY);
		TopTextHeight = SizeY * TopTextScale;
		Text = FString::FromInt(MyWeapon->GetCurrentAmmo() - MyWeapon->GetCurrentAmmoInClip());
		Canvas->StrLen(BigFont, Text, SizeX, SizeY);

		const float BottomTextScale = 0.49f; // of 51pt font
		const float BottomTextPosX = Canvas->ClipX - Canvas->OrgX - (PriWeaponBoxWidth + Offset * 2 + (BoxWidth + SizeX * BottomTextScale) / 2.0f) * ScaleUI;
		const float BottomTextPosY = TopTextPosY + (TopTextHeight - 0.8f * TextOffset) * ScaleUI;
		TextItem.Text = FText::FromString(Text);
		TextItem.Scale = FVector2D(BottomTextScale*ScaleUI, BottomTextScale * ScaleUI);
		TextItem.FontRenderInfo = ShadowedFont;
		Canvas->DrawItem(TextItem, BottomTextPosX, BottomTextPosY);

		// Drawing clip icons
		Canvas->SetDrawColor(FColor::White);

		const float AmmoPerIcon = MyWeapon->GetAmmoPerClip() / MyWeapon->AmmoIconsCount;
		for (int32 i = 0; i < MyWeapon->AmmoIconsCount; i++)
		{
			if ((i + 1) * AmmoPerIcon > MyWeapon->GetCurrentAmmoInClip())
			{
				const float UsedPerIcon = (i + 1) * AmmoPerIcon - MyWeapon->GetCurrentAmmoInClip();
				float PercentLeftInIcon = 0;
				if (UsedPerIcon < AmmoPerIcon)
				{
					PercentLeftInIcon = (AmmoPerIcon - UsedPerIcon) / AmmoPerIcon;
				}
				const int32 Color = 128 + 128 * PercentLeftInIcon;
				Canvas->SetDrawColor(Color, Color, Color, Color);
			}

			const float ClipOffset = MyWeapon->PrimaryClipIconOffset * ScaleUI * i;
			Canvas->DrawIcon(MyWeapon->PrimaryClipIcon, PriClipPosX + ClipOffset, PriClipPosY, ScaleUI);
		}
		Canvas->SetDrawColor(HUDDark);
	}
	*/
}
void ASpaceHUD::DrawCrosshair()
{
	
		const float SpreadMulti = 300;
		/*
		//AShooterWeapon_Instant* InstantWeapon = Cast<AShooterWeapon_Instant>(Pawn->GetWeapon());
		//AShooterWeapon* MyWeapon = Pawn->GetWeapon();
		const float CurrentTime = GetWorld()->GetTimeSeconds();
		
		float AnimOffset = 0;
		if (MyWeapon)
		{
			const float EquipStartedTime = MyWeapon->GetEquipStartedTime();
			const float EquipDuration = MyWeapon->GetEquipDuration();
			AnimOffset = 300 * (1.0f - FMath::Min(1.0f, (CurrentTime - EquipStartedTime) / EquipDuration));
		}
		
		float CrossSpread = 2 + AnimOffset;
		if (InstantWeapon != NULL)
		{
			CrossSpread += SpreadMulti*FMath::Tan(FMath::DegreesToRadians(InstantWeapon->GetCurrentSpread()));
		}
		*/
		
		
		float CenterX = Canvas->ClipX / 2;
		float CenterY = Canvas->ClipY / 2;
		Canvas->SetDrawColor(255, 255, 255, 192);

		FCanvasIcon* CurrentCrosshair[5];
		for (int32 i = 0; i< 5; i++)
		{
			/*
			if (MyWeapon && MyWeapon->UseCustomAimingCrosshair && Pawn->IsTargeting())
			{
				CurrentCrosshair[i] = &MyWeapon->AimingCrosshair[i];
			}
			else if (MyWeapon && MyWeapon->UseCustomCrosshair)
			{
				CurrentCrosshair[i] = &MyWeapon->Crosshair[i];
			}
			else
			{
				CurrentCrosshair[i] = &Crosshair[i];
			}
			*/
			CurrentCrosshair[i] = &Crosshair[i];
		}
		/*
		if (Pawn->IsTargeting() && MyWeapon->UseLaserDot)
		{
			Canvas->SetDrawColor(255, 0, 0, 192);
			Canvas->DrawIcon(
				*CurrentCrosshair[4],
				CenterX - (*CurrentCrosshair[4]).UL*ScaleUI / 2.0f,
				CenterY - (*CurrentCrosshair[4]).VL*ScaleUI / 2.0f, 
				ScaleUI
			);
		}
		else
		{
			Canvas->DrawIcon(*CurrentCrosshair[4],
				CenterX - (*CurrentCrosshair[4]).UL*ScaleUI / 2.0f,
				CenterY - (*CurrentCrosshair[4]).VL*ScaleUI / 2.0f, ScaleUI);

			Canvas->DrawIcon(*CurrentCrosshair[0],
				CenterX - 1 - (*CurrentCrosshair[0]).UL * ScaleUI - CrossSpread * ScaleUI,
				CenterY - (*CurrentCrosshair[0]).VL*ScaleUI / 2.0f, ScaleUI);
			
			Canvas->DrawIcon(*CurrentCrosshair[1],
				CenterX + CrossSpread * ScaleUI,
				CenterY - (*CurrentCrosshair[1]).VL * ScaleUI / 2.0f, ScaleUI);

			Canvas->DrawIcon(*CurrentCrosshair[2],
				CenterX - (*CurrentCrosshair[2]).UL * ScaleUI / 2.0f,
				CenterY - 1 - (*CurrentCrosshair[2]).VL * ScaleUI - CrossSpread * ScaleUI, ScaleUI);
			
			Canvas->DrawIcon(*CurrentCrosshair[3],
				CenterX - (*CurrentCrosshair[3]).UL * ScaleUI / 2.0f,
				CenterY + CrossSpread * ScaleUI, ScaleUI);
		*/
		/*
				
		}

		if (CurrentTime - LastEnemyHitTime >= 0 && CurrentTime - LastEnemyHitTime <= LastEnemyHitDisplayTime)
		{
			const float Alpha = FMath::Min(1.0f, 1 - (CurrentTime - LastEnemyHitTime) / LastEnemyHitDisplayTime);
			Canvas->SetDrawColor(255, 255, 255, 255 * Alpha);

			Canvas->DrawIcon(HitNotifyCrosshair,
				CenterX - HitNotifyCrosshair.UL*ScaleUI / 2.0f,
				CenterY - HitNotifyCrosshair.VL*ScaleUI / 2.0f, ScaleUI);
		}
		*/
	Canvas->DrawIcon(*CurrentCrosshair[4],
		CenterX - (*CurrentCrosshair[4]).UL*ScaleUI / 2.0f,
		CenterY - (*CurrentCrosshair[4]).VL*ScaleUI / 2.0f, ScaleUI);
	Canvas->DrawIcon(*CurrentCrosshair[0],
		CenterX - 1 - (*CurrentCrosshair[0]).UL * ScaleUI - 1 * ScaleUI,
		CenterY - (*CurrentCrosshair[0]).VL*ScaleUI / 2.0f, ScaleUI);

	Canvas->DrawIcon(*CurrentCrosshair[1],
		CenterX + 1 * ScaleUI,
		CenterY - (*CurrentCrosshair[1]).VL * ScaleUI / 2.0f, ScaleUI);

	Canvas->DrawIcon(*CurrentCrosshair[2],
		CenterX - (*CurrentCrosshair[2]).UL * ScaleUI / 2.0f,
		CenterY - 1 - (*CurrentCrosshair[2]).VL * ScaleUI - 1 * ScaleUI, ScaleUI);

	Canvas->DrawIcon(*CurrentCrosshair[3],
		CenterX - (*CurrentCrosshair[3]).UL * ScaleUI / 2.0f,
		CenterY + 1 * ScaleUI, ScaleUI);
	/*
	*/



}
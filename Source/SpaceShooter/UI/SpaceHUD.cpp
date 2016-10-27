// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
 
#include "SpaceShooter.h"
#include "SpaceHUD.h"
#include "UI/IngameHUD.h"
 #include "Engine.h"
#include "Characters/PlayerCharacterController.h"
#include "Characters/Trainer.h"
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
	/*
	*/

}






void ASpaceHUD::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	//SAssignNew(GameHUD, SIngameHUD).PC((PlayerCharacterController*) GetOwningPlayerController());
	SAssignNew(GameHUD, SIngameHUD)
		.PC((APlayerCharacterController*)GetOwningPlayerController())
		.PT(Cast<ATrainer>(GetOwningPawn()));

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

	}

		

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
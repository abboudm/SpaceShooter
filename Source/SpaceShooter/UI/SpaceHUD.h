
#pragma once
 
#include "GameFramework/HUD.h"
#include "SpaceHUD.generated.h"


UCLASS()
class SPACESHOOTER_API ASpaceHUD : public AHUD
{
	GENERATED_BODY()
        // Initializes the Slate UI and adds it as widget content to the game viewport.
	
	ASpaceHUD(const FObjectInitializer& PCIP);

	virtual void PostInitializeComponents() override;
 
        // Reference to the Main Menu Slate UI.
	TSharedPtr<class SIngameHUD> GameHUD;


protected:
	// Floor for automatic hud scaling.
	static const float MinHudScale;
	// UI scaling factor for other resolutions than Full HD. //
	float ScaleUI;
	// Crosshair icons (left, top, right, bottom and center).//
	UPROPERTY()
		FCanvasIcon Crosshair[5];
	UPROPERTY()
		UTexture2D* HUDMainTexture;
public:

	/** Main HUD update loop. */
	virtual void DrawHUD() override;
	void DrawCrosshair();


 	//UFUNCTION(BlueprintImplementableEvent, Category = "Menus|Main Menu")
	//void PlayGameClicked();

};
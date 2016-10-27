
#pragma once

#include "SlateWidgetStyleContainerBase.h" 
//#include "SlateBasics.h"
#include "GlobalMenuStyle.generated.h" 


USTRUCT()
struct FGlobalStyle : public FSlateWidgetStyle
{
	GENERATED_USTRUCT_BODY()

	virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;

	static const FName TypeName;

	virtual const FName GetTypeName() const override;

	static const FGlobalStyle& GetDefault(); // static const FStrategyMenuStyle& GetDefault();

	UPROPERTY(EditAnywhere, Category = Appearance)
	FButtonStyle MenuButtonStyle;
	UPROPERTY(EditAnywhere, Category = Appearance)
		FButtonStyle TabButtonStyle;
	
	//UPROPERTY(EditAnywhere, Category = Appearance)
	//FTextBlockStyle MenuButtonTextStyle;

	//UPROPERTY(EditAnywhere, Category = Appearance)
	//FTextBlockStyle MenuTitleStyle;
	
	UPROPERTY(EditAnywhere, Category = Appearance)
		FTextBlockStyle HeaderTextStyle;
	UPROPERTY(EditAnywhere, Category = Appearance)
		FTextBlockStyle TitleTextStyle;
	UPROPERTY(EditAnywhere, Category = Appearance)
		FTextBlockStyle ItemTextStyle;


	UPROPERTY(EditAnywhere, Category = Appearance)
		FTextBlockStyle HUDTextStyle;

};

UCLASS(hidecategories = Object, MinimalAPI)
class UGlobalMenuStyle : public USlateWidgetStyleContainerBase
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(EditAnywhere, Category = Appearance, meta = (ShowOnlyInnerProperties))
	FGlobalStyle MenuStyle;

	virtual const struct FSlateWidgetStyle* const GetStyle() const override
	{
		return static_cast<const struct FSlateWidgetStyle*>(&MenuStyle);
	}

};

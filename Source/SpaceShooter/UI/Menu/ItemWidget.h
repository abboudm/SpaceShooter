
#pragma once

#include "SlateBasics.h"
#include "Items/Item.h"



// Lays out and controls the Main Menu UI for our tutorial.
class SPACESHOOTER_API SItemWidget : public SCompoundWidget
{

public:
	SLATE_BEGIN_ARGS(SItemWidget)
	{}
	SLATE_ARGUMENT(FItem, Item)
	SLATE_END_ARGS()

	
	void Construct(const FArguments& args);
	const struct FGlobalStyle* MenuStyle;
	
	FItem Item;

	TAttribute<FText> Name;
	TAttribute<FText> Value;
	TAttribute<FText> Weight;

	FText GetName() const;
	FText GetValue() const;
	FText GetWeight() const;

	DECLARE_DELEGATE_OneParam(FUseItem, FItem);
	FUseItem UseItem;
	/*
	DECLARE_DELEGATE(FOnUseItem);
	FOnUseItem UseItem;
	*/

	FReply ItemClicked();


};
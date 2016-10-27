
#include "SpaceShooter.h"
#include "ItemWidget.h"
#include "UI/Styles/GlobalMenuStyle.h"
#include "UI/Styles/MenuStyles.h"
#include "Engine.h"
#include "Items/Item.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SItemWidget::Construct(const FArguments& args)
{
	Item = args._Item;
	MenuStyle = &FMenuStyles::Get().GetWidgetStyle<FGlobalStyle>("Global");
	Name.Bind(this, &SItemWidget::GetName);
	Value.Bind(this, &SItemWidget::GetValue);
	Weight.Bind(this, &SItemWidget::GetWeight);

	ChildSlot
		.Padding(0.0,0.0,0.0,0.0)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
	[
		SNew(SOverlay)
		+ SOverlay::Slot()
		.VAlign(VAlign_Fill)
		.HAlign(HAlign_Fill)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Fill)
			.AutoWidth()
			[
				SNew(STextBlock)
					.TextStyle(&MenuStyle->HUDTextStyle)
					.Text(Name)
					.MinDesiredWidth(550)
			]

			+ SHorizontalBox::Slot()
			.Padding(0, 0, 0, 0)
			.HAlign(HAlign_Right)
			.VAlign(VAlign_Fill)
			[
				SNew(STextBlock)
					.TextStyle(&MenuStyle->HUDTextStyle)
					.Text(Value)
					.MinDesiredWidth(30)
			]
			+ SHorizontalBox::Slot()
			.HAlign(HAlign_Right)
			.VAlign(VAlign_Fill)
			[
				SNew(STextBlock)
					.TextStyle(&MenuStyle->HUDTextStyle)
					.Text(Weight)
					.MinDesiredWidth(30)
			]
		
		]

		+ SOverlay::Slot()
			.VAlign(VAlign_Fill)
			.HAlign(HAlign_Fill)
			[
				SNew(SButton)
				.ButtonStyle(&MenuStyle->MenuButtonStyle)
				//.TextStyle(&MenuStyle->MenuButtonTextStyle)
				//.Text(FText::FromString("Play Game!"))
				.OnClicked(this, &SItemWidget::ItemClicked)
			]


		
	];


	/*
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
				.Text(Name)
			]
			+ SVerticalBox::Slot()
			[
				SNew(STextBlock)
				.TextStyle(&MenuStyle->HUDTextStyle)
				.Text(Value)
			]
			+ SVerticalBox::Slot()
			[
				SNew(STextBlock)
				.TextStyle(&MenuStyle->HUDTextStyle)
				.Text(Weight)
			]
		]
	];
	*/
	




}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION




FText SItemWidget::GetName() const
{

	FString out = Item.Name.ToString();

	if (Item.Quantity > 1)
	{
		out.Append("(");
		out.Append(FString::FromInt(Item.Quantity));
		out.Append(")");
	}
	//out.Append("||");
	return FText::FromString(out);
}

FText SItemWidget::GetValue() const
{
	FString out = FString::FromInt(Item.Value);
	//out.Append("||");
	return FText::FromString(out);
}

FText SItemWidget::GetWeight() const
{
	FString out = FString::FromInt(Item.Weight);
	//out.Append("||");
	return FText::FromString(out);
}

FReply SItemWidget::ItemClicked()
{
	UseItem.ExecuteIfBound(Item);
	//UseItem.ExecuteIfBound();
	//OnToggleMenu.ExecuteIfBound();
	return FReply::Handled();
}

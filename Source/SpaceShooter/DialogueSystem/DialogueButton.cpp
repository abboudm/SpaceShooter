//Copyright (c) 2016 Artem A. Mavrin and other contributors
#include "SpaceShooter.h"
#include "DialogueSystem/DialogueSystemPrivatePCH.h"
#include "Widget.h"
#include "TextBlock.h"
#include "DialogueButton.h"

//#define LOCTEXT_NAMESPACE "DialogueSystem"

UDialogueButton::UDialogueButton()
{
	OnClicked.AddDynamic(this, &UDialogueButton::OnClick);
}

void UDialogueButton::OnClick()
{
	UWidget* WText = GetChildAt(0);
	UTextBlock* TextBlock = Cast<UTextBlock>(WText);
	if (TextBlock && WaitTask != nullptr)
	{
		FText SelectedQuestion = TextBlock->GetText();
		WaitTask->SetAnswer(SelectedQuestion);
	}
}

#if WITH_EDITOR
const FText UDialogueButton::GetPaletteCategory()
{
	return NSLOCTEXT("DialogueSystem", "Dialogue", "Dialogue");
}
#endif

/////////////////////////////////////////////////////

//#undef LOCTEXT_NAMESPACE

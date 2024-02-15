#include "Components/CDialogueComponent.h"
#include "Global.h"
#include "Widgets/CUserWidget_Dialogue.h"

UCDialogueComponent::UCDialogueComponent()
{

}

void UCDialogueComponent::ShowDialogue(FString name, FString Text)
{
	
	if (!!!DialogueWidget)
	{
		DialogueWidget = Cast<UCUserWidget_Dialogue>(CreateWidget(GetWorld(), DialogueWidgetClass));
		CheckNull(DialogueWidget);
		DialogueWidget->Update(name, Text);
		DialogueWidget->AddToViewport();
	}
	else
	{
		DialogueWidget->Update(name, Text);
		DialogueWidget->AddToViewport();
	}	
}

void UCDialogueComponent::QuitDialogue()
{
	CheckNull(DialogueWidget);
	DialogueWidget->RemoveFromParent();
	OnDialogue = false;
	Index = 0;
}

FString UCDialogueComponent::GetText()
{
	if (Index >= Speak.Num())
	{
		//QuitDialogue();
		Index = 0;
		return "";
	}
	else
	{
		Index++;
		return Speak[Index-1];
	}
}

void UCDialogueComponent::SpeakTo(AActor* InOther)
{
	UCDialogueComponent* dialogue = CHelpers::GetComponent<UCDialogueComponent>(InOther);
	CheckNull(dialogue);
	FString Text = this->GetText();
	if (Text == "")
	{
		dialogue->QuitDialogue();
	}
	else
	{
		dialogue->ShowDialogue(Name.ToString(), Text);
	}
}


void UCDialogueComponent::BeginPlay()
{
	Super::BeginPlay();


}





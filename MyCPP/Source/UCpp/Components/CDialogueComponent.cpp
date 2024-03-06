#include "Components/CDialogueComponent.h"
#include "Global.h"
#include "Widgets/CUserWidget_Dialogue.h"
#include "Components/WidgetComponent.h"
#include "Widgets/CUserWidget_Shout.h"

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
		DialogueWidget->SetVisibility(ESlateVisibility::Visible);

		//DialogueWidget->AddToViewport();
	}	
}

void UCDialogueComponent::QuitDialogue()
{
	CheckNull(DialogueWidget);
	DialogueWidget->SetVisibility(ESlateVisibility::Hidden);
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

void UCDialogueComponent::Shout()
{
	UWidgetComponent* ShoutWidget = CHelpers::GetComponent<UWidgetComponent>(GetOwner());
	ShoutWidget->InitWidget();
	CheckNull(ShoutWidget);
	
	//for (FString text: Dialogue->GetShout())
	{
		//ShoutWidget->Update(text);
		//Cast<UCUserWidget_Shout>(ShoutWidget->GetUserWidgetObject())->Update(text);

	}
	//(Cast<UCUserWidget_Shout>(Shout))->Update();

}

void UCDialogueComponent::SpeakTo(AActor* InOther)
{
	UCDialogueComponent* dialogue = CHelpers::GetComponent<UCDialogueComponent>(InOther);
	UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(GetOwner());

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





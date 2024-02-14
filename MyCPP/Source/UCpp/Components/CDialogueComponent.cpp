#include "Components/CDialogueComponent.h"
#include "Global.h"
#include "Widgets/CUserWidget_Dialogue.h"



UCDialogueComponent::UCDialogueComponent()
{

}

void UCDialogueComponent::ShowDialogue()
{
	if (!!!DialogueWidget)
	{
		DialogueWidget = Cast<UCUserWidget_Dialogue>(CreateWidget(GetWorld(), DialogueWidgetClass));
		CheckNull(DialogueWidget);
		DialogueWidget->Update(GetOwner()->GetName(), "Hello");
		DialogueWidget->AddToViewport();

	}
}


void UCDialogueComponent::BeginPlay()
{
	Super::BeginPlay();

	
}





#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "CDialogueComponent.generated.h"


UCLASS( ClassGroup=(GameProject), meta=(BlueprintSpawnableComponent) )
class UCPP_API UCDialogueComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "Widget")
		TSubclassOf<UUserWidget> DialogueWidgetClass;

	UPROPERTY()
		class UCUserWidget_Dialogue* DialogueWidget;
	
public:	
	UCDialogueComponent();

	void ShowDialogue();

protected:
	virtual void BeginPlay() override;


};

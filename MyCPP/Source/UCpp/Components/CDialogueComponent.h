#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "Components/CStateComponent.h"
#include "CDialogueComponent.generated.h"

USTRUCT(BlueprintType)
struct FDialogueData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		EStateType Type;

	UPROPERTY(EditAnywhere)
		FString String;

	UPROPERTY(EditAnywhere)
		int Index;
};


UCLASS( ClassGroup=(GameProject), meta=(BlueprintSpawnableComponent) )
class UCPP_API UCDialogueComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "Widget")
		TSubclassOf<UUserWidget> DialogueWidgetClass;

	UPROPERTY()
		class UCUserWidget_Dialogue* DialogueWidget;

	UPROPERTY(EditAnywhere)
		TArray<FString> Speak;

	UPROPERTY(EditAnywhere)
		FName Name;

private:
	UPROPERTY(EditDefaultsOnly, Category = "DataTable")
		UDataTable* DataTable;

public:	
	UCDialogueComponent();

	void ShowDialogue(FString name, FString Text);

	void QuitDialogue();

	FString GetText();

	void SpeakTo(AActor* InOther);
protected:
	virtual void BeginPlay() override;

private:
	bool OnDialogue;
	int Index;
};

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "Components/CStateComponent.h"
#include "Components/CBehaviorComponent.h"
#include "CDialogueComponent.generated.h"

USTRUCT(BlueprintType)
struct FBehaviorShoutData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		EBehaviorType Type;

	UPROPERTY(EditAnywhere)
		FString String;

	UPROPERTY(EditAnywhere)
		int Index;
};

USTRUCT(BlueprintType)
struct FActionShoutData : public FTableRowBase
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


USTRUCT(BlueprintType)
struct FSpeakData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		int ID;

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
		FString Say;

	UPROPERTY(EditAnywhere)
		TMap<EStateType, FString> ActionSpeak;

	UPROPERTY(EditAnywhere)
		TMap<EBehaviorType, FString> BehaviorSpeak;


	UPROPERTY(EditAnywhere)
		FName Name;

	UPROPERTY(EditAnywhere)
		int SpeakID;

private:
	UPROPERTY(EditDefaultsOnly, Category = "DataTable")
		UDataTable* ActionSpeakTable;
	
	UPROPERTY(EditDefaultsOnly, Category = "DataTable")
		UDataTable* BehaviorSpeakTable;

	UPROPERTY(EditDefaultsOnly, Category = "DataTable")
		UDataTable* SpeakTable;

public:	
	UCDialogueComponent();

	void ShowDialogue(FString name, FString Text);

	void QuitDialogue();

	FString GetText();

	TMap<EStateType, FString> GetShout() { return ActionSpeak; }

	TMap<EBehaviorType, FString> GetBehaviorShout() { return BehaviorSpeak; }

	FString GetSay() { return Say; }

	void SpeakTo(AActor* InOther);

	
protected:
	virtual void BeginPlay() override;

private:
	bool OnDialogue;
	int Index;
};

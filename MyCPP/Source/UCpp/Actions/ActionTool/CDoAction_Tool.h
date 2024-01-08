// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/CDoAction.h"
#include "CDoAction_Tool.generated.h"

/**
 * 
 */
UCLASS()
class UCPP_API ACDoAction_Tool : public ACDoAction
{
	GENERATED_BODY()
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	virtual void DoAction()       override;
	virtual void Begin_DoAction() override;
	virtual void End_DoAction()   override;

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TSubclassOf<class ACAttachment> AttachmentClass;
private:
	class ACAttachment* Attachment;
private:
	FString GetLabelName(class ACharacter* InOwnerCharacter, FString InName);

};

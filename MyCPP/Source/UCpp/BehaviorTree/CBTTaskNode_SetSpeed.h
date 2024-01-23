// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Components/CStatusComponent.h"
#include "CBTTaskNode_SetSpeed.generated.h"


UCLASS()
class UCPP_API UCBTTaskNode_SetSpeed : public UBTTaskNode
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere)
		ECharacterSpeed SpeedType;

public:
	UCBTTaskNode_SetSpeed();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};

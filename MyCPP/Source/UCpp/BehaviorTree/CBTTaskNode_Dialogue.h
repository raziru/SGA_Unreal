// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CBTTaskNode_Dialogue.generated.h"

/**
 * 
 */
UCLASS()
class UCPP_API UCBTTaskNode_Dialogue : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UCBTTaskNode_Dialogue();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};

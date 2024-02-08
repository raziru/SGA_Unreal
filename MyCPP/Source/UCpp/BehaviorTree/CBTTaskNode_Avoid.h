// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CBTTaskNode_Avoid.generated.h"

/**
 * 
 */
UCLASS()
class UCPP_API UCBTTaskNode_Avoid : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UCBTTaskNode_Avoid();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};

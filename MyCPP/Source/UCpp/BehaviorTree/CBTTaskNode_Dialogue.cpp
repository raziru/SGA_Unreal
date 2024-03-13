// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTree/CBTTaskNode_Dialogue.h"
#include "Global.h"
#include "Characters/CAIController.h"
#include "Characters/CEnemy_AI.h"
#include "Components/CDialogueComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CBehaviorComponent.h"



UCBTTaskNode_Dialogue::UCBTTaskNode_Dialogue()
{
	NodeName = "Dialogue";

}

EBTNodeResult::Type UCBTTaskNode_Dialogue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());

	ACEnemy_AI* ai = Cast<ACEnemy_AI>(controller->GetPawn());

	UCBehaviorComponent* behavior = CHelpers::GetComponent<UCBehaviorComponent>(controller);

	UCDialogueComponent* dialogue = CHelpers::GetComponent<UCDialogueComponent>(ai);

	if (behavior->IsApproachMode())
	{
		if (dialogue->GetBehaviorShout().Find(EBehaviorType::Approach))
		{
			ai->Say(dialogue->GetBehaviorShout()[EBehaviorType::Approach]);
		}
	}
	else if (behavior->IsPatrolMode())
	{
		if (dialogue->GetBehaviorShout().Find(EBehaviorType::Patrol))
		{
			ai->Say(dialogue->GetBehaviorShout()[EBehaviorType::Patrol]);
		}
	}


	return EBTNodeResult::Succeeded;

}

// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTree/CBTTaskNode_Avoid.h"
#include "Global.h"
#include "Characters/CAIController.h"
#include "Characters/CEnemy_AI.h"
#include "Components/CStateComponent.h"


UCBTTaskNode_Avoid::UCBTTaskNode_Avoid()
{
	NodeName = "Avoid";

}

EBTNodeResult::Type UCBTTaskNode_Avoid::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());

	ACEnemy_AI* ai = Cast<ACEnemy_AI>(controller->GetPawn());
	UCStateComponent* State = CHelpers::GetComponent<UCStateComponent>(ai);

	State->SetBackstepMode();

	return EBTNodeResult::Succeeded;

}

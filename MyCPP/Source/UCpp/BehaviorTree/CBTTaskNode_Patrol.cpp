// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTree/CBTTaskNode_Patrol.h"
#include "Global.h"
#include "Characters/CAIController.h"
#include "Characters/CEnemy_AI.h"
#include "Components/CPatrolComponent.h"


UCBTTaskNode_Patrol::UCBTTaskNode_Patrol()
{
	NodeName = "Patrol";

}

EBTNodeResult::Type UCBTTaskNode_Patrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	
	ACEnemy_AI* ai = Cast<ACEnemy_AI>(controller->GetPawn());
	UCPatrolComponent* patrol = CHelpers::GetComponent<UCPatrolComponent>(ai);

	FVector Location;
	float AcceptanceRadius;
	//EPathFollowingRequestResult::Type result;
	if (patrol->GetMoveTo(Location,AcceptanceRadius))
	{
		if (controller->MoveToLocation(Location, AcceptanceRadius)==EPathFollowingRequestResult::RequestSuccessful|| controller->MoveToLocation(Location, AcceptanceRadius) == EPathFollowingRequestResult::Failed)
		{
			//patrol->UpdateNextIndex();
			//controller->OnMoveCompleted(,result)
		}
		//controller->MoveToLocation(Location, AcceptanceRadius) == EPathFollowingRequestResult::RequestSuccessful || controller->MoveToLocation(Location, AcceptanceRadius) == EPathFollowingRequestResult::Failed
		return EBTNodeResult::Succeeded;

	}
	else
	{
		return EBTNodeResult::Failed;

	}

}



// Fill out your copyright notice in the Description page of Project Settings.


#include "CBTService_Melee.h"
#include "Global.h"
#include "Characters/CPlayer.h"
#include "Characters/CAIController.h"
#include "Characters/CEnemy_AI.h"
#include "Components/CBehaviorComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CPatrolComponent.h"




UCBTService_Melee::UCBTService_Melee()
{
    NodeName = "Melee";
}

void UCBTService_Melee::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
    UCBehaviorComponent* behavior = CHelpers::GetComponent<UCBehaviorComponent>(controller);

    ACEnemy_AI* ai = Cast<ACEnemy_AI>(controller->GetPawn());
    UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(ai);
    

    UCPatrolComponent* patrol = CHelpers::GetComponent<UCPatrolComponent>(ai);

    if (state->IsCorpseMode())
    {
        behavior->SetWaitMode();
        return;
    }

    if (CanAvoid)
    {
        CanAvoid = false;
        AvoidCount = 0;
        AvoidTime = 0.0f;
        behavior->SetAvoidMode();
        return;
    }

    if (state->IsHittedMode())
    {
        behavior->SetHittedMode();
        AvoidCount++;
        if (AvoidCount>=(FMath::RandRange(4, 7)))
        {
            CanAvoid = true;

        }
        return;
    }

    ACPlayer* target = behavior->GetTargetPlayer();
    if (target == NULL)
    {
        //TODO: 패트롤 모드
        behavior->SetPatrolMode();
        return;
    }
    else
    {
        UCStateComponent* targetState = CHelpers::GetComponent<UCStateComponent>(target);
        if (targetState->IsDeadMode())
        {
            behavior->SetWaitMode();

            return;
        }
    }

    float distance = ai->GetDistanceTo(target);
    if (distance < controller->GetMeleeActionRange())
    {
        behavior->SetActionMode();
        AvoidTime += DeltaSeconds;
        if (AvoidTime>= FMath::RandRange(3.0f, 4.0f))
        {
            CLog::Print(AvoidTime);
            CanAvoid = true;
        }
        return;
    }

    if (distance < controller->GetSightRadius())
    {
        behavior->SetApproachMode();

        return;
    }

}

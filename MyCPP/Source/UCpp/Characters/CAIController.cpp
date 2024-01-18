

#include "Characters/CAIController.h"
#include "Global.h"
#include "CEnemy_AI.h"
#include "CPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
//#include "Components/CBehaviorComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

ACAIController::ACAIController()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateActorComponent<UBlackboardComponent>(this, &Blackboard, "Blackboard");
}



void ACAIController::BeginPlay()
{
	Super::BeginPlay();

}

void ACAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


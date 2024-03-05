

#include "Characters/CEnemy_AI.h"
#include "Global.h"
#include "Components/CPickupComponent.h"
#include "Components/CPatrolComponent.h"



void ACEnemy_AI::End_Dead()
{
	Super::End_Dead();
	if (!!BehaviorTree)
	{
		BehaviorTree=NULL;
	}

}

void ACEnemy_AI::Interact(AActor* InOther)
{
	CLog::Print(InOther->GetName());
	//Dialogue->ShowDialogue();
	//CHelpers::GetComponent(&Dialogue);
	if (State->IsCorpseMode())
	{
		InteractType = EInteractType::Openable;

		Pickup->Pickup(InOther);
	}
	else
	{

	}
	/*else
	{
		InteractType = EInteractType::Speakable;

		Dialogue->SpeakTo(InOther);
	}*/
}

ACEnemy_AI::ACEnemy_AI()
{
	CHelpers::CreateActorComponent<UCPatrolComponent>(this, &Patrol, "Patrol");
}

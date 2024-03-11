

#include "Characters/CEnemy_AI.h"
#include "Global.h"
#include "Components/CPickupComponent.h"
#include "Components/CPatrolComponent.h"
#include "Components/CDialogueComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/CBehaviorComponent.h"

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
}





ACEnemy_AI::ACEnemy_AI()
{
	CHelpers::CreateActorComponent<UCPatrolComponent>(this, &Patrol, "Patrol");
	

}

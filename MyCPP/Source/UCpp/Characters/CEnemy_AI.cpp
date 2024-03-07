

#include "Characters/CEnemy_AI.h"
#include "Global.h"
#include "Components/CPickupComponent.h"
#include "Components/CPatrolComponent.h"
#include "Components/CDialogueComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/CBehaviorComponent.h"
#include "Widgets/CUserWidget_Shout.h"



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
}



void ACEnemy_AI::Shout()
{
	ShoutWidget->InitWidget();
	CheckNull(ShoutWidget);
	if (Dialogue->GetShout().Find(State->CurrentMode()))
	{
		Cast<UCUserWidget_Shout>(ShoutWidget->GetUserWidgetObject())->Update(Dialogue->GetShout()[State->CurrentMode()]);

	}
	
}



ACEnemy_AI::ACEnemy_AI()
{
	CHelpers::CreateActorComponent<UCPatrolComponent>(this, &Patrol, "Patrol");
	

}

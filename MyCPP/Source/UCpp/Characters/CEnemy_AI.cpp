

#include "Characters/CEnemy_AI.h"
#include "Global.h"
#include "Components/CPickupComponent.h"
#include "Components/CPatrolComponent.h"
#include "Components/WidgetComponent.h"
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

	for (FString text : Dialogue->GetShout())
	{
		//ShoutWidget->Update(text);
		Cast<UCUserWidget_Shout>(ShoutWidget->GetUserWidgetObject())->Update(text);

	}
}



ACEnemy_AI::ACEnemy_AI()
{
	CHelpers::CreateActorComponent<UCPatrolComponent>(this, &Patrol, "Patrol");
	CHelpers::CreateComponent<UWidgetComponent>(this, &ShoutWidget, "ShoutWidget", GetMesh());

	TSubclassOf<UCUserWidget_Shout> ShoutClass;
	CHelpers::GetClass<UCUserWidget_Shout>(&ShoutClass, "WidgetBlueprint'/Game/Widgets/WB_Shout.WB_Shout_C'");
	ShoutWidget->SetWidgetClass(ShoutClass);
	ShoutWidget->SetRelativeLocation(FVector(0, 190, 190));
	ShoutWidget->SetDrawSize(FVector2D(240, 30));
	ShoutWidget->SetWidgetSpace(EWidgetSpace::Screen);

}

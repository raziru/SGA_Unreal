

#include "Characters/CEnemy_AI.h"
#include "Global.h"
#include "Components/CPatrolComponent.h"

void ACEnemy_AI::PlayHitted()
{
	Montages->PlayHitted();

}

ACEnemy_AI::ACEnemy_AI()
{
	CHelpers::CreateActorComponent<UCPatrolComponent>(this, &Patrol, "Patrol");
}

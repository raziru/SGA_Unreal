
#pragma once

#include "CoreMinimal.h"
#include "Characters/CEnemy.h"
#include "CEnemy_AI.generated.h"

UCLASS()
class UCPP_API ACEnemy_AI : public ACEnemy
{
    GENERATED_BODY()

private:
    UPROPERTY(EditDefaultsOnly, Category = "AI")
        class UBehaviorTree* BehaviorTree;

    UPROPERTY(EditDefaultsOnly, Category = "AI")
        uint8 TeamID = 1;

private:
    UPROPERTY(VisibleDefaultsOnly)
        class UCPatrolComponent* Patrol;

    UPROPERTY(VisibleDefaultsOnly)
        class UWidgetComponent* ShoutWidget;
public:
    FORCEINLINE class UBehaviorTree* GetBehaviorTree() { return BehaviorTree; }
    FORCEINLINE uint8 GetTeamID() { return TeamID; }



    virtual void End_Dead()   override;

    virtual void Interact(AActor* InOther) override;

    void Shout();
 

protected:
    
public:
    ACEnemy_AI();

private:
    bool AI_Enable = true;
};

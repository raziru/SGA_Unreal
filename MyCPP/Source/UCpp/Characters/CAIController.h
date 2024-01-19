
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CAIController.generated.h"


UCLASS()
class UCPP_API ACAIController : public AAIController
{
	GENERATED_BODY()
private:
    UPROPERTY(EditAnywhere)
        float MeleeActionRange = 150;

    UPROPERTY(EditAnywhere)
        bool bDrawDebug = true;

    UPROPERTY(EditAnywhere)
        float AdjustCircleHeight = 50;

private:
    UPROPERTY(VisibleDefaultsOnly)
        class UAIPerceptionComponent* Perception;

    UPROPERTY(VisibleDefaultsOnly)
        class UCBehaviorComponent* Behavior;
public:
    FORCEINLINE float GetMeleeActionRange() { return MeleeActionRange; }
protected:
    virtual void BeginPlay() override;

    virtual void OnPossess(APawn* InPawn) override;
    virtual void OnUnPossess() override;

private:
    UFUNCTION()
        void OnPerceptionUpdated(const TArray<AActor*>& UpdateActors);

public:
    ACAIController();

    virtual void Tick(float DeltaTime) override;

    float GetSightRadius();


private:
    class ACEnemy_AI* OwnerEnemy;
    class UAISenseConfig_Sight* Sight;
};

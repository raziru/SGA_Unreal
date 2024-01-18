
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
public:
    FORCEINLINE float GetMeleeActionRange() { return MeleeActionRange; }
protected:
    virtual void BeginPlay() override;
public:
    ACAIController();

    virtual void Tick(float DeltaTime) override;

private:
    class ACEnemy_AI* OwnerEnemy;
    class UAISenseConfig_Sight* Sight;
};

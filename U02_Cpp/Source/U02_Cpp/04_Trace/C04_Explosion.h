
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C04_Explosion.generated.h"

UCLASS()
class U02_CPP_API AC04_Explosion : public AActor
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleDefaultsOnly)
		class UParticleSystemComponent* Particle;
public:	
	AC04_Explosion();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION()
		void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
};

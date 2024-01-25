
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CThrow.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FThrowBeginOverlap, FHitResult, InHitResult);

UCLASS()
class UCPP_API ACThrow : public AActor
{
	GENERATED_BODY()
	
public:
	void OnProjectile();
	void OffProjectile();
private:
	UPROPERTY(EditDefaultsOnly)
		class UParticleSystem* Explosion;

	UPROPERTY(EditDefaultsOnly)
		FTransform ExplosionTransform;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UProjectileMovementComponent* Projectile;

public:
	ACThrow();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		virtual void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	UPROPERTY(BlueprintAssignable)
		FThrowBeginOverlap OnThrowBeginOverlap;

private:
	bool CanCollision = true;
};

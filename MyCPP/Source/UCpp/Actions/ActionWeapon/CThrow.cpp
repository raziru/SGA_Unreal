// Fill out your copyright notice in the Description page of Project Settings.


#include "CThrow.h"
#include "Global.h"
#include "Components/ShapeComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

void ACThrow::OffProjectile()
{
	Projectile->Deactivate();
	InitialLifeSpan = 0.0f;
	CanCollision = false;
}

void ACThrow::OnProjectile()
{
	Projectile->Activate();
	InitialLifeSpan = 3.0f;

}

ACThrow::ACThrow()
{
	CHelpers::CreateActorComponent<UProjectileMovementComponent>(this, &Projectile, "Projectile");

	InitialLifeSpan = 3.0f;

	Projectile->InitialSpeed = 4000.0f;
	Projectile->MaxSpeed = 8000.0f;
	Projectile->ProjectileGravityScale = 0.0f;

}

void ACThrow::BeginPlay()
{
	Super::BeginPlay();

	TArray<UShapeComponent*> components;
	GetComponents<UShapeComponent>(components);

	for (UShapeComponent* shape : components)
		shape->OnComponentBeginOverlap.AddDynamic(this, &ACThrow::OnComponentBeginOverlap);
	

}

void ACThrow::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CLog::Print(OtherActor->GetName());
	if (CanCollision == false)
	{
		return;
	}
	if (GetOwner() == OtherActor || OtherActor->GetClass()==this->GetClass())
	{
		return;
	}

	if (!!Explosion)
	{
		FTransform transform = ExplosionTransform;
		transform.AddToTranslation(SweepResult.Location);
		transform.SetRotation(FQuat(SweepResult.ImpactNormal.Rotation()));

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Explosion, transform);
	}

	if (OnThrowBeginOverlap.IsBound())
		OnThrowBeginOverlap.Broadcast(SweepResult);

	Destroy();
}


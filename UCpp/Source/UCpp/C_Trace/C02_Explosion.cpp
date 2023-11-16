// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Trace/C02_Explosion.h"
#include "Global.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AC02_Explosion::AC02_Explosion()
{
	CHelpers::CreateComponent<UParticleSystemComponent>(this, &Particle, "Particle");

	UParticleSystem* particle;
	CHelpers::GetAsset<UParticleSystem>(&particle, "ParticleSystem'/Game/Effects/P_Explosion2.P_Explosion2'");
	Particle->SetTemplate(particle);
	Particle->bAutoActivate = false;

}

// Called when the game starts or when spawned
void AC02_Explosion::BeginPlay()
{
	Super::BeginPlay();
	
}

void AC02_Explosion::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	Particle->ResetParticles();
	Particle->SetActive(true);

	FVector start = GetActorLocation();
	FVector end = FVector(start.X, start.Y, start.Z + 10);

	TArray<TEnumAsByte<EObjectTypeQuery>> queries;//언리얼은 enum이 타입인지 모른다. byte라 지정해준 것
	//C++에서는 enum을 int로 기본을 잡아준다.
	queries.Add(EObjectTypeQuery::ObjectTypeQuery4);

	TArray<AActor*> ignoreActors;
	TArray<FHitResult> hitResults;
	if (UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(), start, end, 200, queries, false, ignoreActors, EDrawDebugTrace::ForOneFrame, hitResults, true))
	{
		for (const FHitResult& hitResult : hitResults)
		{
			UStaticMeshComponent* meshComponent = Cast<UStaticMeshComponent>(hitResult.GetActor()->GetRootComponent());
			if (!!meshComponent)
				meshComponent->AddRadialImpulse(GetActorLocation(), 1000, meshComponent->GetMass() * 700.0f, ERadialImpulseFalloff::RIF_Linear);
		}
	}
}


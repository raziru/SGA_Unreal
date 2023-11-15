// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Collision/C09_Particles.h"
#include "Global.h"
#include "C08_EventTrigger.h"
#include "Components/TextRenderComponent.h"
#include "Particles/ParticleSystem.h"
// Sets default values
AC09_Particles::AC09_Particles()
{
	CHelpers::CreateComponent<USceneComponent>(this, &Scene, "Scene");
	CHelpers::CreateComponent<UTextRenderComponent>(this, &Text, "Text", Scene);

	Text->SetRelativeLocation(FVector(0, 0, 100));
	Text->SetRelativeRotation(FRotator(0, 180, 0));
	Text->SetRelativeScale3D(FVector(2));
	Text->TextRenderColor = FColor::Red;
	Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	Text->Text = FText::FromString(GetName());

	CHelpers::GetAsset<UParticleSystem>(&Particles[0], "ParticleSystem'/Game/Effects/P_Genno_Weapon_Lightning_01.P_Genno_Weapon_Lightning_01'");
	CHelpers::GetAsset<UParticleSystem>(&Particles[1], "ParticleSystem'/Game/Effects/P_Cube_Mesh_Test.P_Cube_Mesh_Test'");
	CHelpers::GetAsset<UParticleSystem>(&Particles[2], "ParticleSystem'/Game/Effects/P_HeldCharge_Ice_00.P_HeldCharge_Ice_00'");

}

// Called when the game starts or when spawned
void AC09_Particles::BeginPlay()
{
	Super::BeginPlay();
	TArray<AC08_EventTrigger*> triggers;
	CHelpers::FindActors<AC08_EventTrigger>(GetWorld(), triggers);
	triggers[0]->OnEventTrigger.AddUFunction(this, "PlayParticle");
}
void AC09_Particles::PlayParticle(int32 InIndex)
{
	FTransform transform;
	transform.SetLocation(GetActorLocation());

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particles[InIndex], transform);
}


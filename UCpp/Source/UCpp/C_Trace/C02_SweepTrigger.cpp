// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Trace/C02_SweepTrigger.h"
#include "Global.h"
#include "C02_Explosion.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"

AC02_SweepTrigger::AC02_SweepTrigger()
{
	CHelpers::CreateComponent<USceneComponent>(this, &Scene, "Scene");
	CHelpers::CreateComponent<UBoxComponent>(this, &Box, "Box", Scene);
	CHelpers::CreateComponent<UTextRenderComponent>(this, &Text, "Text", Scene);


	Box->SetRelativeScale3D(FVector(3));
	Box->bHiddenInGame = false;

	Text->SetRelativeLocation(FVector(0, 0, 100));
	Text->SetRelativeRotation(FRotator(0, 180, 0));
	Text->SetRelativeScale3D(FVector(2));
	Text->TextRenderColor = FColor::Red;
	Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	Text->Text = FText::FromString(GetName());

}

// Called when the game starts or when spawned
void AC02_SweepTrigger::BeginPlay()
{
	Super::BeginPlay();
	TArray<AC02_Explosion*> explosions;
	CHelpers::FindActors(GetWorld(), explosions);

	OnActorBeginOverlap.AddDynamic(explosions[0], &AC02_Explosion::ActorBeginOverlap);
}


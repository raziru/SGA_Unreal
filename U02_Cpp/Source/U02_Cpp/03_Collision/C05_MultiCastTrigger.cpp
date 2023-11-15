// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Collision/C05_MultiCastTrigger.h"
#include "Global.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"

// Sets default values
AC05_MultiCastTrigger::AC05_MultiCastTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
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
void AC05_MultiCastTrigger::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &AC05_MultiCastTrigger::ActorBeginOverlap);
	OnActorEndOverlap.AddDynamic(this,   &AC05_MultiCastTrigger::ActorEndOverlap);
}



void AC05_MultiCastTrigger::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OnMultiLightBeginOverlap.IsBound())
	{
		int32 index = UKismetMathLibrary::RandomIntegerInRange(0, 2);

		FLinearColor color;
		color.R = UKismetMathLibrary::RandomFloatInRange(0, 1);
		color.G = UKismetMathLibrary::RandomFloatInRange(0, 1);
		color.B = UKismetMathLibrary::RandomFloatInRange(0, 1);
		color.A = 1.0f;

		OnMultiLightBeginOverlap.Broadcast(index, color);
	}
}

void AC05_MultiCastTrigger::ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{

}
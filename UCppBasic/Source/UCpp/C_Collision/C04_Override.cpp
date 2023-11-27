// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Collision/C04_Override.h"
#include "Global.h"
#include "Player/CPlayer.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
// Sets default values
AC04_Override::AC04_Override()
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
void AC04_Override::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &AC04_Override::ActorBeginOverlap);
	  OnActorEndOverlap.AddDynamic(this, &AC04_Override::ActorEndOverlap);
}
	
// Called every frame
void AC04_Override::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC04_Override::ChangeColorWhite_Implementation()
{
	ACPlayer* player = Cast<ACPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	player->ChangeColor(FLinearColor(0, 0, 1));
}

void AC04_Override::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	ChangeColorRed();
}

void AC04_Override::ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	ChangeColorWhite();
}


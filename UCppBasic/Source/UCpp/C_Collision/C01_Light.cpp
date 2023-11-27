// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Collision/C01_Light.h"
#include "Global.h"
#include "C_TriggerLight.h"
#include "Components/TextRenderComponent.h"
#include "Components/PointLightComponent.h"

// Sets default values
AC01_Light::AC01_Light()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	CHelpers::CreateComponent<USceneComponent>(this, &Scene, "Scene");
	CHelpers::CreateComponent<UTextRenderComponent>(this, &Text, "Text", Scene);
	CHelpers::CreateComponent<UPointLightComponent>(this, &Light, "Light", Scene);
	CHelpers::CreateComponent<UPointLightComponent>(this, &Light2, "Light2", Scene);


	Text->SetRelativeLocation(FVector(0, 0, 100));
	Text->SetRelativeRotation(FRotator(0, 180, 0));
	Text->SetRelativeScale3D(FVector(2));
	Text->TextRenderColor = FColor::Red;
	Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	Text->Text = FText::FromString(GetName());

	//1e+4f = 10^4 = 10000
	//1e-6f = 10^-6 = 0.000001;
	Light->Intensity = 1e+4f;//지수
	Light->AttenuationRadius = 200;
	Light->LightColor = FColor(255, 128, 50);

	Light2->SetRelativeLocation(FVector(0, 200, 0));
	Light2->Intensity = 1e+4f;
	Light2->AttenuationRadius = 200;
	Light2->LightColor = FColor(255, 128, 50);
}

// Called when the game starts or when spawned
void AC01_Light::BeginPlay()
{
	Super::BeginPlay();
	Light->SetVisibility(false);
	Light2->SetVisibility(false);


	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AC_TriggerLight::StaticClass(), actors);
	CheckFalse(actors.Num() > 0);//false를 확인하는것, false일때 걸린다. true면 통과한다.

	AC_TriggerLight* trigger = Cast<AC_TriggerLight>(actors[0]);//Single Cast
	trigger->OnBoxLightBeginOverlap.BindUFunction(this, "OnLight");//bind로 묶는다.
	trigger->OnBoxLightEndOverlap.BindUFunction(this, "OffLight");
	trigger->OnBoxLightRandomBeginOverlap.BindUFunction(this, "OnRandomLight");
}

void AC01_Light::OnLight()
{
	Light->SetVisibility(true);
	Light2->SetVisibility(true);
}

void AC01_Light::OffLight()
{
	Light->SetVisibility(false);
	Light2->SetVisibility(false);
}

FString AC01_Light::OnRandomLight(FLinearColor InColor)
{
	Light2->SetVisibility(true);
	Light2->SetLightColor(InColor);

	return InColor.ToString();
}




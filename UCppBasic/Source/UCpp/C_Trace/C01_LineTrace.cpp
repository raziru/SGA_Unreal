// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Trace/C01_LineTrace.h"
#include "Global.h"
#include "Player/CPlayer.h"
#include "C01_Cylinder.h"
#include "Components/TextRenderComponent.h"
// Sets default values
AC01_LineTrace::AC01_LineTrace()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CHelpers::CreateComponent<USceneComponent>(this, &Scene, "Scene");
	CHelpers::CreateComponent<UTextRenderComponent>(this, &Text, "Text", Scene);

	Text->SetRelativeLocation(FVector(0, 0, 140));
	Text->SetRelativeRotation(FRotator(0, 180, 0));
	Text->SetRelativeScale3D(FVector(2));
	Text->TextRenderColor = FColor::Red;
	Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	Text->Text = FText::FromString(GetName());
}

// Called when the game starts or when spawned
void AC01_LineTrace::BeginPlay()
{
	Super::BeginPlay();
	CHelpers::FindActors<AC01_Cylinder>(GetWorld(), Cylinders);
	OnTraceResult.AddDynamic(this, &AC01_LineTrace::StartJump);
}

// Called every frame
void AC01_LineTrace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Super::Tick(DeltaTime);
	FVector start = Cylinders[0]->GetActorLocation();
	FVector end = Cylinders[1]->GetActorLocation();

	//DrawDebugLine
	{
		start.Z -= 10;
		end.Z -= 10;

		DrawDebugLine(GetWorld(), start, end, FColor::Yellow, false);
	}
	//Line Trace
	{
		start.Z += 10;
		end.Z += 10;

		TArray<AActor*> ignoreActors;
		ignoreActors.Add(Cylinders[0]);//ignore cylinder
		ignoreActors.Add(Cylinders[1]);


		FHitResult hitResult;
		if (UKismetSystemLibrary::LineTraceSingleByProfile(GetWorld(), start, end, "Pawn",
			false, ignoreActors, EDrawDebugTrace::ForOneFrame, hitResult, true, FLinearColor::Green, FLinearColor::Red))
		{
			//CLog::Log(hitResult.GetActor()->GetName());
			if (OnTraceResult.IsBound())
			{
				FLinearColor color;
				color.R = UKismetMathLibrary::RandomFloatInRange(0, 1);
				color.G = UKismetMathLibrary::RandomFloatInRange(0, 1);
				color.B = UKismetMathLibrary::RandomFloatInRange(0, 1);
				color.A = 1.0f;

				OnTraceResult.Broadcast(hitResult.GetActor(), color);
			}
		}//if(LineTraceSingleByProfile)
	}

}

// Called to bind functionality to input
void AC01_LineTrace::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AC01_LineTrace::StartJump(AActor* InActor, FLinearColor InColor)
{
	ACPlayer* player = Cast<ACPlayer>(InActor);
	CheckNull(player);

	player->Jump();
}

void AC01_LineTrace::RestoreColor(ACPlayer* InPlayer)
{
	InPlayer->ChangeColor(FLinearColor(1, 1, 1));
}


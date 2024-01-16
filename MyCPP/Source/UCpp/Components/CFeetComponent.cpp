// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CFeetComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"

UCFeetComponent::UCFeetComponent()
{
	
	PrimaryComponentTick.bCanEverTick = true;

}


void UCFeetComponent::BeginPlay()
{
	Super::BeginPlay();
	OwnerCharacter = Cast<ACharacter>(GetOwner());

	
}


void UCFeetComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	float LeftDistance;
	Trace(LeftSocket, LeftDistance);

	Data.LeftDistance.X = UKismetMathLibrary::FInterpTo(
		Data.LeftDistance.X, LeftDistance, DeltaTime, InterpSpeed
	);
}

void UCFeetComponent::Trace(FName InSocket, float& OutDistance)
{
	OutDistance = 0.0f;


	FVector location = OwnerCharacter->GetMesh()->GetSocketLocation(InSocket);
	FVector start = FVector(location.X, location.Y, OwnerCharacter->GetActorLocation().Z);

	float traceZ = start.Z - OwnerCharacter->GetCapsuleComponent()->GetScaledCapsuleHalfHeight() - TraceDistance;
	FVector end = FVector(location.X, location.Y, traceZ);

	//DrawDebugLine(GetWorld(), start, end, FColor::Green);

	TArray<AActor*> ignoreActors;
	ignoreActors.Add(OwnerCharacter);

	FHitResult hitResult;
	UKismetSystemLibrary::LineTraceSingle(
		GetWorld(), start, end,
		UEngineTypes::ConvertToTraceType(ECC_Visibility), //눈에 보이는 것은 전부 추적
		true, ignoreActors,
		DrawDebugType, hitResult, true,
		FLinearColor::Green, FLinearColor::Red
	);
}



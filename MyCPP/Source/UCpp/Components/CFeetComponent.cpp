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
	FRotator LeftRotation;
	Trace(LeftSocket, LeftDistance, LeftRotation);

	float RightDistance;
	FRotator RightRotation;

	Trace(RightSocket, RightDistance, RightRotation);

	float offset = FMath::Min(LeftDistance, RightDistance);

	//Global 연산
	Data.PelvisDistance.Z = UKismetMathLibrary::FInterpTo(Data.PelvisDistance.Z, offset, DeltaTime, InterpSpeed);

	//local 연산
	Data.LeftDistance.X = UKismetMathLibrary::FInterpTo(
		Data.LeftDistance.X, (LeftDistance - offset), DeltaTime, InterpSpeed
	);

	//local 연산 - 축기준으로 완전히 반전되어 있기 때문에 마이너스를 붙여서 음수로 만든다.
	Data.RightDistance.X = UKismetMathLibrary::FInterpTo(
		Data.RightDistance.X, -(RightDistance - offset), DeltaTime, InterpSpeed
	);

	Data.LeftRotation = UKismetMathLibrary::RInterpTo(Data.LeftRotation, LeftRotation, DeltaTime, InterpSpeed);
	Data.RightRotation = UKismetMathLibrary::RInterpTo(Data.RightRotation, RightRotation, DeltaTime, InterpSpeed);

}

void UCFeetComponent::Trace(FName InSocket, float& OutDistance, FRotator& OutRotation)
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

	CheckFalse(hitResult.IsValidBlockingHit());

	//충돌지점에서 트레이스 종료거리 차이 계산
	float length = (hitResult.ImpactPoint - hitResult.TraceEnd).Size();
	//TraceDistance : half to trace. OffsetDistance : 길이 보정값
	OutDistance = OffsetDistance + length - TraceDistance;

	FVector normal = hitResult.ImpactNormal;
	float roll = UKismetMathLibrary::DegAtan2(normal.Y, normal.Z);
	float pitch = -UKismetMathLibrary::DegAtan2(normal.X, normal.Z);//지면 기울기의 반대 방향으로 반작용이 가해지기때문에 각도가 반대로 된다.

	OutRotation = FRotator(pitch, 0.0f, roll);
}



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

	//Global ����
	Data.PelvisDistance.Z = UKismetMathLibrary::FInterpTo(Data.PelvisDistance.Z, offset, DeltaTime, InterpSpeed);

	//local ����
	Data.LeftDistance.X = UKismetMathLibrary::FInterpTo(
		Data.LeftDistance.X, (LeftDistance - offset), DeltaTime, InterpSpeed
	);

	//local ���� - ��������� ������ �����Ǿ� �ֱ� ������ ���̳ʽ��� �ٿ��� ������ �����.
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
		UEngineTypes::ConvertToTraceType(ECC_Visibility), //���� ���̴� ���� ���� ����
		true, ignoreActors,
		DrawDebugType, hitResult, true,
		FLinearColor::Green, FLinearColor::Red
	);

	CheckFalse(hitResult.IsValidBlockingHit());

	//�浹�������� Ʈ���̽� ����Ÿ� ���� ���
	float length = (hitResult.ImpactPoint - hitResult.TraceEnd).Size();
	//TraceDistance : half to trace. OffsetDistance : ���� ������
	OutDistance = OffsetDistance + length - TraceDistance;

	FVector normal = hitResult.ImpactNormal;
	float roll = UKismetMathLibrary::DegAtan2(normal.Y, normal.Z);
	float pitch = -UKismetMathLibrary::DegAtan2(normal.X, normal.Z);//���� ������ �ݴ� �������� ���ۿ��� �������⶧���� ������ �ݴ�� �ȴ�.

	OutRotation = FRotator(pitch, 0.0f, roll);
}



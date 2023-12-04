// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/CAttachment.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/ShapeComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"

// Sets default values
ACAttachment::ACAttachment()
{
	CHelpers::CreateComponent<USceneComponent>(this, &Scene, "Scene");

}



// Called when the game starts or when spawned
void ACAttachment::BeginPlay()
{
	//이 노드에 함수가 연결될 경우 연결된 함수가 Super::BeginPlay()에서 실행되고 이어서 작성한 코드들이 실행된다.
	//그래서 변수 할당을 먼저하고 부모함수를 호출해야 null참조가 발생하지 않는다.
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	State = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);
	Status = CHelpers::GetComponent<UCStatusComponent>(OwnerCharacter);
	Super::BeginPlay();
	
}
void ACAttachment::OnCollision()
{
}

void ACAttachment::OffCollision()
{
}

void ACAttachment::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}
void ACAttachment::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}
void ACAttachment::AttachTo(FName InSocketName)
{
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), InSocketName);
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/CAttachment.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CStateComponent.h"
//#include "Components/CStatusComponent.h"

// Sets default values
ACAttachment::ACAttachment()
{
 	
}

// Called when the game starts or when spawned
void ACAttachment::BeginPlay()
{
	//�� ��忡 �Լ��� ����� ��� ����� �Լ��� Super::BeginPlay()���� ����ǰ� �̾ �ۼ��� �ڵ���� ����ȴ�.
	//�׷��� ���� �Ҵ��� �����ϰ� �θ��Լ��� ȣ���ؾ� null������ �߻����� �ʴ´�.
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	State = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);
	//Status = CHelpers::GetComponent<UCStatusComponent>(OwnerCharacter);
	Super::BeginPlay();
	
}
void ACAttachment::AttachTo(FName InSocketName)
{
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), InSocketName);
}


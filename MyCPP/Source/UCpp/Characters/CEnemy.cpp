// Fill out your copyright notice in the Description page of Project Settings.


#include "CEnemy.h"
#include "Global.h"
#include "Actions/CActionData.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimInstance.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/CActionComponent.h"
#include "Components/CStatusComponent.h"
#include "Components/CMontagesComponent.h"
#include "Components/CDialogueComponent.h"
#include "Components/CPickupComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/WidgetComponent.h"
#include "Widgets/CUserWidget_Name.h"
#include "Widgets/CUserWidget_Health.h"


// Sets default values
ACEnemy::ACEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	CHelpers::CreateComponent<UWidgetComponent>(this, &NameWidget, "NameWidget", GetMesh());
	CHelpers::CreateComponent<UWidgetComponent>(this, &HealthWidget, "HealthWidget", GetMesh());

	CHelpers::CreateActorComponent<UCActionComponent>(this, &Action, "Action");
	CHelpers::CreateActorComponent<UCMontagesComponent>(this, &Montages, "Montages");
	CHelpers::CreateActorComponent<UCStatusComponent>(this, &Status, "Status");
	CHelpers::CreateActorComponent<UCStateComponent>(this, &State, "State");
	CHelpers::CreateActorComponent<UCDialogueComponent>(this, &Dialogue, "Dialogue");
	CHelpers::CreateActorComponent<UCPickupComponent>(this, &Pickup, "Pickup");



	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	
	USkeletalMesh* mesh;
	CHelpers::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/Character/Mesh/SK_Mannequin.SK_Mannequin'");
	GetMesh()->SetSkeletalMesh(mesh);
	
	GetCharacterMovement()->RotationRate = FRotator(0, 720, 0);

	TSubclassOf<UCUserWidget_Name> nameClass;
	CHelpers::GetClass<UCUserWidget_Name>(&nameClass, "WidgetBlueprint'/Game/Widgets/WB_Name.WB_Name_C'");
	NameWidget->SetWidgetClass(nameClass);
	NameWidget->SetRelativeLocation(FVector(0, 0, 240));
	NameWidget->SetDrawSize(FVector2D(240, 30));
	NameWidget->SetWidgetSpace(EWidgetSpace::Screen);

	TSubclassOf<UCUserWidget_Health> healthClass;
	CHelpers::GetClass<UCUserWidget_Health>(&healthClass, "WidgetBlueprint'/Game/Widgets/WB_Health.WB_Health_C'");
	HealthWidget->SetWidgetClass(healthClass);
	HealthWidget->SetRelativeLocation(FVector(0, 0, 190));
	HealthWidget->SetDrawSize(FVector2D(120, 20));
	HealthWidget->SetWidgetSpace(EWidgetSpace::Screen);

}



// Called when the game starts or when spawned
void ACEnemy::BeginPlay()
{
	//construct helper외의 create는 생성자에서 사용할 수 없다.
	//그리고 begin play전에 실행해야 제대로 반영된다.
	InteractType = OwnInteractType;

	UMaterialInstanceConstant* body;
	UMaterialInstanceConstant* logo;

	CHelpers::GetAssetDynamic<UMaterialInstanceConstant>(&body, "MaterialInstanceConstant'/Game/Materials/M_UE4Man_Body_Inst.M_UE4Man_Body_Inst'");
	CHelpers::GetAssetDynamic<UMaterialInstanceConstant>(&logo, "MaterialInstanceConstant'/Game/Materials/M_UE4Man_ChestLogo_Inst.M_UE4Man_ChestLogo_Inst'");

	BodyMaterial = UMaterialInstanceDynamic::Create(body, this);
	LogoMaterial = UMaterialInstanceDynamic::Create(logo, this);

	GetMesh()->SetMaterial(0, BodyMaterial);
	GetMesh()->SetMaterial(1, LogoMaterial);

	Super::BeginPlay();
	
	State->OnStateTypeChanged.AddDynamic(this, &ACEnemy::OnStateTypeChanged);

	NameWidget->InitWidget();
	Cast<UCUserWidget_Name>(NameWidget->GetUserWidgetObject())->SetNameText(GetActorLabel());

	HealthWidget->InitWidget();
	Cast<UCUserWidget_Health>(HealthWidget->GetUserWidgetObject())->Update(Status->GetHealth(), Status->GetMaxHealth());

	
	//Action->SetUnarmedMode();
	//OnUnarmed();
}

// Called every frame
void ACEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACEnemy::ChangeColor(FLinearColor InColor)
{
	BodyMaterial->SetVectorParameterValue("BodyColor", InColor);
	LogoMaterial->SetVectorParameterValue("BodyColor", InColor);
}

void ACEnemy::Interact(AActor* InOther)
{
	CLog::Print(InOther->GetName());
	//Dialogue->ShowDialogue();
	//CHelpers::GetComponent(&Dialogue);
	/*if (State->IsCorpseMode())
	{
		InteractType = EInteractType::Openable;
		
		Pickup->Pickup(InOther);
	}
	else
	{
		InteractType = EInteractType::Speakable;

		Dialogue->SpeakTo(InOther);
	}*/
	

	switch (InteractType)
	{
	case EInteractType::Speakable:
		Dialogue->SpeakTo(InOther);
		break;
	case EInteractType::Pickable:
		Pickup->Pickup(InOther);
		break;
	case EInteractType::Openable:
		Pickup->Pickup(InOther);
		break;
	case EInteractType::Disabled:
		break;
	case EInteractType::Max:
		break;
	default:
		break;
	}
	
	//Destroy();
}

void ACEnemy::OnDefaultMode()
{
	OnUnarmed();
}



float ACEnemy::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	DamageInstigator = EventInstigator;
	if (State->IsCorpseMode())
	{
		DamageValue = 0;

	}
	else
	{
		DamageValue = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
		State->SetHittedMode();

	}
	CLog::Log(Damage);

	return Status->GetHealth();
}

void ACEnemy::OnStateTypeChanged(EStateType InPrevType, EStateType InNewType)
{
	switch (InNewType)
	{
	case EStateType::Hitted: Hitted(); break;
	case EStateType::Backstep: Begin_Backstep(); break;
	case EStateType::Dead: Dead(); break;
	}
}

void ACEnemy::OnUnarmed()
{
	CheckFalse(State->IsIdleMode());
	Action->SetUnarmedMode();
}

void ACEnemy::Hitted()
{
	Status->SubHealth(DamageValue);
	Cast<UCUserWidget_Health>(HealthWidget->GetUserWidgetObject())->Update(Status->GetHealth(), Status->GetMaxHealth());
	DamageValue = 0.0f;

	if (Status->GetHealth() <= 0.0f)
	{
		State->SetDeadMode();

		return;
	}

	Status->SetStop();


	FVector start = GetActorLocation();
	FVector target = DamageInstigator->GetPawn()->GetActorLocation();
	SetActorRotation(UKismetMathLibrary::FindLookAtRotation(start, target));
	DamageInstigator = NULL;

	FVector direction = target - start;
	direction.Normalize();
	LaunchCharacter(-direction * LaunchAmount, true, false);//z축이 개입할거냐 아닐거냐

	ChangeColor(FLinearColor(1, 0, 0, 1));

	UKismetSystemLibrary::K2_SetTimer(this, "RestoreColor", 0.1f, false);//delay
	Montages->PlayHitted();
}

void ACEnemy::Dead()
{
	CheckFalse(State->IsDeadMode());

	Montages->PlayDead();
}
void ACEnemy::Begin_Backstep()
{
	CheckFalse(State->IsIdleMode());
	Montages->PlayBackstep();

}

void ACEnemy::End_Backstep()
{
	State->SetIdleMode();
}
void ACEnemy::Begin_Dead()
{
	Action->OffAllCollision();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
void ACEnemy::End_Dead()
{
	
	HealthWidget->SetVisibility(false);
	InteractType = EInteractType::Openable;
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	State->SetCorpseMode();

	//InteractType = EInteractType::Openable;


}
void ACEnemy::RestoreColor()
{
	FLinearColor color = Action->GetCurrent()->GetEquipmentColor();
	ChangeColor(color);
}

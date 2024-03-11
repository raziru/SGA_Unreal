// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/CPlayer.h"
#include "Global.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Animation/AnimInstance.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/InputComponent.h"
#include "Components/CTargetComponent.h"
#include "Components/COptionComponent.h"
#include "Components/CInteractComponent.h"
#include "Components/CMontagesComponent.h"
#include "Components/CFeetComponent.h"
#include "Components/CStatusComponent.h"
#include "Components/CEquipComponent.h"
#include "Components/CDialogueComponent.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/WidgetComponent.h"
#include "Widgets/CUserWidget_Name.h"
#include "Widgets/Action/CUserWidget_ActionList.h"
#include "Widgets/CUserWidget_Health.h"



// Sets default values
ACPlayer::ACPlayer()
{
	PrimaryActorTick.bCanEverTick = true;
	CHelpers::CreateComponent<USpringArmComponent>(this, &SpringArm, "SpringArm", GetMesh());
	CHelpers::CreateComponent<UCameraComponent>(this, &Camera, "Camera", SpringArm);
	CHelpers::CreateComponent<UBoxComponent>(this, &InteractBox, "InteractBox", GetMesh());



	//기능만 달린 컴포넌트들을 생성하여 player 클래스를 관리하기 쉽게한다.

	//ActionComponent에 DataAsset을 둬서 무기 종류, 장착방식, 장비 정보를 Asset에서 자유롭게 설정하고
	//그 내용을 캐릭터가 가져가서 사용하게 만든다. 재사용성과 추상화를 신경쓴 설계
	CHelpers::CreateActorComponent<UCActionComponent>(this, &Action, "Action");
	CHelpers::CreateActorComponent<UCTargetComponent>(this, &Target, "Target");
	CHelpers::CreateActorComponent<UCMontagesComponent>(this, &Montages, "Montages");
	CHelpers::CreateActorComponent<UCFeetComponent>(this, &Feet, "Feet");

	CHelpers::CreateActorComponent<UCOptionComponent>(this, &Option, "Option");

	CHelpers::CreateActorComponent<UCStatusComponent>(this, &Status, "Status");
	CHelpers::CreateActorComponent<UCStateComponent>(this, &State, "State");
	CHelpers::CreateActorComponent<UCInteractComponent>(this, &Interaction, "Interact");
	CHelpers::CreateActorComponent<UCInventoryComponent>(this, &Inventory, "Inventory");
	CHelpers::CreateActorComponent<UCEquipComponent>(this, &Equipment, "Equipment");
	CHelpers::CreateActorComponent<UCDialogueComponent>(this, &Dialogue, "Dialogue");



	USkeletalMesh* mesh;
	CHelpers::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/Character/Mesh/SK_Mannequin.SK_Mannequin'");
	GetMesh()->SetSkeletalMesh(mesh);

	TSubclassOf<UAnimInstance> animInstance;
	CHelpers::GetClass<UAnimInstance>(&animInstance, "AnimBlueprint'/Game/Player/ABP_CPlayer.ABP_CPlayer_C'");
	GetMesh()->SetAnimInstanceClass(animInstance);

	SpringArm->SetRelativeLocation(FVector(0, 0, 140));
	SpringArm->SetRelativeRotation(FRotator(0, 90, 0));
	SpringArm->TargetArmLength = 250.0f;
	SpringArm->bDoCollisionTest = false;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bEnableCameraLag = true;

	InteractBox->SetRelativeLocation(FVector(0, 80, 100));
	InteractBox->SetRelativeScale3D(FVector(3, 3, 3));


	GetCharacterMovement()->RotationRate = FRotator(0, 720, 0);
	GetCharacterMovement()->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;

	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	TSubclassOf<UCUserWidget_Health> statusClass;
	CHelpers::GetClass<UCUserWidget_Health>(&statusClass, "WidgetBlueprint'/Game/Widgets/WB_PlayerStatus.WB_PlayerStatus_C'");
	StatusWidget = Cast<UCUserWidget_Health>(CreateWidget(GetWorld(), statusClass));
}

void ACPlayer::BeginPlay()
{
	UMaterialInstanceConstant* body;
	UMaterialInstanceConstant* logo;

	CHelpers::GetAssetDynamic<UMaterialInstanceConstant>(&body, "MaterialInstanceConstant'/Game/Materials/M_UE4Man_Body_Inst.M_UE4Man_Body_Inst'");
	CHelpers::GetAssetDynamic<UMaterialInstanceConstant>(&logo, "MaterialInstanceConstant'/Game/Materials/M_UE4Man_ChestLogo_Inst.M_UE4Man_ChestLogo_Inst'");

	BodyMaterial = UMaterialInstanceDynamic::Create(body, this);
	LogoMaterial = UMaterialInstanceDynamic::Create(logo, this);

	GetMesh()->SetMaterial(0, BodyMaterial);
	GetMesh()->SetMaterial(1, LogoMaterial);

	Super::BeginPlay();
	//Action->SetUnarmedMode();
	Status->SetSpeed(ECharacterSpeed::Run);
	Inventory->SetCanChange(true);
	//State에서 선언한 OnstatetypeChanged가 broadcast로 호출되면 
	//묶여있는 함수가 같이 연계된다. --  delegate는 함수포인터를 사용한것과 비슷하다.
	//함수포인터는 인자로 받아야하지만 delegate는 필요가없다.

	Action->OnActionTypeChanged.AddDynamic(this, &ACPlayer::OnActionTypeChanged);
	Action->EquipSecond.AddDynamic(this, &ACPlayer::EquipSecond);
	Action->UnequipSecond.AddDynamic(this, &ACPlayer::UnequipSecond);
	Action->EndConsumableAction.AddDynamic(Inventory, &UCInventoryComponent::EndConsumableAction);



	State->OnStateTypeChanged.AddDynamic(this, &ACPlayer::OnStateTypeChanged);
	Inventory->SetNewMainWeapon.AddDynamic(Action,&UCActionComponent::SetNewMainWeapon);
	Inventory->SetNewArmor.AddDynamic(Equipment,&UCEquipComponent::SetNewArmor);
	Inventory->SetNewTool.AddDynamic(Action,&UCActionComponent::SetNewTool);
	Inventory->SetNewConsumable.AddDynamic(Action,&UCActionComponent::SetNewConsumable);

	Equipment->OnShield.AddDynamic(Action, &UCActionComponent::OnAdditionalAttachment);
	Equipment->OffShield.AddDynamic(Action, &UCActionComponent::OffAdditionalAttachment);

	Equipment->SetNewStatus.AddDynamic(this, &ACPlayer::SetNewStatus);


	Status->RefreshStatus.AddDynamic(this, &ACPlayer::ResfreshStatus);

	Action->GetActionList()->GetData(0).OnUserWidget_ActionItem_Clicked.AddDynamic(this, &ACPlayer::OnFist);
	Action->GetActionList()->GetData(1).OnUserWidget_ActionItem_Clicked.AddDynamic(this, &ACPlayer::OnOneHand);
	Action->GetActionList()->GetData(2).OnUserWidget_ActionItem_Clicked.AddDynamic(this, &ACPlayer::OnTwoHand);
	Action->GetActionList()->GetData(3).OnUserWidget_ActionItem_Clicked.AddDynamic(this, &ACPlayer::OnWarp);
	Action->GetActionList()->GetData(4).OnUserWidget_ActionItem_Clicked.AddDynamic(this, &ACPlayer::OnFireStorm);
	Action->GetActionList()->GetData(5).OnUserWidget_ActionItem_Clicked.AddDynamic(this, &ACPlayer::OnThrow);

	UpdateWidget();
	StatusWidget->AddToViewport();
	StatusWidget->SetVisibility(ESlateVisibility::Hidden);

}



FGenericTeamId ACPlayer::GetGenericTeamId() const
{
	return FGenericTeamId(TeamId);
}

void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &ACPlayer::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACPlayer::OnMoveRight);
	PlayerInputComponent->BindAxis("HorizontalLook", this, &ACPlayer::OnHorizontalLook);
	PlayerInputComponent->BindAxis("VerticalLook", this, &ACPlayer::OnVerticalLook);
	PlayerInputComponent->BindAxis("Zoom", this, &ACPlayer::OnZoom);

	PlayerInputComponent->BindAction("Avoid", EInputEvent::IE_Pressed, this, &ACPlayer::OnAvoidAndJump);
	PlayerInputComponent->BindAction("Avoid", EInputEvent::IE_Released, this, &ACPlayer::OnJumpEnd);


	PlayerInputComponent->BindAction("Walk", EInputEvent::IE_Pressed, this, &ACPlayer::OnWalk);
	PlayerInputComponent->BindAction("Walk", EInputEvent::IE_Released, this, &ACPlayer::OffWalk);

	
	PlayerInputComponent->BindAction("Fist", EInputEvent::IE_Pressed, this, &ACPlayer::OnFist);
	PlayerInputComponent->BindAction("OneHand", EInputEvent::IE_Pressed, this, &ACPlayer::OnOneHand);
	PlayerInputComponent->BindAction("TwoHand", EInputEvent::IE_Pressed, this, &ACPlayer::OnTwoHand);
	PlayerInputComponent->BindAction("Warp", EInputEvent::IE_Pressed, this, &ACPlayer::OnWarp);
	PlayerInputComponent->BindAction("FireStorm", EInputEvent::IE_Pressed, this, &ACPlayer::OnFireStorm);
	PlayerInputComponent->BindAction("ItemType", EInputEvent::IE_Pressed, this, &ACPlayer::OnMainWeapon);

	PlayerInputComponent->BindAction("RightAction", EInputEvent::IE_Pressed, this, &ACPlayer::OnDoSecondAction);
	PlayerInputComponent->BindAction("RightAction", EInputEvent::IE_Released, this, &ACPlayer::OnDoSecondActionRelease);

	PlayerInputComponent->BindAction("Throw", EInputEvent::IE_Pressed, this, &ACPlayer::OnThrow);
	PlayerInputComponent->BindAction("Action", EInputEvent::IE_Pressed, this, &ACPlayer::OnDoAction);
	PlayerInputComponent->BindAction("Action", EInputEvent::IE_Released, this, &ACPlayer::OnDoActionRelease);

	PlayerInputComponent->BindAction("Targeting", EInputEvent::IE_Pressed, this, &ACPlayer::OnTarget);
	PlayerInputComponent->BindAction("TargetLeft", EInputEvent::IE_Pressed, this, &ACPlayer::OnTargetLeft);
	PlayerInputComponent->BindAction("TargetRight", EInputEvent::IE_Pressed, this, &ACPlayer::OnTargetRight);

	PlayerInputComponent->BindAction("Interact", EInputEvent::IE_Pressed, this, &ACPlayer::Interact);
	PlayerInputComponent->BindAction("Inventory", EInputEvent::IE_Pressed, this, &ACPlayer::OpenInventory);
	PlayerInputComponent->BindAction("MagicInventory", EInputEvent::IE_Pressed, this, &ACPlayer::OpenMagicInventory);

	PlayerInputComponent->BindAction("UseTool", EInputEvent::IE_Pressed, this, &ACPlayer::OnTool);

	PlayerInputComponent->BindAction("QuickSlot", EInputEvent::IE_Pressed, this, &ACPlayer::OnViewActionList);
	PlayerInputComponent->BindAction("QuickSlot", EInputEvent::IE_Released, this, &ACPlayer::OffViewActionList);

}

//Moving
void ACPlayer::OnMoveForward(float InAxis)
{
	CheckFalse(Status->CanMove());

	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetForwardVector();

	AddMovementInput(direction, InAxis);
}

void ACPlayer::OnMoveRight(float InAxis)
{
	CheckFalse(Status->CanMove());

	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetRightVector();

	AddMovementInput(direction, InAxis);
}

void ACPlayer::OnHorizontalLook(float InAxis)
{
	float rate = Option->GetHorizontalLookRate();
	AddControllerYawInput(InAxis * rate * GetWorld()->GetDeltaSeconds());
}

void ACPlayer::OnVerticalLook(float InAxis)
{
	float rate = Option->GetVerticalLookRate();
	AddControllerPitchInput(InAxis * rate * GetWorld()->GetDeltaSeconds());
}

void ACPlayer::OnZoom(float InAxis)
{
	SpringArm->TargetArmLength += (1000.0f * InAxis * GetWorld()->GetDeltaSeconds());
	SpringArm->TargetArmLength = FMath::Clamp(SpringArm->TargetArmLength, 50.0f, 500.0f);
}

void ACPlayer::OnAvoidAndJump()
{
	CheckFalse(State->IsIdleMode());
	if (Action->IsUnarmedMode())
	{
		OnJumpStart();
	}
	else
	{
		OnAvoid();
	}
}

void ACPlayer::OnAvoid()
{
	CheckFalse(State->IsIdleMode());
	if (InputComponent->GetAxisValue("MoveForward") < 0.0f)
	{
		State->SetBackstepMode();

		return;
	}

	State->SetRollMode();
}

void ACPlayer::OnJumpStart()
{
	CheckFalse(State->IsIdleMode());
	State->SetJumpMode();
	bPressedJump = true;
}

void ACPlayer::OnJumpEnd()
{
	CheckFalse(State->IsJumpMode());

	bPressedJump = false;
	State->SetIdleMode();

}

void ACPlayer::OnStateTypeChanged(EStateType InPrevType, EStateType InNewType)
{

	switch (InNewType)
	{
		case EStateType::Roll:  Begin_Roll(); break;
		case EStateType::Backstep: Begin_Backstep(); break;
		case EStateType::Hitted: Hitted(); break;
		case EStateType::Dead: Dead(); break;

	}
	if (InNewType == EStateType::Idle)
	{
		Inventory->SetCanChange(true);
	}
	else
	{
		Inventory->SetCanChange(false);
	}
}

float ACPlayer::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
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

void ACPlayer::Begin_Dead()
{
}

void ACPlayer::End_Dead()
{
	//FGenericPlatformMisc::RequestExit(false);
	UKismetSystemLibrary::QuitGame(this, 0, EQuitPreference::Quit, false);
}

void ACPlayer::Hitted()
{
	Status->SubHealth(DamageValue);
	StatusWidget->Update(Status->GetHealth(), Status->GetMaxHealth());
	//Cast<UCUserWidget_Health>(HealthWidget->GetUserWidgetObject())->Update(Status->GetHealth(), Status->GetMaxHealth());
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

void ACPlayer::Dead()
{
	CheckFalse(State->IsDeadMode());

	Montages->PlayDead();
}

void ACPlayer::RestoreColor()
{
	FLinearColor color = Action->GetCurrent()->GetEquipmentColor();
	ChangeColor(color);
	Status->SetMove();
}

void ACPlayer::EquipSecond(EActionType InActionType)
{
	switch (InActionType)
	{
	case EActionType::Unarmed:
		break;
	case EActionType::Fist:
		break;
	case EActionType::OneHand:
		Equipment->OnSecondEquip(EArmorType::Shield);
		break;
	case EActionType::TwoHand:
		break;
	case EActionType::Warp:
		break;
	case EActionType::FireStorm:
		break;
	case EActionType::Throw:
		break;
	case EActionType::Max:
		break;
	default:
		break;
	}
}

void ACPlayer::UnequipSecond(EActionType InActionType)
{
	switch (InActionType)
	{
	case EActionType::Unarmed:
		break;
	case EActionType::Fist:
		break;
	case EActionType::OneHand:
		Equipment->OnSecondUnEquip(EArmorType::Shield);
		break;
	case EActionType::TwoHand:
		break;
	case EActionType::Warp:
		break;
	case EActionType::FireStorm:
		break;
	case EActionType::Throw:
		break;
	case EActionType::Max:
		break;
	default:
		break;
	}
}

void ACPlayer::SetNewStatus(const FStatusData NewStatus)
{
	Status->SetNewStatus(NewStatus);
	UpdateWidget();

}

void ACPlayer::ResfreshStatus(const FStatusData NewStatus)
{
	//GetCharacterMovement()->MaxWalkSpeed = NewStatus.Speed[(int32)ECharacterSpeed::Run];
}

//Interacting
void ACPlayer::Interact()
{
	Interaction->Interact();
}


void ACPlayer::OnDefaultMode()
{
	OnUnarmed();
}

void ACPlayer::BPAddHealth(float InAmount)
{
	Status->AddHealth(InAmount);
	UpdateWidget();

}

void ACPlayer::BPSubHealth(float InAmount)
{
	Status->SubHealth(InAmount);
	UpdateWidget();

}

void ACPlayer::BPAddMana(float InAmount)
{
	Status->AddMana(InAmount);
	UpdateWidget();

}

void ACPlayer::BPSubMana(float InAmount)
{
	Status->SubMana(InAmount);
	UpdateWidget();

}

void ACPlayer::BPAddStatus(FStatusData InStatusData)
{
	SetNewStatus(InStatusData);
}

void ACPlayer::PickupMagic(ACItem* InItem)
{
	Inventory->PickupMagic(InItem);
}

void ACPlayer::OpenInventory()
{
	Inventory->OpenInventory();
}

void ACPlayer::OpenMagicInventory()
{
	Inventory->OpenMagicInventory();
}

void ACPlayer::Begin_Roll()
{
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	FVector start = GetActorLocation();
	FVector from = start + GetVelocity().GetSafeNormal2D();
	SetActorRotation(UKismetMathLibrary::FindLookAtRotation(start, from));

	Montages->PlayRoll();
}

void ACPlayer::End_Roll()
{
	if (Action->IsUnarmedMode() == false)
	{
		bUseControllerRotationYaw = true;
		GetCharacterMovement()->bOrientRotationToMovement = false;
	}

	State->SetIdleMode();
}

void ACPlayer::Begin_Backstep()
{
	bUseControllerRotationYaw = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	Montages->PlayBackstep();
	
}

void ACPlayer::End_Backstep()
{
	if (Action->IsUnarmedMode())
	{
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bOrientRotationToMovement = true;
	}

	State->SetIdleMode();
}

void ACPlayer::OnUnarmed()
{
	CheckFalse(State->IsIdleMode());
	Action->SetUnarmedMode();
}

void ACPlayer::OnFist()
{
	CheckFalse(State->IsIdleMode());

	Action->SetFistMode();
}
void ACPlayer::OnOneHand()
{
	CheckFalse(State->IsIdleMode());

	Action->SetOneHandMode();
}


void ACPlayer::OnTwoHand()
{
	CheckFalse(State->IsIdleMode());

	Action->SetTwoHandMode();
}
void ACPlayer::OnWarp()
{

	CheckFalse(State->IsIdleMode());

	Action->SetWarpMode();
}
void ACPlayer::OnFireStorm()
{
	CheckFalse(State->IsIdleMode());

	Action->SetFireStormMode();
}
void ACPlayer::OnThrow()
{
	CheckFalse(State->IsIdleMode());

	Action->SetThrowMode();
}
void ACPlayer::OnActionTypeChanged(EActionType InPrevType, EActionType InNewType)
{
	if (InNewType == EActionType::Unarmed)
	{
		StatusWidget->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		StatusWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void ACPlayer::OnWalk()
{
	Status->SetSpeed(ECharacterSpeed::Walk);
}

void ACPlayer::OffWalk()
{
	Status->SetSpeed(ECharacterSpeed::Run);

}

void ACPlayer::OnMainWeapon()
{
	CheckFalse(State->IsIdleMode());

	Action->SetMainWeaponMode();
}


void ACPlayer::OnTool()
{
	CheckFalse(State->IsIdleMode());
	Action->SetToolMode();
	Inventory->OpenInventory();
}

void ACPlayer::UpdateWidget()
{
	StatusWidget->Update(Status->GetHealth(), Status->GetMaxHealth());
	StatusWidget->UpdateMana(Status->GetMana(), Status->GetMaxMana());
}

void ACPlayer::OnDoAction()
{
	Action->DoAction();
}

void ACPlayer::OnDoActionRelease()
{
	Action->DoActionRelease();
}

void ACPlayer::OnDoSecondAction()
{
	Action->DoSecondAction();
}

void ACPlayer::OnDoSecondActionRelease()
{
	Action->DoSecondActionRelease();
}

void ACPlayer::OnTarget()
{
	Target->ToggleTarget();
}

void ACPlayer::OnTargetLeft()
{
	Target->ChangeTargetLeft();
}

void ACPlayer::OnTargetRight()
{
	Target->ChangeTargetRight();
}

void ACPlayer::OnAim()
{
	Action->OnAim();
}

void ACPlayer::OffAim()
{
	Action->OffAim();
}

void ACPlayer::OnViewActionList()
{
	CheckFalse(State->IsIdleMode());

	Action->OnViewActionList();
}

void ACPlayer::OffViewActionList()
{
	Action->OffViewActionList();
}



void ACPlayer::ChangeColor(FLinearColor InColor)
{
	BodyMaterial->SetVectorParameterValue("BodyColor", InColor);
	LogoMaterial->SetVectorParameterValue("BodyColor", InColor);
}



#include "CAim.h"
#include "Global.h"
#include "HUD/CHUD.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CStateComponent.h"

UCAim::UCAim()
{
	CHelpers::GetAssetDynamic<UCurveFloat>(&Curve, "CurveFloat'/Game/Actions/Curve/C_Aim.C_Aim'");
}

void UCAim::BeginPlay(ACharacter* InCharacter)
{
	OwnerCharacter = InCharacter;

	SpringArm = CHelpers::GetComponent<USpringArmComponent>(OwnerCharacter);
	Camera = CHelpers::GetComponent<UCameraComponent>(OwnerCharacter);
	State = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);

	HUD = OwnerCharacter->GetWorld()->GetFirstPlayerController()->GetHUD<ACHUD>();

	TimelineFloat.BindUFunction(this, "Zooming");

	Timeline.AddInterpFloat(Curve, TimelineFloat);
	Timeline.SetPlayRate(200);
}

void UCAim::OnZoom()
{
	CheckFalse(IsAvaliable());
	CheckTrue(bInZoom);

	bInZoom = true;

	SpringArm->TargetArmLength = 100.0f;
	SpringArm->SocketOffset = FVector(0, 30, 10);
	SpringArm->bEnableCameraLag = false;

	//Camera->FieldOfView = 45;

	Timeline.PlayFromStart();
	HUD->SetDrawMode();
}

void UCAim::OffZoom()
{
	CheckFalse(bInZoom);

	bInZoom = false;

	SpringArm->TargetArmLength = 250.0f;
	SpringArm->SocketOffset = FVector(0, 0, 0);
	SpringArm->bEnableCameraLag = true;

	//Camera->FieldOfView = 90;

	HUD->SetUndrawMode();
	Timeline.ReverseFromEnd();

}

void UCAim::Tick(float DeltaTime)
{
	Timeline.TickTimeline(DeltaTime);

}

void UCAim::Zooming(float Output)
{
	CLog::Print(Output, 0);
	Camera->FieldOfView = Output;
}

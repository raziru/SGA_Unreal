// Fill out your copyright notice in the Description page of Project Settings.


#include "CDoAction_Warp.h"
#include "Global.h"
#include "CAttachment.h"
#include "CAim.h"
#include "GameFramework/Character.h"
#include "Components/DecalComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"


void ACDoAction_Warp::BeginPlay()
{
    Super::BeginPlay();

    Aim = NewObject<UCAim>();//Unreal Gabarge 컬렉터에서 인식하게 만들기 위함

    Aim->BeginPlay(OwnerCharacter);

    for (AActor* actor : OwnerCharacter->Children)
    {
        if (actor->IsA<ACAttachment>() && actor->GetActorLabel().Contains("Warp"))
        {
            Decal = CHelpers::GetComponent<UDecalComponent>(actor);

            break;
        }
    }

    
}

void ACDoAction_Warp::DoAction()
{
    CheckFalse(*bEquipped);

    FRotator rotator;
    CheckFalse(GetCrursorLocationAndRotation(Location, rotator));

    CheckFalse(State->IsIdleMode());
    State->SetActionMode();

    Decal->SetWorldLocation(Location);
    Decal->SetWorldRotation(rotator);

    OwnerCharacter->PlayAnimMontage(Datas[0].AnimMontage, Datas[0].PlayRatio, Datas[0].StartSection);

    Datas[0].bCanMove ? Status->SetMove() : Status->SetStop();
}

void ACDoAction_Warp::Begin_DoAction()
{
    FTransform transform = Datas[0].EffectTransform;

    UGameplayStatics::SpawnEmitterAttached(Datas[0].Effect, OwnerCharacter->GetMesh(), "", transform.GetLocation(), FRotator(transform.GetRotation()), transform.GetScale3D());

}

void ACDoAction_Warp::End_DoAction()
{
    OwnerCharacter->SetActorLocation(Location);
    Location = FVector::ZeroVector;

    State->SetIdleMode();
    Status->SetMove();
}

void ACDoAction_Warp::DoSecondAction()
{
    OnAim();
}

void ACDoAction_Warp::DoSecondActionRelease()
{
    OffAim();
}

void ACDoAction_Warp::OnAim()
{
    Aim->OnZoom();

}

void ACDoAction_Warp::OffAim()
{
    Aim->OffZoom();

}

void ACDoAction_Warp::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);


    CheckFalse(*bEquipped);
    Aim->Tick(DeltaTime);

    FVector location;
    FRotator rotator;



    if (GetCrursorLocationAndRotation(location, rotator))
    {
        Decal->SetVisibility(true);
        Decal->SetWorldLocation(location);
        Decal->SetWorldRotation(rotator);

        return;
    }

    Decal->SetVisibility(false);


}
bool ACDoAction_Warp::GetCrursorLocationAndRotation(FVector& OutLocation, FRotator& OutRotator)
{
    APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);

    TArray<TEnumAsByte<EObjectTypeQuery>> objects;
    objects.Add(EObjectTypeQuery::ObjectTypeQuery1);

    FHitResult hitResult;
    if (controller->GetHitResultUnderCursorForObjects(objects, false, hitResult))
    {
        OutLocation = hitResult.Location;
        OutRotator = hitResult.ImpactNormal.Rotation();

        return true;
    }
    return false;
}

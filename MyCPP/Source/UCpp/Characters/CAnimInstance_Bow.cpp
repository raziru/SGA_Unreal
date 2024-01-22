// Fill out your copyright notice in the Description page of Project Settings.


#include "CAnimInstance_Bow.h"
#include "Global.h"
#include "Actions/CAttachment.h"



void UCAnimInstance_Bow::NativeBeginPlay()
{
	Super::NativeBeginPlay();

}

void UCAnimInstance_Bow::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	ACAttachment* Attachment = Cast<ACAttachment>(GetOwningActor());
	CheckNull(Attachment);
	IsPulled = Attachment->GetIsPress();
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Action/CUserWidget_ActionButton.h"
#include "Global.h"
#include "CUserWidget_ActionList.h"
#include "Characters/CPlayer.h"

void UCUserWidget_ActionButton::Click()
{
	GetActionList()->Clicked(GetName());
} 
void UCUserWidget_ActionButton::Hover()
{
	GetActionList()->Hovered(GetName());

}

void UCUserWidget_ActionButton::Unhover()
{
	GetActionList()->Unhovered(GetName());

}

UCUserWidget_ActionList* UCUserWidget_ActionButton::GetActionList()
{
	ACPlayer* player = Cast<ACPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	return player->GetActionList();
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "CUserWidget_ActionList.h"
#include "Global.h"
#include "CUserWidget_ActionButton.h"
#include "Components/GridPanel.h"
#include "Components/Border.h"


void UCUserWidget_ActionList::NativeConstruct()
{
    UGridPanel* gridPanel = Cast<UGridPanel>(GetWidgetFromName("Grid"));
    TArray<UWidget*> widgets = gridPanel->GetAllChildren();//�ڽ�Ŭ������ ���������� ��ü�� ���Ұ�

    for (UWidget* widget : widgets)
    {
        FUserWidget_Action_Data data;
        data.Item = Cast<UCUserWidget_ActionButton>(widget);

        Datas.Add(data);
    }

    Super::NativeConstruct();
}

void UCUserWidget_ActionList::Clicked(FString InName)
{

    for (const FUserWidget_Action_Data& data : Datas)
    {
        if (data.Item->GetName() == InName)
        {
            if (data.OnUserWidget_ActionItem_Clicked.IsBound())
                data.OnUserWidget_ActionItem_Clicked.Broadcast();

            SetVisibility(ESlateVisibility::Hidden);

            UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = false;
            UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeGameOnly());
            UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0f);

            break;
        }
    }
}

void UCUserWidget_ActionList::Hovered(FString InName)
{
    for (const FUserWidget_Action_Data& data : Datas)
    {
        UBorder* border = Cast<UBorder>(data.Item->GetWidgetFromName("BG_Border"));

        if (data.Item->GetName() == InName)
        {
            border->SetBrushColor(FLinearColor::Red);

            break;
        }
    }
}

void UCUserWidget_ActionList::Unhovered(FString InName)
{
    for (const FUserWidget_Action_Data& data : Datas)
    {
        UBorder* border = Cast<UBorder>(data.Item->GetWidgetFromName("BG_Border"));

        if (data.Item->GetName() == InName)
        {
            border->SetBrushColor(FLinearColor::White);

            break;
        }
    }
}


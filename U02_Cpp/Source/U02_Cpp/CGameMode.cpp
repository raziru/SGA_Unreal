// Copyright Epic Games, Inc. All Rights Reserved.


#include "CGameMode.h"
#include "Global.h"

ACGameMode::ACGameMode()
{
	//ConstructorHelpers::FClassFinder<APawn> pawn(
	//	L"Blueprint'/Game/Player/BP_CPlayer.BP_CPlayer_C'");//C�� ������ �������Ʈ�� _C�� �پ��־�� �Ѵ�.
	//if (pawn.Succeeded())
	//{
	//	pawn.Class
	//}

	CHelpers::GetClass <APawn> (&DefaultPawnClass, "Blueprint'/Game/Player/BP_CPlayer.BP_CPlayer_C'");

}

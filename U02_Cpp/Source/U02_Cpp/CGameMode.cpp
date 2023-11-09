// Copyright Epic Games, Inc. All Rights Reserved.


#include "CGameMode.h"
#include "Global.h"

ACGameMode::ACGameMode()
{
	//ConstructorHelpers::FClassFinder<APawn> pawn(
	//	L"Blueprint'/Game/Player/BP_CPlayer.BP_CPlayer_C'");//C로 생성된 블루프린트는 _C가 붙어있어야 한다.
	//if (pawn.Succeeded())
	//{
	//	pawn.Class
	//}

	CHelpers::GetClass <APawn> (&DefaultPawnClass, "Blueprint'/Game/Player/BP_CPlayer.BP_CPlayer_C'");

}

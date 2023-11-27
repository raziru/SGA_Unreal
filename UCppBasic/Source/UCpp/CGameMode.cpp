// Copyright Epic Games, Inc. All Rights Reserved.


#include "CGameMode.h"
#include "Global.h"

ACGameMode::ACGameMode()
{
	//constructorhelpers::fclassfinder<apawn> pawn(
	//	l"blueprint'/game/player/bp_c_player.bp_c_player_c'");//c로 생성된 블루프린트는 _c가 붙어있어야 한다.
	//if (pawn.succeeded())
	//{
	//	pawn.class
	//}

	CHelpers::GetClass <APawn>(&DefaultPawnClass, "Blueprint'/Game/Player/BP_Player.BP_Player_C'");
}

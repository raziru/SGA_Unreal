// Copyright Epic Games, Inc. All Rights Reserved.


#include "CGameMode.h"
#include "Global.h"

ACGameMode::ACGameMode()
{
	//constructorhelpers::fclassfinder<apawn> pawn(
	//	l"blueprint'/game/player/bp_c_player.bp_c_player_c'");//c�� ������ �������Ʈ�� _c�� �پ��־�� �Ѵ�.
	//if (pawn.succeeded())
	//{
	//	pawn.class
	//}

	CHelpers::GetClass <APawn>(&DefaultPawnClass, "Blueprint'/Game/Player/BP_Player.BP_Player_C'");
}

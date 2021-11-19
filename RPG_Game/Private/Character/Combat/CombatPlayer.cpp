// Fill out your copyright notice in the Description page of Project Settings.


#include "../../../Public/Character/Combat/CombatPlayer.h"

void ACombatPlayer::InputPlayerStatus(URPGGameInstance* GameInstance, int32 Index)
{
	if (Index == -1)
	{
		CharacterStatus = GameInstance->MainMapPCStautus;
	}
	else
	{
		CharacterStatus = GameInstance->SubPlayerStatus[Index];
	}
}

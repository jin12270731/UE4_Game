// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Public/Library/DetailFunction.h"
#include "../../RPG_GameLoadingScreen/Public/RPG_GameLoadingScreen.h"

void UDetailFunction::PlayLoadingScreen(bool bPlayUntilStopped, float PlayTime)
{
	IActionRPGLoadingScreenModule& LoadingScreenModule = IActionRPGLoadingScreenModule::Get();
	LoadingScreenModule.StartInGameLoadingScreen(bPlayUntilStopped, PlayTime);
}

void UDetailFunction::StopLoadingScreen()
{
	IActionRPGLoadingScreenModule& LoadingScreenModule = IActionRPGLoadingScreenModule::Get();
	LoadingScreenModule.StopInGameLoadingScreen();
}

TMap<ACombatCharacterBase*, int32> UDetailFunction::DesideTurn(TMap<ACombatCharacterBase*, int32> Maps)
{
	Maps.ValueSort([](const int32& A, const int32& B){
		return A > B;
	});
	return Maps;
}

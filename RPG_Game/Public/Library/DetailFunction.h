// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "./Character/Combat/CombatCharacterBase.h"
#include "DetailFunction.generated.h"

/**
 * 
 */
UCLASS()
class UDetailFunction : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	UFUNCTION(BlueprintCallable, Category = Loading)
		static void PlayLoadingScreen(bool bPlayUntilStopped, float PlayTime);

	UFUNCTION(BlueprintCallable, Category = Loading)
		static void StopLoadingScreen();
	UFUNCTION(BlueprintCallable)
		static TMap<ACombatCharacterBase*, int32> DesideTurn(TMap<ACombatCharacterBase*, int32> Maps);
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Character/Combat/CombatCharacterBase.h"
#include "../RPGGameInstance.h"
#include "Character/Combat/CombatEnemy.h"
#include "Character/MainMap/CharacterBase.h"
#include "EnemyFunction.generated.h"

/**
 *
 */
UCLASS()
class RPG_GAME_API UEnemyFunction : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
		static FCharacterBaseStatus GetEnemyStatus(int32 Index, int32 Level, const FEnemyStatusData EnemyData, const FEnemyUpCoefficient EnemyUpData,
			const EGrowRate GrowRate, const TArray<FItemStruct> MaterialItemStruct, const TArray<int32> MaterialNumber);
	UFUNCTION(BlueprintCallable)
		static int32 GetEnemyLevel(int32 Max, int32 Min);
	static float GetAddStatus(float Base, int32 Level, float Coefficient);
};



// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/MainMap/CharacterBase.h"
#include "MainMapEnemyBase.generated.h"

/**
 * 
 */
UCLASS()
class AMainMapEnemyBase : public ACharacterBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true))
		int32 TearOffMaxHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true))
		int32 TearOffNowHP;
};

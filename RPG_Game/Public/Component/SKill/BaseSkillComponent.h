// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/BaseMainMapPlayerComponent.h"
#include "../../RPGGameInstance.h"
#include "BaseSkillComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class RPG_GAME_API UBaseSkillComponent : public UBaseMainMapPlayerComponent
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
		URPGGameInstance* Instance;
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveData.h"
#include "SettingSave.generated.h"

/**
 * 
 */
UCLASS()
class USettingSave : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY()
		FString SlotName;
	
	USettingSave();
};

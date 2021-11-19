// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "../RPGGameInstance.h"
#include "SaveBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class USaveBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
		static void MainSaveData(FString saveName, URPGGameInstance* gameInstance, FTransform playerTransform);
	void SettingSaveDaya(FString settingSaveName);

};

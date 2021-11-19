// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Dom/JsonObject.h"
#include "../Character/MainMap/MainMapPC.h"
#include "JsonLibrary.generated.h"

typedef TSharedPtr<FJsonObject> JsonObjectPtr;

/**
 * 
 */
UCLASS()
class RPG_GAME_API UJsonLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Json")
		static bool WriteGameinstanceToJsonFile(const URPGGameInstance* GameIns);
	UFUNCTION(BlueprintCallable, Category = "Json")
		static bool JsonFileToWriteGameinstance(URPGGameInstance* GameIns);
	UFUNCTION(BlueprintCallable, Category = "Json")
		static bool GetJsonFileData(FString& GetString, TArray<FString> SarchStrings);
	UFUNCTION(BlueprintCallable, Category = "Json")
		static bool WriteJsonFile(FString WriteString, TArray<FString> WriteStrings, bool isCoin = false);
};

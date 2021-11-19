// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "./Character/MainMap/MainMapPC.h"
#include "./Character/MainMap/MainMapNPC.h"
#include "SaveData.generated.h"


USTRUCT(BlueprintType)
struct FTimerStruct {
	GENERATED_BODY()
public:
	UPROPERTY(EditanyWhere, BlueprintReadOnly)
		int32 MyDays;
	UPROPERTY(EditanyWhere, BlueprintReadOnly)
		int32 MyHours;
	UPROPERTY(EditanyWhere, BlueprintReadOnly)
		float MyMinute;
	UPROPERTY(EditanyWhere, BlueprintReadOnly)
		FString WorldCalendar;
	UPROPERTY(EditanyWhere, BlueprintReadOnly)
		int32 WorldYear;
	UPROPERTY(EditanyWhere, BlueprintReadOnly)
		int32 WorldMonth;
	UPROPERTY(EditanyWhere, BlueprintReadOnly)
		int32 WorldDays;
	UPROPERTY(EditanyWhere, BlueprintReadOnly)
		int32 WorldHours;
	UPROPERTY(EditanyWhere, BlueprintReadOnly)
		float WorldMinute;

};
/**
 * 
 */
UCLASS()
class USaveData : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FMainMapPCStautus SaveMainMapPCStautus;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TArray<FMainMapNPCStautus> SaveSubNPCStautus;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FTimerStruct TimerStruct;
	USaveData();
};
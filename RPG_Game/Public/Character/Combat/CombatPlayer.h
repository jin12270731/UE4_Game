// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Combat/CombatCharacterBase.h"
#include "RPGGameInstance.h"
#include "CombatPlayer.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FPlayerUpCoefficient : public FTableRowBase {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float UpHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float UpSP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float UpMP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float UpNormalAttack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float UpMagicAttack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float UpNormalDefense;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float UpMagicDefense;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float UpSpeed;
};

USTRUCT(BlueprintType)
struct FNeedExperience : public FTableRowBase {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float BaseExperience; 
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float EscapeExperience; 
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<float> ToLevel;
};


USTRUCT(BlueprintType)
struct FDifficultyStatusUp : public FTableRowBase {
	GENERATED_BODY()
public:
	UPROPERTY()
		float ExpCoefficenet;
};

UCLASS()
class ACombatPlayer : public ACombatCharacterBase
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
		void InputPlayerStatus(URPGGameInstance* GameInstance, int32 Index);
};

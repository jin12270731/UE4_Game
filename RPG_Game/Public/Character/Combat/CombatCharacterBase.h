// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/MainMap/CharacterBase.h"
#include "CombatCharacterBase.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class ECommandType : uint8 {
	None,
	NormalAttack,
	Magic,
	Skill,
	Item,
	Escape,
	Damage,
	Died
};


UCLASS()
class ACombatCharacterBase : public ACharacterBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
		TArray<ACombatCharacterBase*> TargetCharacter;
	UPROPERTY(BlueprintReadWrite)
		FString CommandType;
	UPROPERTY(BlueprintReadWrite)
		FString CommandName;
	UPROPERTY(BlueprintReadWrite)
		ECommandType Command;
	UPROPERTY(BlueprintReadWrite)
		FCharacterBaseStatus CharacterStatus;
	UFUNCTION(BlueprintCallable)
		void SendAnimation(UAnimMontage* DamegeAnim, float Rate);
};
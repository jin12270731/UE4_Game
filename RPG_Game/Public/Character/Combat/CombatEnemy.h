// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Combat/CombatCharacterBase.h"
#include "RPGGameInstance.h"
#include "CombatEnemy.generated.h"

USTRUCT(BlueprintType)
struct FEnemyMaterial
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName ItemKind;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 ItemNumber;
};

USTRUCT(BlueprintType)
struct FEnemyStatusData : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString EnemyName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EGrowthTypeEnum EnemyType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 EnemyHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 EnemySP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 EnemyMP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 EnemyNomalAttack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 EnemyMagicAttack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 EnemyNomalDefense;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 EnemyMagicDefense;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 EnemySpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 EnemyExperience;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MinRespornNumber;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MaxRepornNumber;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float EnemyWalkSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float EnemyRunSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float EnemySarchSphere;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float EnemySarchForward;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float EnemyCritical;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float EnemyCriticalCoefficient;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FEnemyMaterial> EnemyMaterial;
};

USTRUCT(BlueprintType)
struct FEnemyUpCoefficient : public FTableRowBase {
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float UpExperience;
};


/**
 * 
 */
UCLASS(Blueprintable)
class ACombatEnemy : public ACombatCharacterBase
{
	GENERATED_BODY()
public:
};

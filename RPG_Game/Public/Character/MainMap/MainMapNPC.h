// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "MainMapNPC.generated.h"


USTRUCT(BlueprintType)
struct FMainMapNPCStautus : public FCharacterBaseStatus {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int32 TitoPoint;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		TArray<ETitoList> HaveTito;
	FMainMapNPCStautus() : TitoPoint(0) {};
};
/**
 * 
 */
UCLASS()
class AMainMapNPC : public ACharacterBase
{
	GENERATED_BODY()
	
};

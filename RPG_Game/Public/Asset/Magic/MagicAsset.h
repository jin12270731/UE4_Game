// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MagicAsset.generated.h"

/**
 * 
 */
UCLASS()
class RPG_GAME_API UMagicAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UMagicAsset() : name(TEXT("test")) {};
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString name;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TSubclassOf<AActor> MagicActor;

	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
};

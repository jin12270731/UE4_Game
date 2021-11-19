// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "../Public/Character/MainMap/MainMapEnemyBase.h"
#include "../Public/Character/MainMap/CharacterBase.h"
#include "MainSpawnManegerComponent.generated.h"


USTRUCT(BlueprintType)
struct FSpawnEnemyData: public FTableRowBase {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int32 ID;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int32 X1;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int32 Y1;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int32 X2;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int32 Y2;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		TArray<FString> Enemys;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		TArray <float> EnemyProbability;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int32 MaxNum;
};

USTRUCT(BlueprintType)
struct FEnemySpawnPoint
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
		FVector2D SpawnPoint;
	UPROPERTY(BlueprintReadOnly)
		int32 Distance;
	UPROPERTY(BlueprintReadWrite)
		int32 Level;
	UPROPERTY(BlueprintReadWrite)
		FName EnemyTag;
	UPROPERTY(BlueprintReadWrite)
		bool isStatus;
	UPROPERTY(BlueprintReadWrite)
		int32 EnemyID;
	UPROPERTY(BlueprintReadWrite)
		EGrowRate GrowRate;
	UPROPERTY(BlueprintReadWrite)
		bool isDead;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int32 TearOffNowHP;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int32 TearOffMaxHP;
	UPROPERTY(BlueprintReadWrite)
		AMainMapEnemyBase* SpawnEnemy;
	FEnemySpawnPoint();
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), Blueprintable)
class UMainSpawnManegerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMainSpawnManegerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY(BlueprintReadWrite)
		TArray<FEnemySpawnPoint> EnemySpawnArray;
	UFUNCTION(BlueprintCallable)
		int GetArrayNum();
	UFUNCTION(BlueprintCallable)
		void CreateSpawnEnemyPoint(TArray<FSpawnEnemyData> SpawnEnemyData);
	UFUNCTION(BlueprintCallable)
		void CheckPlayerDistance(FVector2D PlayerPoint);
	UFUNCTION(BlueprintCallable)
		void SortDistance();
	TTuple<int32, EGrowRate> GetEnemyBaseLevel();
};
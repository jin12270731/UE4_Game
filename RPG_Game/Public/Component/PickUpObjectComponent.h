// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Other/MainMapObject.h"
#include "PickUpObjectComponent.generated.h"


USTRUCT(BlueprintType)
struct FMainMapObjectPoint
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
		FTransform SpawnPoint;
	UPROPERTY(BlueprintReadOnly)
		int32 Distance;
	UPROPERTY(BlueprintReadWrite)
		int32 ObjectID;
	UPROPERTY(BlueprintReadWrite)
		int32 EnemyID;
	UPROPERTY(BlueprintReadWrite)
		FString ObjectKey;
	UPROPERTY(BlueprintReadWrite)
		AMainMapObject* Object;
	FMainMapObjectPoint() : SpawnPoint(FTransform(FQuat(0.f, 0.f, 0.f, 0.f), FVector(0.0f, 0.0f, 0.0f), FVector(0.0f, 0.0f, 0.0f))), Distance(-1), ObjectID(0), Object(nullptr) {}
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class RPG_GAME_API UPickUpObjectComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPickUpObjectComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintReadWrite)
		TArray<FMainMapObjectPoint> MainMapObjectPoint;
	UFUNCTION(BlueprintCallable)
		void CheckPlayerDistance(FVector2D PlayerPoint);
	UFUNCTION(BlueprintCallable)
		void SortDistance();
};
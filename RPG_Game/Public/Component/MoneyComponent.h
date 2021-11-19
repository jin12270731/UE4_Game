// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RPGGameInstance.h"
#include "./Character/MainMap/MainMapPC.h"
#include "MoneyComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class RPG_GAME_API UMoneyComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMoneyComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable)
		void AddMoney(AMainMapPC* Status, int32 BronzeCoin);
	UFUNCTION(BlueprintCallable)
		void SubMoney(AMainMapPC* Status, int32 BronzeCoin);
	UFUNCTION(BlueprintCallable)
		bool CheckMoney(AMainMapPC* Status, int32 BronzeCoin);
		
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RPGGameInstance.h"
#include "TimerCountComponent.generated.h"




UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UTimerCountComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTimerCountComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	/*UPROPERTY(BlueprintReadOnly, EditanyWhere)
		FTimerStruct TimerStruct;*/
	UFUNCTION(BlueprintCallable)
		void AddTimer(int32 min);
private:
	void TimerCount(float delta);
};

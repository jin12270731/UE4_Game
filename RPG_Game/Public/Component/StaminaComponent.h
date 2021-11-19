// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Pawn.h"
#include "TimerManager.h"
#include "Engine.h"
#include "GenericPlatform/GenericPlatformMath.h"
#include "StaminaComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UStaminaComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStaminaComponent();
	UPROPERTY(BlueprintReadOnly)
		float NowStamina;
	UPROPERTY(BlueprintReadOnly)
		float MaxStamina;
	UPROPERTY(BlueprintReadOnly)
		float DamegeStaminaCoff;
	UPROPERTY(BlueprintReadOnly)
		float RecoveryStaminaCoff;
	UFUNCTION(BlueprintCallable)
		void ChangeStamina();
	UFUNCTION()
		void DamegeStamina();
	UFUNCTION()
		void RecoveryStamina();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	FTimerHandle timerHandle;
	FTimerHandle timerHandle2;
	bool Flag, Flag2;
	float BuffSpeed;
	float NowSpeed;
};

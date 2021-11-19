// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Public/Component/StaminaComponent.h"

// Sets default values for this component's properties
UStaminaComponent::UStaminaComponent() : Flag(false), Flag2(false)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


void UStaminaComponent::ChangeStamina()
{
	FVector velocity = GetOwner()->GetVelocity();
	float len = velocity.Size();
	NowSpeed = len;
	FTimerManager& TimerManager = GetOwner()->GetWorldTimerManager();
	if (FGenericPlatformMath::Abs(NowSpeed - BuffSpeed) > 50.0f) {
		Flag = false;
		BuffSpeed = len;
	}
	if (len >= 800 && Flag == false)
	{
		TimerManager.SetTimer(timerHandle, this, &UStaminaComponent::DamegeStamina, 0.01f, true);
		Flag = true;
		BuffSpeed = len;
		TimerManager.SetTimer(timerHandle2, this, &UStaminaComponent::RecoveryStamina, 0.0f, false);
		Flag2 = false;
	}
	else if (len < 800 && Flag == false)
	{
		TimerManager.SetTimer(timerHandle, this, &UStaminaComponent::DamegeStamina, 0.0f, false);
		Flag = true;
		BuffSpeed = len;
		if (NowStamina < MaxStamina && Flag2 == false) {
			TimerManager.SetTimer(timerHandle2, this, &UStaminaComponent::RecoveryStamina, 0.01f, true);
			Flag2 = true;
		}
	}
	
}

void UStaminaComponent::DamegeStamina()
{
	NowStamina -= DamegeStaminaCoff;
	if (NowStamina < 0) {
		NowStamina = 0;
	}
}

void UStaminaComponent::RecoveryStamina()
{
	FTimerManager& TimerManager = GetOwner()->GetWorldTimerManager();
	NowStamina += RecoveryStaminaCoff;
	if (NowStamina >= MaxStamina) {
		Flag2 = false;
		NowStamina = MaxStamina;
		TimerManager.SetTimer(timerHandle2, this, &UStaminaComponent::RecoveryStamina, 0.0f, false);
	}
}

// Called when the game starts
void UStaminaComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...
	NowStamina = 10.0f;
	MaxStamina = 10.0f;
	DamegeStaminaCoff = 0.01;
	RecoveryStaminaCoff = 0.01;
}


// Called every frame
void UStaminaComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
	ChangeStamina();
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::SanitizeFloat(NowStamina));
}


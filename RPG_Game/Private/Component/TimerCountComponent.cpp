// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Public/Component/TimerCountComponent.h"

// Sets default values for this component's properties
UTimerCountComponent::UTimerCountComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UTimerCountComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...
	
	
}


// Called every frame
void UTimerCountComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
	TimerCount(DeltaTime);
}

void UTimerCountComponent::AddTimer(int32 min)
{
	if (Cast<URPGGameInstance>(GetOwner()->GetGameInstance())) {
		FTimerStruct& timer = Cast<URPGGameInstance>(GetOwner()->GetGameInstance())->TimerStruct;
		timer.MyMinute += min;
		timer.WorldMinute += min;
		//MyTime
		int32 amari = timer.MyMinute / 60;
		if (amari > 0) {
			timer.MyMinute = timer.MyMinute - amari * 60.0f;
			timer.MyHours += amari;
		}
		amari = timer.MyHours / 24;
		if (amari > 0) {
			timer.MyHours = timer.MyHours - amari * 24;
			timer.MyDays += amari;
		}
		//WorldTime
		amari = timer.WorldMinute / 60;
		if (amari > 0) {
			timer.WorldMinute = timer.WorldMinute - amari * 60.0f;
			timer.WorldHours += amari;
		}
		amari = timer.WorldHours / 24;
		if (amari > 0) {
			timer.WorldHours = timer.WorldHours - amari * 24;
			timer.WorldDays += amari;
		}
		amari = timer.WorldDays / 20;
		if (amari > 0) {
			timer.WorldDays = timer.WorldDays - amari * 20;
			timer.WorldMonth += amari;
		}
		amari = timer.WorldMonth / 4;
		if (amari > 0) {
			timer.WorldMonth = timer.WorldMonth - amari * 4;
			timer.WorldYear += amari;
		}
	}
}

void UTimerCountComponent::TimerCount(float delta)
{
	if (Cast<URPGGameInstance>(GetOwner()->GetGameInstance())) {
		FTimerStruct& timer = Cast<URPGGameInstance>(GetOwner()->GetGameInstance())->TimerStruct;
		timer.MyMinute += delta;
		timer.WorldMinute += delta;
		//MyTime
		if (timer.MyMinute >= 60) {
			timer.MyMinute = 0.0f;
			timer.MyHours += 1;
		}
		if (timer.MyHours >= 24) {
			timer.MyHours = 0;
			timer.MyDays += 1;
		}
		//WorldTime
		if (timer.WorldMinute >= 60) {
			timer.WorldMinute = 0.0f;
			timer.WorldHours += 1;
		}
		if (timer.WorldHours >= 24) {
			timer.WorldHours = 0;
			timer.WorldDays += 1;
		}
		if (timer.WorldDays > 20) {
			timer.WorldDays = 1;
			timer.WorldMonth += 1;
		}
		if (timer.WorldMonth > 4) {
			timer.WorldMonth = 1;
			timer.WorldYear += 1;
		}
	}
}

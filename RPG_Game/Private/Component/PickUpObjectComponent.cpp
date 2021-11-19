// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/PickUpObjectComponent.h"

// Sets default values for this component's properties
UPickUpObjectComponent::UPickUpObjectComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPickUpObjectComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPickUpObjectComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPickUpObjectComponent::CheckPlayerDistance(FVector2D PlayerPoint)
{
	for (auto& Array : MainMapObjectPoint)
	{
		int32 x = FMath::Abs(PlayerPoint.X - Array.SpawnPoint.GetLocation().X);
		int32 y = FMath::Abs(PlayerPoint.Y - Array.SpawnPoint.GetLocation().Y);
		Array.Distance = x + y;
	}
}

void UPickUpObjectComponent::SortDistance()
{
	MainMapObjectPoint.Sort([](const FMainMapObjectPoint& A, const FMainMapObjectPoint& B) 
	{
		return A.Distance < B.Distance;
	});
}


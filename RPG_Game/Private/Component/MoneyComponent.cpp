// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/MoneyComponent.h"

// Sets default values for this component's properties
UMoneyComponent::UMoneyComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMoneyComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UMoneyComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMoneyComponent::AddMoney(AMainMapPC* Status, int32 BronzeCoin)
{
}

void UMoneyComponent::SubMoney(AMainMapPC* Status, int32 BronzeCoin)
{
	FMainMapPCStautus& stautus = Status->MainMapPCStautus;
	//現在、所有している硬貨をすべて、銅貨に変換する
	int32 havegold = stautus.PCoins * 10;
	havegold += stautus.GCoins;
	int32 havesirver = havegold * 10;
	havesirver += stautus.SCoins;
	int32 havebronze = havesirver * 10;
	havebronze += stautus.BCoins;
	//所有している銅貨をひく
	int32 bronze = havebronze - BronzeCoin;
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Black, FString::FromInt(bronze));
	if (bronze < 0)
		return;
	int32 sirver = bronze / 10;
	bronze -= (sirver * 10);
	int32 gold = sirver / 10;
	sirver -= gold * 10;
	int32 platinum = gold / 10;
	gold -= platinum * 10;
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::FromInt(sirver));
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::FromInt(gold));
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::FromInt(bronze));
	stautus.BCoins = bronze;
	stautus.SCoins = sirver;
	stautus.GCoins = gold;
	stautus.PCoins = platinum;
}

bool UMoneyComponent::CheckMoney(AMainMapPC* Status, int32 BronzeCoin)
{
	//if (Cast<URPGGameInstance>(GetOwner()->GetGameInstance()))
	//const FMainMapPCStautus& stautus = Cast<URPGGameInstance>(GetOwner()->GetGameInstance())->MainMapPCStautus;
	const FMainMapPCStautus& stautus = Status->MainMapPCStautus;
	int32 gold = stautus.PCoins * 10;
	gold += stautus.GCoins;
	int32 sirver = gold * 10;
	sirver += stautus.SCoins;
	int32 bronze = sirver * 10;
	bronze += stautus.BCoins;
	if (bronze >= BronzeCoin)
	{
		return true;
	}
	return false;
}


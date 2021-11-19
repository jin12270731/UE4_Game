// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Public/Component/MainSpawnManegerComponent.h"

// Sets default values for this component's properties
UMainSpawnManegerComponent::UMainSpawnManegerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UMainSpawnManegerComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...
	
}


// Called every frame
void UMainSpawnManegerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

int UMainSpawnManegerComponent::GetArrayNum()
{
	return EnemySpawnArray.Num();
}


void UMainSpawnManegerComponent::CreateSpawnEnemyPoint(TArray<FSpawnEnemyData> SpawnEnemyData)
{
	/*if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("test"));*/
	//Need Spawn data
	TArray<FSpawnEnemyData> LocalSpawnEnemyData;
	//Not Need Spawn data
	TArray<FSpawnEnemyData> LocalNotSpawnEnemyData;
	for(const auto EnemyData : SpawnEnemyData)
	{
		if (EnemyData.MaxNum > 0)
		{
			LocalSpawnEnemyData.Add(EnemyData);
		}
		else
		{
			LocalNotSpawnEnemyData.Add(EnemyData);
		}
	}
	/*if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::FromInt(LocalSpawnEnemyData.Num()));
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::FromInt(LocalNotSpawnEnemyData.Num()));*/
	int Index = 0;
	for (int i = 0; i < 500; i++) 
	{
		if (LocalSpawnEnemyData.Num() - 1 < Index)
			break;
		if (LocalSpawnEnemyData[Index].MaxNum > EnemySpawnArray.Num())
		{
			//set basic data
			FEnemySpawnPoint result;
			TTuple<int32, EGrowRate> tuple = GetEnemyBaseLevel();
			result.Level = tuple.Get<int32>();
			result.GrowRate = tuple.Get<EGrowRate>();
			result.EnemyID = i;
			result.isStatus = false;
			result.Distance = -1;

			//set enemy name
			int j = 0;
			for (j = 0; j < LocalSpawnEnemyData[Index].EnemyProbability.Num(); j++)
			{
				if (UKismetMathLibrary::RandomBoolWithWeight(LocalSpawnEnemyData[Index].EnemyProbability[j]))
				{
					result.EnemyTag = FName(*LocalSpawnEnemyData[Index].Enemys[j]);
					break;
				}
			}
			if(j >= LocalSpawnEnemyData[Index].EnemyProbability.Num())
				result.EnemyTag = FName(*LocalSpawnEnemyData[Index].Enemys[j - 1]);

			//set spawn point
			FVector2D spawnPoint;
			//serch spawn point.
			bool flag = true;//found a spawn point
			while (flag)
			{
				//get spawn point. random value
				spawnPoint.X = FMath::RandRange(LocalSpawnEnemyData[Index].X1, LocalSpawnEnemyData[Index].X2);
				spawnPoint.Y = FMath::RandRange(LocalSpawnEnemyData[Index].Y1, LocalSpawnEnemyData[Index].Y2);
				//Can you spawn?
				for (const auto notSpawn : LocalNotSpawnEnemyData)
				{
					//If it is within the range.
					if (spawnPoint.X >= notSpawn.X1 && spawnPoint.X <= notSpawn.X2)
						flag = true;//Not found a spawn point.Continue for loop and while loop.
					else if (spawnPoint.Y >= notSpawn.Y1 && spawnPoint.Y <= notSpawn.Y2)
						flag = true;//Not found a spawn point.Continue for loop and while loop.
					else
					{
						flag = false;
						break;//Found a spawn point.Exit for loop and while loop.
					}
				}
			}
			result.SpawnPoint.Set(spawnPoint.X, spawnPoint.Y);
			EnemySpawnArray.Add(result);
		} else Index++;
	}
}

void UMainSpawnManegerComponent::CheckPlayerDistance(FVector2D PlayerPoint)
{
	for (auto& Array : EnemySpawnArray)
	{
		int32 x = FMath::Abs(PlayerPoint.X - Array.SpawnPoint.X);
		int32 y = FMath::Abs(PlayerPoint.Y - Array.SpawnPoint.Y);
		Array.Distance = x + y;
	}
}

void UMainSpawnManegerComponent::SortDistance()
{
	EnemySpawnArray.Sort([](const FEnemySpawnPoint& A, const FEnemySpawnPoint& B) {
		return A.Distance < B.Distance;
	});
}

TTuple<int32, EGrowRate> UMainSpawnManegerComponent::GetEnemyBaseLevel()
{
	if (UKismetMathLibrary::RandomBoolWithWeight(.3f))
		return TTuple<int32, EGrowRate>(FMath::RandRange(1, 19), EGrowRate::Child);
	else if (UKismetMathLibrary::RandomBoolWithWeight(.7f))
	{
		if (UKismetMathLibrary::RandomBoolWithWeight(.7f))
			return TTuple<int32, EGrowRate>(FMath::RandRange(20, 39), EGrowRate::Adult);
		else
			return TTuple<int32, EGrowRate>(FMath::RandRange(20, 39), EGrowRate::Old);
	}
	else {
		if (UKismetMathLibrary::RandomBoolWithWeight(.7f))
			return TTuple<int32, EGrowRate>(FMath::RandRange(40, 100), EGrowRate::Adult);
		else
			return TTuple<int32, EGrowRate>(FMath::RandRange(40, 100), EGrowRate::Old);
	}
}

FEnemySpawnPoint::FEnemySpawnPoint()
{
	this->Distance = -1;
	this->EnemyTag = TEXT("None");
	this->Level = 1;
	this->isStatus = false;
	this->SpawnPoint = FVector2D(0.f, 0.f);
	this->SpawnEnemy = nullptr;
	this->isDead = false;
	this->GrowRate = EGrowRate::Parent;
	this->TearOffNowHP = 0;
	this->TearOffMaxHP = 0;
}

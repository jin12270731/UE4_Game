// Fill out your copyright notice in the Description page of Project Settings.


#include "../../../Public/Character/MainMap/CharacterBase.h"

// Sets default values
ACharacterBase::ACharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

bool ACharacterBase::RemoveItem(FString Key, int32 Index)
{
	return false;
}

bool ACharacterBase::RemoveClothes(FString Key, int32 Index)
{
	return false;
}

FClothesStruct ACharacterBase::SetRightOrLeft(FString Key, int32 Index, ERightOrLeft RightOrLeft, EFingerKinds FingerKinds)
{
	return FClothesStruct();
}



FCharacterBaseStatus::FCharacterBaseStatus()
{
	CharacterName = TEXT("NoName");
	Level = 1;
	NowHP = 1;
	MaxHP = NowHP;
	NowSP = 1;
	MaxSP = NowSP;
	NowMP = 1;
	MaxMP = NowMP;
	NormalAttack = 1;
	MagicAttack = 1;
	NormalDefense = 1;
	MagicDefense = 1;
	Speed = 1;
	Critical = 0.0f;
	CriticalCoefficient = 1.0f;
	TotalExperience = 0.0f;
	RemainderExperience = 0.0f;
	DieFlag = false;
	Gender = EGenderEnum::Man;
	GrowRate = EGrowRate::Parent;
	GrowthType = EGrowthTypeEnum::Balance;
}

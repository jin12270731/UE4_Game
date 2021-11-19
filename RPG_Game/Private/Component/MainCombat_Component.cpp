// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Public/Component/MainCombat_Component.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UMainCombat_Component::UMainCombat_Component()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PlayerDistance = 200;
	EnemyDistance = 200;
	// ...
}


// Called when the game starts
void UMainCombat_Component::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMainCombat_Component::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

FTransform UMainCombat_Component::GetSpawnTransform(int32 Index, FVector PlayerSenter, FRotator Rotator)
{
	if (Index == 0)
	{
		return FTransform(Rotator, PlayerSenter, FVector(1.0f));
	}
	else
	{
		Index--;
		if (Index % 2 == 0)
		{
			FVector spawnVector = PlayerSenter;
			spawnVector.Y += PlayerDistance * (Index / 2 + 1);
			return FTransform(Rotator, spawnVector, FVector(1.0f));
		}
		else
		{
			FVector spawnVector = PlayerSenter;
			spawnVector.Y += -PlayerDistance * (Index / 2 + 1);
			return FTransform(Rotator, spawnVector, FVector(1.0f));
		}
	}
}

void UMainCombat_Component::ChangeStatusNormalAttack(ACombatCharacterBase* PlayingCharacter)
{
	
	for (auto Target : PlayingCharacter->TargetCharacter)
	{
		float Damage;
		//クリティカル!!
		if (UKismetMathLibrary::RandomBoolWithWeight(PlayingCharacter->CharacterStatus.Critical / 100.0f))
		{
			Damage = PlayingCharacter->CharacterStatus.NormalAttack * PlayingCharacter->CharacterStatus.CriticalCoefficient - Target->CharacterStatus.NormalDefense;
		}
		else//NOTクリティカル!!
		{
			Damage = PlayingCharacter->CharacterStatus.NormalAttack - Target->CharacterStatus.NormalDefense;
		}
		if (Damage < 0)
		{
			Damage = 0;
		}
		Target->CharacterStatus.NowHP -= UKismetMathLibrary::Round(Damage);
		CheckHP(Target);
	}
}

void UMainCombat_Component::ChangeStatusSkill(ACombatCharacterBase* PlayingCharacter, FSkillStatus SkillStatus)
{
	PlayingCharacter->CharacterStatus.NowSP -= SkillStatus.CostSP;
	switch (SkillStatus.Target)
	{
		case ETargetType::Both:
			break;
		case ETargetType::Enemy:
			break;
		case ETargetType::Friend:
			break;
		case ETargetType::Self:
			break;
	}
}

void UMainCombat_Component::ChangeStatusMagic(ACombatCharacterBase* PlayingCharacter, FMagicStatus MagicStatus)
{
	PlayingCharacter->CharacterStatus.NowMP -= MagicStatus.CostMP;
	for (auto Target : PlayingCharacter->TargetCharacter)
	{
		switch (MagicStatus.Target)
		{
		case ETargetType::Both:
			break;
		case ETargetType::Enemy:
			if (PlayingCharacter->CharacterStatus.NowMP >= 0)
			{
				float Damage;
				//クリティカル!!
				if (UKismetMathLibrary::RandomBoolWithWeight(PlayingCharacter->CharacterStatus.Critical / 100.0f))
				{
					Damage = (PlayingCharacter->CharacterStatus.MagicAttack + MagicStatus.BaseAttack) * PlayingCharacter->CharacterStatus.CriticalCoefficient - Target->CharacterStatus.MagicDefense;
				}
				else//NOTクリティカル!!
				{
					Damage = (PlayingCharacter->CharacterStatus.MagicAttack + MagicStatus.BaseAttack) - Target->CharacterStatus.MagicDefense;
				}
				if (Damage < 0)
				{
					Damage = 0;
				}
				Target->CharacterStatus.NowHP -= UKismetMathLibrary::Round(Damage);
				CheckHP(Target);
			}
			break;
		case ETargetType::Friend:
			if (PlayingCharacter->CharacterStatus.NowMP >= 0)
			{

			}
			break;
		case ETargetType::Self:
			break;
		}
		
	}
	CheckMP(PlayingCharacter);
}

void UMainCombat_Component::ChangeStatusItem(ACombatCharacterBase* PlayingCharacter)
{
}

void UMainCombat_Component::CheckHP(ACombatCharacterBase* Character)
{
	if (Character->CharacterStatus.NowHP < 0)
	{
		Character->CharacterStatus.NowHP = 0;
		Character->CharacterStatus.DieFlag = true;
	}
	else if (Character->CharacterStatus.NowHP > Character->CharacterStatus.MaxHP)
	{
		Character->CharacterStatus.NowHP = Character->CharacterStatus.MaxHP;
	}
}

void UMainCombat_Component::CheckMP(ACombatCharacterBase* Character)
{
	if (Character->CharacterStatus.NowMP < 0)
	{
		Character->CharacterStatus.NowMP = 0;
	}
	else if (Character->CharacterStatus.NowMP > Character->CharacterStatus.MaxMP)
	{
		Character->CharacterStatus.NowMP = Character->CharacterStatus.MaxMP;
	}
}

bool UMainCombat_Component::CheckGameOver(TArray<ACombatCharacterBase*> Players)
{
	bool flag = true;
	for (auto Player : Players)
	{
		if (!Player->CharacterStatus.DieFlag)
		{
			flag = false;
			break;
		}
	}
	return flag;
}

bool UMainCombat_Component::CheckWinner(TArray<ACombatCharacterBase*> Enemys)
{
	bool flag = true;
	for (auto Enemy : Enemys)
	{
		if (!Enemy->CharacterStatus.DieFlag)
		{
			flag = false;
			break;
		}
	}
	return flag;
}

void UMainCombat_Component::PlayerLevelUp(ACombatCharacterBase* Player, float TotalExp, FPlayerUpCoefficient PlayerUp, FDifficultyStatusUp DiffcultyStatusUp, FNeedExperience Need, int32& OutLevel, float& Amari)
{
	int UpLevel = 0;
	if (Player != nullptr)
	{
		if (!Player->CharacterStatus.DieFlag)
		{
			float NeedExp;
			Player->CharacterStatus.TotalExperience += TotalExp;
			TotalExp += Player->CharacterStatus.RemainderExperience;
			NeedExp = GetNeedExperience(Player, Need);
			while (NeedExp <= TotalExp){
				TotalExp -= NeedExp;
				Player->CharacterStatus.Level += 1;
				LevelUp(Player, PlayerUp, DiffcultyStatusUp);
				UpLevel++;
				NeedExp = GetNeedExperience(Player, Need);
			}
			Amari = TotalExp;
			OutLevel = UpLevel;
		}
		else
		{
			OutLevel = 0;
			Amari = 0;
		}
		
	}
}

float UMainCombat_Component::GetNeedExperience(ACombatCharacterBase* Player, FNeedExperience Need)
{
	if (nullptr != Player)
	{
		return Player->CharacterStatus.Level* Need.BaseExperience * Need.ToLevel[Player->CharacterStatus.Level % 10];
	}
	return 0.0f;
}

void UMainCombat_Component::LevelUp(ACombatCharacterBase* Player, FPlayerUpCoefficient PlayerUp, FDifficultyStatusUp DiffcultyStatusUp)
{
	int level = Player->CharacterStatus.Level;
	Player->CharacterStatus.MaxHP += FMath::RoundToInt(FMath::Pow(PlayerUp.UpHP, level) * DiffcultyStatusUp.ExpCoefficenet);
	Player->CharacterStatus.MaxSP += FMath::RoundToInt(FMath::Pow(PlayerUp.UpSP, level) * DiffcultyStatusUp.ExpCoefficenet);
	Player->CharacterStatus.MaxMP += FMath::RoundToInt(FMath::Pow(PlayerUp.UpMP, level) * DiffcultyStatusUp.ExpCoefficenet);
	Player->CharacterStatus.NormalAttack += FMath::RoundToInt(FMath::Pow(PlayerUp.UpNormalAttack, level) * DiffcultyStatusUp.ExpCoefficenet);
	Player->CharacterStatus.NormalDefense += FMath::RoundToInt(FMath::Pow(PlayerUp.UpNormalDefense, level) * DiffcultyStatusUp.ExpCoefficenet);
	Player->CharacterStatus.MagicAttack += FMath::RoundToInt(FMath::Pow(PlayerUp.UpMagicAttack, level) * DiffcultyStatusUp.ExpCoefficenet);
	Player->CharacterStatus.MagicDefense += FMath::RoundToInt(FMath::Pow(PlayerUp.UpMagicDefense, level) * DiffcultyStatusUp.ExpCoefficenet);
	Player->CharacterStatus.Speed += FMath::RoundToInt(FMath::Pow(PlayerUp.UpSpeed, level) * DiffcultyStatusUp.ExpCoefficenet);
}

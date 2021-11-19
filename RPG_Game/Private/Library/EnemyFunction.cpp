// Fill out your copyright notice in the Description page of Project Settings.


#include "Library/EnemyFunction.h"

FCharacterBaseStatus UEnemyFunction::GetEnemyStatus(int32 Index, int32 Level, const FEnemyStatusData EnemyData, const FEnemyUpCoefficient EnemyUpData,
	const EGrowRate GrowRate, const TArray<FItemStruct> MaterialItemStruct, const TArray<int32> MaterialNumber)
{
	FCharacterBaseStatus CharacterStatus;
	int32 Locallevel;
	CharacterStatus.GrowRate = GrowRate;
	if (GrowRate == EGrowRate::Child || Level < 20) {
		if (UKismetMathLibrary::RandomBoolWithWeight(.1f)) {
			Locallevel = GetEnemyLevel(100, 90);
			CharacterStatus.GrowRate = EGrowRate::Parent;
		}
		else
		{
			CharacterStatus.GrowRate = EGrowRate::Child;
			Locallevel = GetEnemyLevel(19, Level - 1);
		}
	}
	else
	{
		if (Level - 5 < 20)
			Locallevel = GetEnemyLevel(Level + 5, 20);
		else
			Locallevel = GetEnemyLevel(Level + 5, Level - 5);
		CharacterStatus.GrowRate = EGrowRate::Adult;
	}
	//NO DATA
	CharacterStatus.Gender;
	/*CharacterStatus.Skill;
	CharacterStatus.Magic;*/

	//�f�ރA�C�e�����v�Z����
	if (MaterialItemStruct.Num() == MaterialNumber.Num())
	{
		float coeff = Locallevel / 5.0f;
		coeff /= 10;
		coeff += 1.0f;
		float f = Locallevel / 3.0f;
		f /= 10;
		f += 1.0f;
		for (int32 i = 0; i < MaterialItemStruct.Num(); i++)
		{
			//�A�C�e���������v�Z����

			int32 MaterialCount = FMath::RoundToInt(MaterialNumber[i] * coeff);
			//�f�ރA�C�e�������L���Ă��邩�ǂ���
			FItemArray* ItemArray = CharacterStatus.Items.Find(MaterialItemStruct[i].Key);
			if (ItemArray)//���L���Ă���
			{
				//�f�ނ̐��A���[�v����
				for (int32 j = 0; j < MaterialCount; j++)
				{
					//�̐ς⎿�ʁA�N�I���e�B�[�����߂�
					FItemStruct material = MaterialItemStruct[i];
					material.Mass = FMath::RoundToInt(material.Mass * f);
					material.Volume = FMath::RoundToInt(material.Volume * f);
					material.Quality = FMath::RoundToInt(material.Quality * f);
					ItemArray->ItemStruct.Add(material);
				}
			}
			else
			{
				FItemArray Item;
				//�f�ނ̐��A���[�v����
				for (int32 j = 0; j < MaterialCount; j++)
				{
					//�̐ς⎿�ʁA�N�I���e�B�[�����߂�
					FItemStruct material = MaterialItemStruct[i];
					material.Mass = FMath::RoundToInt(material.Mass * f);
					material.Volume = FMath::RoundToInt(material.Volume * f);
					material.Quality = FMath::RoundToInt(material.Quality * f);
					Item.ItemStruct.Add(material);
				}
				CharacterStatus.Items.Add(MaterialItemStruct[i].Key, Item);
			}
		}
	}



	CharacterStatus.RemainderExperience = 0.0f;
	//Setup Data
	CharacterStatus.CharacterName = EnemyData.EnemyName;
	CharacterStatus.CharacterName.AppendInt(Index + 1);
	CharacterStatus.DieFlag = false;
	CharacterStatus.Level = Locallevel;
	CharacterStatus.Critical = EnemyData.EnemyCritical;
	CharacterStatus.CriticalCoefficient = EnemyData.EnemyCriticalCoefficient;
	//Random Data
	CharacterStatus.MagicAttack = EnemyData.EnemyMagicAttack + FMath::RoundToInt(GetAddStatus(EnemyUpData.UpMagicAttack, Locallevel, FMath::RandRange(0.5f, 1.5f)));
	CharacterStatus.MagicDefense = EnemyData.EnemyMagicDefense + FMath::RoundToInt(GetAddStatus(EnemyUpData.UpMagicDefense, Locallevel, FMath::RandRange(0.5f, 1.5f)));
	CharacterStatus.NormalAttack = EnemyData.EnemyNomalAttack + FMath::RoundToInt(GetAddStatus(EnemyUpData.UpNormalAttack, Locallevel, FMath::RandRange(0.5f, 1.5f)));
	CharacterStatus.NormalDefense = EnemyData.EnemyNomalDefense + FMath::RoundToInt(GetAddStatus(EnemyUpData.UpNormalDefense, Locallevel, FMath::RandRange(0.5f, 1.5f)));
	CharacterStatus.MaxHP = EnemyData.EnemyHP + FMath::RoundToInt(GetAddStatus(EnemyUpData.UpHP, Locallevel, FMath::RandRange(0.5f, 1.5f)));
	CharacterStatus.MaxMP = EnemyData.EnemyMP + FMath::RoundToInt(GetAddStatus(EnemyUpData.UpMP, Locallevel, FMath::RandRange(0.5f, 1.5f)));
	CharacterStatus.MaxSP = EnemyData.EnemySP + FMath::RoundToInt(GetAddStatus(EnemyUpData.UpSP, Locallevel, FMath::RandRange(0.5f, 1.5f)));
	CharacterStatus.Speed = EnemyData.EnemySpeed + FMath::RoundToInt(GetAddStatus(EnemyUpData.UpSpeed, Locallevel, FMath::RandRange(0.5f, 1.5f)));
	CharacterStatus.TotalExperience = EnemyData.EnemyExperience + GetAddStatus(EnemyUpData.UpExperience, Locallevel, FMath::RandRange(0.5f, 1.5f));

	if (Locallevel < 20)
	{
		CharacterStatus.MagicAttack /= 5;
		CharacterStatus.MagicDefense /= 5;
		CharacterStatus.NormalAttack /= 5;
		CharacterStatus.NormalDefense /= 5;
		CharacterStatus.MaxHP /= 5;
		CharacterStatus.MaxMP /= 5;
		CharacterStatus.MaxSP /= 5;
		CharacterStatus.Speed /= 5;
		CharacterStatus.TotalExperience /= 2;
	}

	//Now in Max
	CharacterStatus.NowHP = CharacterStatus.MaxHP;
	CharacterStatus.NowMP = CharacterStatus.MaxMP;
	CharacterStatus.NowSP = CharacterStatus.MaxSP;

	return CharacterStatus;
}

int32 UEnemyFunction::GetEnemyLevel(int32 Max, int32 Min)
{
	if (Min <= 0)
		Min = 1;
	return FMath::RandRange(Min, Max);
}


float UEnemyFunction::GetAddStatus(float Base, int32 Level, float Coefficient)
{
	return float(FMath::Pow(Base, (int32)Level) * Coefficient);
}

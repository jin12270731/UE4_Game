// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "./Character/MainMap/CharacterBase.h"
#include "./Character/MainMap/MainMapPC.h"
#include "./Character/MainMap/MainMapNPC.h"
#include "./Save/SettingSave.h"
#include "./Save/SaveData.h"
#include "./Component/MainSpawnManegerComponent.h"
#include "./Component/PickUpObjectComponent.h"
#include "Kismet/GameplayStatics.h"
#include "RPGGameInstance.generated.h"


UENUM(BlueprintType)
enum class EDifficultEnum : uint8
{
	Easy,
	Normal,
	Hard,
	Hel
};

UENUM(BlueprintType)
enum class EWhereOpen : uint8
{
	Start,
	Load,
	Return,
	Main
};

UENUM(BlueprintType)
enum class EEventProgress : uint8
{
	Yet,
	Continue,
	Completion
};

UENUM(BlueprintType)
enum class EWinnerKinds : uint8
{
	Dead,
	Escape
};

USTRUCT(BlueprintType)
struct FRandomFloat32  : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
		TMap<float, float> Random;
};

USTRUCT(BlueprintType)
struct FRandomInt32 : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
		TMap<int32, float> Random;
};

USTRUCT(BlueprintType)
struct FTitoStruct : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
		int32 TitoID;
	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
		ETitoList TitoEnum;
	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
		FString TitoName;
	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
		int32 TitoPoint;
	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
		FString Passward;
};

USTRUCT(BlueprintType)
struct FShopItemStruct
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
		FString ItemName;
	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
		int32 ItemCount;
	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
		FRandomInt32 AddRandomItemCount;
	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
		float BaseQuality;
	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
		FRandomFloat32 AddRandomQuality;
	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
		FRandomInt32 AddRandomMaxHP;
	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
		FRandomInt32 AddRandomNowHP;
};
USTRUCT(BlueprintType)
struct FShopItemsList : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
		FString ShopName;
	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
		TArray<FShopItemStruct> ItemsKinds;
};

USTRUCT(BlueprintType)
struct FExplanation : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
		TArray<FString> Explanation;
};

USTRUCT(BlueprintType)
struct FPlayStyleStruct : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int32 StyleID;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString PlaySyleName;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int32 NowTitoPoint;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		TArray<ETitoList> Titos;
};

USTRUCT(BlueprintType)
struct FPlayerBaseStatus : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 PCoins;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 GCoins;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 SCoins;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 BCoins;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FString CharacterName;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 Level;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 MaxHP;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 MaxSP;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 MaxMP;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 NormalAttack;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 MagicAttack;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 NormalDefense;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 MagicDefense;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 Speed;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float Critical;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float CriticalCoefficient;
};


USTRUCT(BlueprintType)
struct FDiffcultyNeedPoint : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float NeedTitoPoint;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float NeedSkillPoint;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float NeedMagicPoint;

};

USTRUCT(BlueprintType)
struct FSpawnEnemy
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 StatusID;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TArray<FCharacterBaseStatus> EnemyStatus;
};

USTRUCT(BlueprintType)
struct FEventState
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		EEventProgress EventProgress;

	FEventState() : EventProgress(EEventProgress::Yet) {};
};

USTRUCT(BlueprintType)
struct FEventsStruct : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event")
		TMap<FName, FEventState> EventMaps;
};

/**
 *
 */
UCLASS()
class URPGGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	//Save Targets
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SaveData")
		int32 PlayerNumber;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SaveData")
		TArray<FMainMapNPCStautus> SubPlayerStatus;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SaveData")
		FMainMapPCStautus MainMapPCStautus;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SaveData")
		FTimerStruct TimerStruct;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SaveData")
		EDifficultEnum NowDifficultEnum;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SaveData")
		USkeletalMesh* PlayerAppearance;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SaveData")
		TArray<FSpawnEnemy> SpawnEnemysStatus;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SaveData")
		TArray<FEnemySpawnPoint> EnemySpawnArray;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SaveData")
		TMap<FName, FEventsStruct> EventList;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SaveData")
		TArray<FMainMapObjectPoint> MainMapObjectPoint;
	//Can save?
	TMap<FString, TMap<FString, FItemArray>> ShopItemMap;

public:

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		USettingSave* SettingSave;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		USaveData* SaveData;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString NowSaveData;
	UPROPERTY(BlueprintReadWrite, EditanyWhere)
		TArray<FString> Season;

public:
	//Open Combat Level need Variable.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName EnemyTag;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Level;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isStatus;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 EnemyID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EWhereOpen WhereOpen;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EWinnerKinds WinnerKinds;

	//コンストラクタ
	URPGGameInstance(const FObjectInitializer& ObjectInitializer);
	//ランダムに関する関数
	UFUNCTION(BlueprintCallable, Category = "Random")
		int32 GetInt32Random(FRandomInt32 RandomList);
	UFUNCTION(BlueprintCallable, Category = "Random")
		float GetFloat32Random(FRandomFloat32 RandomList);
	template<typename T, typename U>
	T GetRandom(U RandomStruct);
	//セーブに関する関数
	UFUNCTION(BlueprintCallable, Category = "Save")
		bool MainSaveData(const FString saveName);
	UFUNCTION(BlueprintCallable, Category = "Save")
		bool SettingSaveData();
	UFUNCTION(BlueprintCallable, Category = "Save")
		bool LoadData(const FString loadName);
	UFUNCTION(BlueprintCallable, Category = "Save")
		TArray<FString> GetAllFilesInDirectory(const FString FullPath);
	//アイテムに関する関数
	UFUNCTION(BlueprintCallable, Category = "Item")
		bool UseSubPlayerItem(FText PlayerName, FItemStruct ItemStruct);
	UFUNCTION(BlueprintCallable, Category = "Item")
		bool UseMainPlayerItem(AMainMapPC* Status, FItemStruct ItemStruct);
	UFUNCTION(BlueprintCallable, Category = "Item")
		bool AppendSubPlayerItem(FText PlayerName, TArray<FItemStruct> ItemStructs, FMassAndVolume MassAndVolume);
	UFUNCTION(BlueprintCallable, Category = "Item")
		bool AppendMainPlayerItem(AMainMapPC* Status, TArray<FItemStruct> ItemStructs, FMassAndVolume MassAndVolume);
	UFUNCTION(BlueprintCallable, Category = "Item")
		bool RemoveItem(FText PlayerName, FString Key, int32 Index);
	template<typename T>
	bool UseItem(T Status, FItemStruct ItemStruct);
	template<typename T>
	bool AppendItems(T Status, TArray<FItemStruct> Items);
	//ショップに関する関数
	UFUNCTION(BlueprintCallable)
		bool GetShopItems(FString ShopKey, TMap<FString, FItemArray>& GetItems);
	UFUNCTION(BlueprintCallable)
		void AddShopItems(FString Name, FShopItemStruct ShopItemStruct, FItemStruct BaseItem);
	//装備に関する関数
	UFUNCTION(BlueprintCallable)
		bool SetSubPlayerClothse(FText PlayerName, EClothesPart ClothesPart, ERightOrLeft RightOrLeft, EFingerKinds FingerKinds, FClothesStruct ClothseStruct);
	UFUNCTION(BlueprintCallable)
		bool SetMainPlayerClothse(AMainMapPC* Status, EClothesPart ClothesPart, ERightOrLeft RightOrLeft, EFingerKinds FingerKinds, FClothesStruct ClothseStruct);
	UFUNCTION(BlueprintCallable)
		bool SubPlayerRemovePartClothes(FText PlayerName, EClothesPart ClothesPart, ERightOrLeft RightOrLeft, EFingerKinds FingerKinds);
	UFUNCTION(BlueprintCallable)
		bool MainPlayerRemovePartClothes(AMainMapPC* Status, EClothesPart ClothesPart, ERightOrLeft RightOrLeft, EFingerKinds FingerKinds);
	UFUNCTION(BlueprintCallable)
		bool RemoveClothse(FText PlayerName, FString Key, int32 Index);
	UFUNCTION(BlueprintCallable)
		FClothesStruct SetRightOrLeft(FText PlayerName, FString Key, int32 Index, ERightOrLeft RightOrLeft, EFingerKinds FingerKinds);
	UFUNCTION(BlueprintCallable)
		TArray<FClothesParts> GetFClothesParts(ERightOrLeft RightOrLeft, EFingerKinds FingerKinds, TArray<FClothesParts> ClothesParts);
	UFUNCTION(BlueprintCallable)
		void GetMainPlayerAddAndMultip(FMainMapPCStautus Status, TMap<FString, int32>& AdderStatus, TMap<FString, float>& MultipStatus);
	UFUNCTION(BlueprintCallable)
		void GetSubPlayerAddAndMultip(FMainMapNPCStautus Status, TMap<FString, int32>& AdderStatus, TMap<FString, float>& MultipStatus);
	template<typename T>
	T SetClothse(T Status, EClothesPart ClothesPart, ERightOrLeft RightOrLeft, EFingerKinds FingerKinds, FClothesStruct ClothesStruct);
	template<typename T>
	TTuple<TMap<FString, int32>, TMap<FString, float>> GetBaseStatus(const T& Status);
	template<typename T>
	T GetChangeStatus(T Status, TMap<FString, int32> BaseStatus1, TMap<FString, float> BaseStatus2);
	template<typename T>
	TTuple<TMap<FString, int32>, TMap<FString, float>> GetAddAndMultip(const T& Status);
	template<typename T>
	bool RemovePartClothes(T Status, EClothesPart ClothesPart, ERightOrLeft RightOrLeft, EFingerKinds FingerKinds);
	//ステータスに関する関数
	template<typename T>
	bool SleepRecovery(T Status, int32 hours, int32 Min);
	template<typename T>
	bool CalcuMassAndVolume(T Status);
	UFUNCTION(BlueprintCallable)
		bool SleepRecovery(AMainMapPC* Status, int32 hours, int32 Min);
	UFUNCTION(BlueprintCallable)
		bool MainPlayerCalcuMassAndVolume(AMainMapPC* Status);
	UFUNCTION(BlueprintCallable)
		bool SubPlayerCalcuMassAndVolume();
	//メインマップ画面のスタミナ機能に関する関数
	void SetTimerStruct(const FTimerStruct timer) { TimerStruct = timer; }
	UFUNCTION(BlueprintCallable)
		void UpdataFlag(TArray<FString> Names);
	UFUNCTION(BlueprintCallable)
		bool CheckFlag(TArray<FString> Names);
	static URPGGameInstance* GetGameInstance();
	virtual void Init() override;
};

//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("test"));

template<typename T, typename U>
inline T URPGGameInstance::GetRandom(U RandomStruct)
{
	TArray<T> Keys;
	RandomStruct.Random.GetKeys(Keys);
	float result = FMath::RandRange(0.0f, 100.0f);
	for (const auto& Key : Keys)
	{
		float* Value = RandomStruct.Random.Find(Key);
		if (Value)
		{
			if (result <= *Value)
			{
				return Key;
			}
		}
	}
	T t = T(0.1);
	return t * 10;
}

template<typename T>
inline bool URPGGameInstance::UseItem(T Status, FItemStruct ItemStruct)
{
	float HPCoeff = (float)ItemStruct.NowHP / ItemStruct.MaxHP;
	for (const auto FluctuationStatusStruct : ItemStruct.FluctuationStatusStructs)
	{
		int32 Value = UKismetMathLibrary::Round(FluctuationStatusStruct.Value * HPCoeff * ItemStruct.Quality);

		//アイテム内容を実行
		switch (FluctuationStatusStruct.TargetStatus)
		{
		case ETargetStatus::MaxHP:
		{
			Status.MaxHP += Value;
			break;
		}
		case ETargetStatus::NowHP:
		{
			Status.NowHP += Value;
			break;
		}
		case ETargetStatus::MaxMP:
		{
			Status.MaxMP += Value;
			break;
		}
		case ETargetStatus::NowMP:
		{
			Status.NowMP += Value;
			break;
		}
		case ETargetStatus::MaxSP:
		{
			Status.MaxSP += Value;
			break;
		}
		case ETargetStatus::NowSP:
		{
			Status.NowSP += Value;
			break;
		}
		}
	}
	return true;
}

template<typename T>
inline bool URPGGameInstance::AppendItems(T Status, TArray<FItemStruct> Items)
{
	for (auto item : Items)
	{
		FItemArray* ItemArray = Status.Items.Find(item.Key);
		if (ItemArray)
		{
			ItemArray->ItemStruct.Add(item);
		}
		else
		{
			FItemArray itemArray = FItemArray(item);
			Status.Items.Add(item.Key, itemArray);
		}
	}
	return false;
}


//現在装備している装備を変更や追加を行う
template<typename T>
inline T URPGGameInstance::SetClothse(T Status, EClothesPart ClothesPart, ERightOrLeft RightOrLeft, EFingerKinds FingerKinds, FClothesStruct ClothesStruct)
{
	bool isFirst = true;
	FOtherClothes OtherClothes = FOtherClothes();
	UEnum* const ClothesPartEnum = FindObject<UEnum>(ANY_PACKAGE, TEXT("EClothesPart"));
	UEnum* const RightOrLeftEnum = FindObject<UEnum>(ANY_PACKAGE, TEXT("ERightOrLeft"));
	UEnum* const FingerKindsEnum = FindObject<UEnum>(ANY_PACKAGE, TEXT("EFingerKinds"));

	//現在装備しているやつを全て外す
	for (const auto ClothesParts : ClothesStruct.ClothesParts)
	{
		if (ClothesPartEnum && RightOrLeftEnum && FingerKindsEnum)
		{
			FString ClothesPartString = "";
			if (INDEX_NONE == OtherClothes.OtherClothesPart.Find(ClothesParts.ClothesPart))
			{
				if (ClothesParts.ClothesPart != EClothesPart::Finger)
				{
					ClothesPartString.Append(RightOrLeftEnum->GetNameStringByIndex(static_cast<int32>(ClothesParts.RightOrLeft)));
				}
				else
				{
					ClothesPartString.Append(RightOrLeftEnum->GetNameStringByIndex(static_cast<int32>(ClothesParts.RightOrLeft)));
					ClothesPartString.Append(FingerKindsEnum->GetNameStringByIndex(static_cast<int32>(ClothesParts.FingerKinds)));
				}
				ClothesPartString.Append("_");
			}
			FString PartString = ClothesPartEnum->GetNameStringByIndex(static_cast<int32>(ClothesParts.ClothesPart));
			ClothesPartString.Append(PartString);
			const FClothesStruct* clothes = Status.Clothes.Find(FName(*ClothesPartString));
			if (clothes)
			{
				//もともと装備している場合は装備リストに移す
				TArray<FString> GetKey;
				Status.HaveClothes.GetKeys(GetKey);
				bool isAdd = false;
				//外す装備の退避
				for (const auto K : GetKey)
				{
					//外す装備の名前と所有している装備の名前を比較する
					if (clothes->Name.Equals(Status.HaveClothes.Find(K)->ClothesStruct[0].Name))
					{
						//所有装備に装備キーの場所に装備構造体を入れる
						for (auto ClothesPart1 : clothes->ClothesParts)
						{
							FString str = "";
							if (INDEX_NONE == OtherClothes.OtherClothesPart.Find(ClothesPart1.ClothesPart))
							{
								if (ClothesPart1.ClothesPart != EClothesPart::Finger)
								{
									str.Append(RightOrLeftEnum->GetNameStringByIndex(static_cast<int32>(ClothesPart1.RightOrLeft)));
								}
								else
								{
									str.Append(RightOrLeftEnum->GetNameStringByIndex(static_cast<int32>(ClothesPart1.RightOrLeft)));
									str.Append(FingerKindsEnum->GetNameStringByIndex(static_cast<int32>(ClothesPart1.FingerKinds)));
								}
								str.Append("_");
							}
							str.Append(ClothesPartEnum->GetNameStringByIndex(static_cast<int32>(ClothesPart1.ClothesPart)));
							const FClothesStruct* localClothes = Status.Clothes.Find(FName(*str));
							if (localClothes)
							{
								if (localClothes->FluctuationStatusStructs.Num() > 0)
								{
									Status.HaveClothes.Find(K)->ClothesStruct.Add(*localClothes);
									isAdd = true;//外した装備の退避完了
									GEngine->AddOnScreenDebugMessage(-1, 100.0f, FColor::Purple, TEXT("add clothes"));
									break;
								}
							}
						}
					}
				}
				if (!isAdd)//外した装備の退避完了していない
				{
					//所有装備リストになかったら、新たに追加する
					FClothesArray addClothesArray;
					for (auto ClothesPart1 : clothes->ClothesParts)
					{
						FString str = "";
						if (INDEX_NONE == OtherClothes.OtherClothesPart.Find(ClothesPart1.ClothesPart))
						{
							if (ClothesPart1.ClothesPart != EClothesPart::Finger)
							{
								str.Append(RightOrLeftEnum->GetNameStringByIndex(static_cast<int32>(ClothesPart1.RightOrLeft)));
							}
							else
							{
								str.Append(RightOrLeftEnum->GetNameStringByIndex(static_cast<int32>(ClothesPart1.RightOrLeft)));
								str.Append(FingerKindsEnum->GetNameStringByIndex(static_cast<int32>(ClothesPart1.FingerKinds)));
							}
							str.Append("_");
						}
						str.Append(ClothesPartEnum->GetNameStringByIndex(static_cast<int32>(ClothesPart1.ClothesPart)));
						const FClothesStruct* localClothes = Status.Clothes.Find(FName(*str));
						if (localClothes)
						{
							if (localClothes->FluctuationStatusStructs.Num() > 0)
							{
								GEngine->AddOnScreenDebugMessage(-1, 100.0f, FColor::Purple, TEXT("make clothes"));
								addClothesArray.ClothesStruct.Add(*localClothes);
								break;
							}
						}
					}
					if (!clothes->Key.IsEmpty())
					{
						Status.HaveClothes.Add(clothes->Key, addClothesArray);
					}
				}
				//外す装備の退避完了
				//必要ない装備リストを作成する
				FString string;
				TArray<FString> keys;
				for (auto ClothesPart1 : clothes->ClothesParts)
				{
					string = "";
					if (INDEX_NONE == OtherClothes.OtherClothesPart.Find(ClothesPart1.ClothesPart))
					{
						string.Append(RightOrLeftEnum->GetNameStringByIndex(static_cast<int32>(ClothesPart1.RightOrLeft)));
						if (ClothesPart1.ClothesPart == EClothesPart::Finger)
						{
							string.Append(FingerKindsEnum->GetNameStringByIndex(static_cast<int32>(ClothesPart1.FingerKinds)));
						}
						string.Append("_");
					}
					string.Append(ClothesPartEnum->GetNameStringByIndex(static_cast<int32>(ClothesPart1.ClothesPart)));
					keys.Add(string);
				}
				//必要ない装備リストを作成した
				for (auto key : keys)
				{
					Status.Clothes.Remove(FName(*key));//不必要な装備を削除する
				}
			}
		}
	}
	//現在装備しているやつを全て外すのを完了

	//装備する
	bool isSetClothes = false;//一度は装備構造体を入れたかどうか
	bool Rflag = false;		  //右にいれたか
	for (const auto ClothesParts : ClothesStruct.ClothesParts)
	{
		if (ClothesPartEnum && RightOrLeftEnum && FingerKindsEnum)
		{
			FString ClothesPartString = "";
			if (INDEX_NONE == OtherClothes.OtherClothesPart.Find(ClothesParts.ClothesPart))
			{
				if (ClothesParts.ClothesPart != EClothesPart::Finger)
				{
					ClothesPartString.Append(RightOrLeftEnum->GetNameStringByIndex(static_cast<int32>(ClothesParts.RightOrLeft)));
				}
				else
				{
					ClothesPartString.Append(RightOrLeftEnum->GetNameStringByIndex(static_cast<int32>(ClothesParts.RightOrLeft)));
					ClothesPartString.Append(FingerKindsEnum->GetNameStringByIndex(static_cast<int32>(ClothesParts.FingerKinds)));
				}
				ClothesPartString.Append("_");
			}
			FString PartString = ClothesPartEnum->GetNameStringByIndex(static_cast<int32>(ClothesParts.ClothesPart));
			ClothesPartString.Append(PartString);
			if (!isSetClothes)
			{
				if (INDEX_NONE == OtherClothes.OtherClothesPart.Find(ClothesParts.ClothesPart))
				{
					//GEngine->AddOnScreenDebugMessage(-1, 100.0f, FColor::Yellow, TEXT("have not clothes(INDEX_NONE)"));
					if (FingerKinds == EFingerKinds::other)
					{
						if (RightOrLeft != ERightOrLeft::Other)
						{
							FString string = RightOrLeftEnum->GetNameStringByIndex(static_cast<int32>(RightOrLeft));
							string.Append("_");
							string.Append(PartString);
							Status.Clothes.Add(FName(*string), ClothesStruct);

						}
						else
						{
							Status.Clothes.Add(FName(*ClothesPartString), ClothesStruct);
						}
					}
					else
					{
						//GEngine->AddOnScreenDebugMessage(-1, 100.0f, FColor::Yellow, TEXT("have not clothes(EFingerKinds::other)"));
						FString string = RightOrLeftEnum->GetNameStringByIndex(static_cast<int32>(RightOrLeft));
						string.Append(FingerKindsEnum->GetNameStringByIndex(static_cast<int32>(FingerKinds)));
						string.Append("_");
						string.Append(PartString);
						Status.Clothes.Add(FName(*string), ClothesStruct);
					}
				}
				else
				{
					//GEngine->AddOnScreenDebugMessage(-1, 100.0f, FColor::Yellow, TEXT("have not clothes"));
					Status.Clothes.Add(FName(*PartString), ClothesStruct);
				}
				isSetClothes = true;
			}
			else
			{
				//GEngine->AddOnScreenDebugMessage(-1, 100.0f, FColor::Yellow, TEXT("have clothes"));
				//一度装備構造体を入れた場合は空の構造体を入れる
				if (INDEX_NONE == OtherClothes.OtherClothesPart.Find(ClothesParts.ClothesPart))
				{
					if (ClothesParts.ClothesPart != EClothesPart::Finger)
					{
						FString LocalString = FString("Right");
						LocalString.Append("_");
						LocalString.Append(PartString);
						if (!Rflag)
						{
							if (isFirst)
								Status.Clothes.Add(FName(*LocalString), ClothesStruct);
							else
								Status.Clothes.Add(FName(*LocalString), FClothesStruct(ClothesStruct.Name, ClothesStruct.ClothesParts));
							Rflag = true;
						}
						else
						{
							FString LocalString2 = FString("Left");
							LocalString2.Append("_");
							LocalString2.Append(PartString);
							if (isFirst)
								Status.Clothes.Add(FName(*LocalString2), ClothesStruct);
							else
								Status.Clothes.Add(FName(*LocalString2), FClothesStruct(ClothesStruct.Name, ClothesStruct.ClothesParts));
						}
					}
				}
				else
				{
					if (isFirst)
						Status.Clothes.Add(FName(*PartString), ClothesStruct);
					else
						Status.Clothes.Add(FName(*PartString), FClothesStruct(ClothesStruct.Name, ClothesStruct.ClothesParts));
				}
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 100.0f, FColor::Red, TEXT("error"));
		}
		isFirst = false;
	}
	return Status;
}

//装備を何もしていないときのステータス
template<typename T>
inline TTuple<TMap<FString, int32>, TMap<FString, float>> URPGGameInstance::GetBaseStatus(const T& Status)
{
	TArray<FName> Keys;
	Status.Clothes.GetKeys(Keys);
	TMap<FString, int32> BaseStatus1;
	TMap<FString, float> BaseStatus2;
	BaseStatus1.Add("NowHP", Status.NowHP);
	BaseStatus1.Add("MaxHP", Status.MaxHP);
	BaseStatus1.Add("NowMP", Status.NowMP);
	BaseStatus1.Add("MaxMP", Status.MaxMP);
	BaseStatus1.Add("NowSP", Status.NowSP);
	BaseStatus1.Add("MaxSP", Status.MaxSP);
	BaseStatus1.Add("NA", Status.NormalAttack);
	BaseStatus1.Add("MA", Status.MagicAttack);
	BaseStatus1.Add("ND", Status.NormalDefense);
	BaseStatus1.Add("MD", Status.MagicDefense);
	BaseStatus1.Add("Speed", Status.Speed);
	BaseStatus2.Add("C", Status.Critical);
	BaseStatus2.Add("CC", Status.CriticalCoefficient);
	BaseStatus2.Add("Exp", Status.TotalExperience);
	TMap<FString, float> coeff;
	coeff.Add("NowHP", 1.0f);
	coeff.Add("MaxHP", 1.0f);
	coeff.Add("NowMP", 1.0f);
	coeff.Add("MaxMP", 1.0f);
	coeff.Add("NowSP", 1.0f);
	coeff.Add("MaxSP", 1.0f);
	coeff.Add("NA", 1.0f);
	coeff.Add("MA", 1.0f);
	coeff.Add("ND", 1.0f);
	coeff.Add("MD", 1.0f);
	coeff.Add("Speed", 1.0f);
	coeff.Add("C", 1.0f);
	coeff.Add("CC", 1.0f);
	coeff.Add("Exp", 1.0f);
	for (auto key : Keys)
	{
		for (auto FluctuationStatusStruct : Status.Clothes.FindRef(key).FluctuationStatusStructs)
		{
			UEnum* const Enum = FindObject<UEnum>(ANY_PACKAGE, TEXT("ETargetStatus"));
			if (Enum)
			{
				FString TargetS = Enum->GetNameStringByIndex(static_cast<int32>(FluctuationStatusStruct.TargetStatus));
				int32* valu = BaseStatus1.Find(TargetS);
				if (valu)
				{
					float multip = (((float)Status.Clothes.FindRef(key).NowHP / Status.Clothes.FindRef(key).MaxHP) * Status.Clothes.FindRef(key).Quality * FluctuationStatusStruct.Value);
					int32 adder = FMath::RoundToInt(multip);
					if (FluctuationStatusStruct.AdderOrMultip == EAdderOrMultip::Adder)
						*valu -= adder;
					else
					{
						if (coeff.Find(TargetS))
							*coeff.Find(TargetS) += (multip - 1);
					}
				}
				else
				{
					float multip = (((float)Status.Clothes.FindRef(key).NowHP / Status.Clothes.FindRef(key).MaxHP) * Status.Clothes.FindRef(key).Quality * FluctuationStatusStruct.Value);
					int32 adder = FMath::RoundToInt(multip);
					float* flo = BaseStatus2.Find(TargetS);
					if (flo)
					{
						if (FluctuationStatusStruct.AdderOrMultip == EAdderOrMultip::Adder)
							*flo -= adder;
						else
						{
							if (coeff.Find(TargetS))
								*coeff.Find(TargetS) += (multip - 1);
						}
					}
				}
			}
		}
	}
	TArray<FString> s;
	coeff.GetKeys(s);
	for (const auto string : s)
	{
		int32* v = BaseStatus1.Find(string);
		if (v)
		{
			*v /= coeff.FindRef(string);
		}
		else
		{
			float* f = BaseStatus2.Find(string);
			if (f)
			{
				*f /= coeff.FindRef(string);
			}
		}
	}
	return TTuple<TMap<FString, int32>, TMap<FString, float>>(BaseStatus1, BaseStatus2);
}

template<typename T>
inline T URPGGameInstance::GetChangeStatus(T Status, TMap<FString, int32> BaseStatus1, TMap<FString, float> BaseStatus2)
{
	//BaseStatusをもとに現在の装備で追加するステータスを計算する
	TArray<FName> Names;
	TMap<FString, int32> UpdateStatus1 = BaseStatus1;
	TMap<FString, float> UpdateStatus2 = BaseStatus2;
	Status.Clothes.GetKeys(Names);
	for (const auto name : Names)
	{
		for (auto FluctuationStatusStruct : Status.Clothes.Find(name)->FluctuationStatusStructs)
		{
			UEnum* const Enum = FindObject<UEnum>(ANY_PACKAGE, TEXT("ETargetStatus"));
			if (Enum)
			{
				//ターゲットのステータスを取得する
				FString K = Enum->GetNameStringByIndex(static_cast<int32>(FluctuationStatusStruct.TargetStatus));
				int32* updata1 = UpdateStatus1.Find(K);
				int32* base1 = BaseStatus1.Find(K);
				if (base1 && updata1 && !Status.Clothes.FindRef(name).Name.IsEmpty())
				{
					float multip = (((float)Status.Clothes.FindRef(name).NowHP / Status.Clothes.FindRef(name).MaxHP) * Status.Clothes.FindRef(name).Quality * FluctuationStatusStruct.Value);
					int32 adder = FMath::RoundToInt(multip);
					if (FluctuationStatusStruct.AdderOrMultip == EAdderOrMultip::Adder)
						*updata1 += adder;
					else
						*updata1 += (multip - 1.f) * *base1;
				}
				else
				{
					float* updata2 = UpdateStatus2.Find(K);
					float* base2 = BaseStatus2.Find(K);
					if (base2 && updata2 && !Status.Clothes.FindRef(name).Name.IsEmpty())
					{
						float multip = (((float)Status.Clothes.FindRef(name).NowHP / Status.Clothes.FindRef(name).MaxHP) * Status.Clothes.FindRef(name).Quality * FluctuationStatusStruct.Value);
						int32 adder = FMath::RoundToInt(multip);
						if (FluctuationStatusStruct.AdderOrMultip == EAdderOrMultip::Adder)
							*updata2 += adder;
						else
							*updata2 += (multip - 1.f) * *base2;
					}
				}
			}
		}
	}
	TArray<FString> string1;
	UpdateStatus1.GetKeys(string1);
	for (const auto string : string1)
	{
		if (string.Equals("NowHP"))
			Status.NowHP = UpdateStatus1.FindRef(string);
		else if (string.Equals("MaxHP"))
			Status.MaxHP = UpdateStatus1.FindRef(string);
		else if (string.Equals("NowMP"))
			Status.NowMP = UpdateStatus1.FindRef(string);
		else if (string.Equals("MaxMP"))
			Status.MaxMP = UpdateStatus1.FindRef(string);
		else if (string.Equals("NowSP"))
			Status.NowSP = UpdateStatus1.FindRef(string);
		else if (string.Equals("MaxSP"))
			Status.MaxSP = UpdateStatus1.FindRef(string);
		else if (string.Equals("NA"))
			Status.NormalAttack = UpdateStatus1.FindRef(string);
		else if (string.Equals("MA"))
			Status.MagicAttack = UpdateStatus1.FindRef(string);
		else if (string.Equals("ND"))
			Status.NormalDefense = UpdateStatus1.FindRef(string);
		else if (string.Equals("MD"))
			Status.MagicDefense = UpdateStatus1.FindRef(string);
		else if (string.Equals("Speed"))
			Status.Speed = UpdateStatus1.FindRef(string);
	}
	TArray<FString> string2;
	UpdateStatus2.GetKeys(string2);
	for (const auto string : string2)
	{
		if (string.Equals("C"))
			Status.Critical = UpdateStatus2.FindRef(string);
		else if (string.Equals("CC"))
			Status.CriticalCoefficient = UpdateStatus2.FindRef(string);
		else if (string.Equals("Exp"))
			Status.TotalExperience = UpdateStatus2.FindRef(string);
	}
	return Status;
}

template<typename T>
inline TTuple<TMap<FString, int32>, TMap<FString, float>> URPGGameInstance::GetAddAndMultip(const T& Status)
{
	TMap<FString, int32> adder;
	adder.Add("NowHP", 0);
	adder.Add("MaxHP", 0);
	adder.Add("NowMP", 0);
	adder.Add("MaxMP", 0);
	adder.Add("NowSP", 0);
	adder.Add("MaxSP", 0);
	adder.Add("NA", 0);
	adder.Add("MA", 0);
	adder.Add("ND", 0);
	adder.Add("MD", 0);
	adder.Add("Speed", 0);
	adder.Add("C", 0);
	adder.Add("CC", 0);
	adder.Add("Exp", 0);
	TMap<FString, float> coeff;
	coeff.Add("NowHP", 1.0f);
	coeff.Add("MaxHP", 1.0f);
	coeff.Add("NowMP", 1.0f);
	coeff.Add("MaxMP", 1.0f);
	coeff.Add("NowSP", 1.0f);
	coeff.Add("MaxSP", 1.0f);
	coeff.Add("NA", 1.0f);
	coeff.Add("MA", 1.0f);
	coeff.Add("ND", 1.0f);
	coeff.Add("MD", 1.0f);
	coeff.Add("Speed", 1.0f);
	coeff.Add("C", 1.0f);
	coeff.Add("CC", 1.0f);
	coeff.Add("Exp", 1.0f);
	TArray<FName> Keys;
	Status.Clothes.GetKeys(Keys);
	for (auto key : Keys)
	{
		for (auto FluctuationStatusStruct : Status.Clothes.FindRef(key).FluctuationStatusStructs)
		{
			UEnum* const Enum = FindObject<UEnum>(ANY_PACKAGE, TEXT("ETargetStatus"));
			if (Enum)
			{
				FString TargetNameString = Enum->GetNameStringByIndex(static_cast<int32>(FluctuationStatusStruct.TargetStatus));
				float flo = ((float)Status.Clothes.FindRef(key).NowHP / Status.Clothes.FindRef(key).MaxHP) * Status.Clothes.FindRef(key).Quality * FluctuationStatusStruct.Value;

				if (FluctuationStatusStruct.AdderOrMultip == EAdderOrMultip::Adder)
				{
					int32* integer = adder.Find(TargetNameString);
					if (integer)
					{
						*integer += flo;
					}
				}
				else
				{
					float* flo2 = coeff.Find(TargetNameString);
					if (flo2)
					{
						*flo2 += (flo - 1);
					}
				}
			}
		}
	}
	return TTuple<TMap<FString, int32>, TMap<FString, float>>(adder, coeff);
}

template<typename T>
inline bool URPGGameInstance::RemovePartClothes(T Status, EClothesPart ClothesPart, ERightOrLeft RightOrLeft, EFingerKinds FingerKinds)
{
	FOtherClothes OtherClothes = FOtherClothes();
	UEnum* const ClothesPartEnum = FindObject<UEnum>(ANY_PACKAGE, TEXT("EClothesPart"));
	UEnum* const RightOrLeftEnum = FindObject<UEnum>(ANY_PACKAGE, TEXT("ERightOrLeft"));
	UEnum* const FingerKindsEnum = FindObject<UEnum>(ANY_PACKAGE, TEXT("EFingerKinds"));

	//指定した場所の装備を削除する
	if (ClothesPartEnum && RightOrLeftEnum && FingerKindsEnum)
	{
		FString ClothesPartString = "";
		if (INDEX_NONE == OtherClothes.OtherClothesPart.Find(ClothesPart))
		{
			if (ClothesPart != EClothesPart::Finger)
			{
				ClothesPartString.Append(RightOrLeftEnum->GetNameStringByIndex(static_cast<int32>(RightOrLeft)));
			}
			else
			{
				ClothesPartString.Append(RightOrLeftEnum->GetNameStringByIndex(static_cast<int32>(RightOrLeft)));
				ClothesPartString.Append(FingerKindsEnum->GetNameStringByIndex(static_cast<int32>(FingerKinds)));
			}
			ClothesPartString.Append("_");
		}
		FString PartString = ClothesPartEnum->GetNameStringByIndex(static_cast<int32>(ClothesPart));
		ClothesPartString.Append(PartString);
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, ClothesPartString);
		const FClothesStruct* clothes = Status.Clothes.Find(FName(*ClothesPartString));
		if (clothes)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("find"));
			//もともと装備している場合は装備リストに移す
			TArray<FString> GetKey;
			Status.HaveClothes.GetKeys(GetKey);
			bool isAdd = false;
			//外す装備の退避
			for (const auto K : GetKey)
			{
				//外す装備の名前と所有している装備の名前を比較する
				if (clothes->Name.Equals(Status.HaveClothes.Find(K)->ClothesStruct[0].Name))
				{
					//所有装備に装備キーの場所に装備構造体を入れる
					for (auto ClothesPart1 : clothes->ClothesParts)
					{
						FString str = "";
						if (INDEX_NONE == OtherClothes.OtherClothesPart.Find(ClothesPart1.ClothesPart))
						{
							if (ClothesPart1.ClothesPart != EClothesPart::Finger)
							{
								str.Append(RightOrLeftEnum->GetNameStringByIndex(static_cast<int32>(ClothesPart1.RightOrLeft)));
							}
							else
							{
								str.Append(RightOrLeftEnum->GetNameStringByIndex(static_cast<int32>(ClothesPart1.RightOrLeft)));
								str.Append(FingerKindsEnum->GetNameStringByIndex(static_cast<int32>(ClothesPart1.FingerKinds)));
							}
							str.Append("_");
						}
						str.Append(ClothesPartEnum->GetNameStringByIndex(static_cast<int32>(ClothesPart1.ClothesPart)));
						const FClothesStruct* localClothes = Status.Clothes.Find(FName(*str));
						if (localClothes)
						{
							if (localClothes->FluctuationStatusStructs.Num() > 0)
							{
								Status.HaveClothes.Find(K)->ClothesStruct.Add(*localClothes);
								isAdd = true;//外した装備の退避完了
								GEngine->AddOnScreenDebugMessage(-1, 100.0f, FColor::Purple, TEXT("add clothes"));
								break;
							}
						}
					}
				}
			}
			if (!isAdd)//外した装備の退避完了していない
			{
				//所有装備リストになかったら、新たに追加する
				FClothesArray addClothesArray;
				for (auto ClothesPart1 : clothes->ClothesParts)
				{
					FString str = "";
					if (INDEX_NONE == OtherClothes.OtherClothesPart.Find(ClothesPart1.ClothesPart))
					{
						if (ClothesPart1.ClothesPart != EClothesPart::Finger)
						{
							str.Append(RightOrLeftEnum->GetNameStringByIndex(static_cast<int32>(ClothesPart1.RightOrLeft)));
						}
						else
						{
							str.Append(RightOrLeftEnum->GetNameStringByIndex(static_cast<int32>(ClothesPart1.RightOrLeft)));
							str.Append(FingerKindsEnum->GetNameStringByIndex(static_cast<int32>(ClothesPart1.FingerKinds)));
						}
						str.Append("_");
					}
					str.Append(ClothesPartEnum->GetNameStringByIndex(static_cast<int32>(ClothesPart1.ClothesPart)));
					const FClothesStruct* localClothes = Status.Clothes.Find(FName(*str));
					if (localClothes)
					{
						if (localClothes->FluctuationStatusStructs.Num() > 0)
						{
							//GEngine->AddOnScreenDebugMessage(-1, 100.0f, FColor::Purple, TEXT("make clothes"));
							addClothesArray.ClothesStruct.Add(*localClothes);
							break;
						}
					}
				}
				if (!clothes->Key.IsEmpty())
				{
					Status.HaveClothes.Add(clothes->Key, addClothesArray);
				}
			}
			//外す装備の退避完了
			//必要ない装備リストを作成する
			FString string;
			TArray<FString> keys;
			for (auto ClothesPart1 : clothes->ClothesParts)
			{
				string = "";
				if (INDEX_NONE == OtherClothes.OtherClothesPart.Find(ClothesPart1.ClothesPart))
				{
					string.Append(RightOrLeftEnum->GetNameStringByIndex(static_cast<int32>(ClothesPart1.RightOrLeft)));
					if (ClothesPart1.ClothesPart == EClothesPart::Finger)
					{
						string.Append(FingerKindsEnum->GetNameStringByIndex(static_cast<int32>(ClothesPart1.FingerKinds)));
					}
					string.Append("_");
				}
				string.Append(ClothesPartEnum->GetNameStringByIndex(static_cast<int32>(ClothesPart1.ClothesPart)));
				keys.Add(string);
			}
			//必要ない装備リストを作成した
			for (auto key : keys)
			{
				Status.Clothes.Remove(FName(*key));//不必要な装備を削除する
			}
		}
		else
		{
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("notFind"));
			return false;//装備がない場合
		}
	}
	return true;
}

template<typename T>
inline bool URPGGameInstance::SleepRecovery(T Status, int32 hours, int32 Min)
{
	int32 time = (hours * 60) + Min;
	int32 localHP = Status.NowHP;
	int32 localMP = Status.NowMP;
	int32 localSP = Status.NowSP;
	localHP += 0.5 * time;
	localMP += (Status.MagicAttack / 10 + Status.MagicDefense) * time;
	localSP += (Status.NormalAttack / 10 + Status.NormalDefense) * time;
	if (localHP > 0 && localHP <= Status.MaxHP)
		Status.NowHP = localHP;
	else if (localHP > Status.MaxHP)
		Status.NowHP = Status.MaxHP;

	if (localMP > 0 && localMP <= Status.MaxMP)
		Status.NowMP = localMP;
	else if (localMP > Status.MaxMP)
		Status.NowMP = Status.MaxMP;

	if (localSP > 0 && localSP <= Status.MaxSP)
		Status.NowSP = localSP;
	else if (localSP > Status.MaxSP)
		Status.NowSP = Status.MaxSP;
	return true;
}

template<typename T>
inline bool URPGGameInstance::CalcuMassAndVolume(T Status)
{
	TArray<FString> Keys;
	Status.Items.GetKeys(Keys);
	int32 Volome = 0;
	int32 Mass = 0;
	int32 ClothesVolome = 0;
	int32 ClothesMass = 0;
	//アイテムの質量と体積を計算
	for (const auto key : Keys)
	{
		for (const auto Item : Status.Items.FindRef(key).ItemStruct)
		{
			Volome += Item.Volume;
			Mass += Item.Mass;
		}
	}
	//所有装備の質量と体積を計算
	Status.HaveClothes.GetKeys(Keys);
	for (const auto key : Keys)
	{
		for (const auto HaveClothes : Status.HaveClothes.FindRef(key).ClothesStruct)
		{
			Volome += HaveClothes.Volume;
			Mass += HaveClothes.Mass;
		}
	}
	//装備の質量と体積を計算
	TArray<FName> Name;
	Status.Clothes.GetKeys(Name);
	for (const auto key : Name)
	{
		const FClothesStruct* Clothes = Status.Clothes.Find(key);
		if (Clothes)
		{
			ClothesVolome += Clothes->Volume;
			ClothesMass += Clothes->Mass;
		}
	}
	Status.MassAndVolume.NowMass = Mass;
	Status.MassAndVolume.NowVolume = Volome;
	Status.MassAndVolume.ClothesNowMass = ClothesMass;
	Status.MassAndVolume.ClothesNowVolume = ClothesVolome;
	return true;
}

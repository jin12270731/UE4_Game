// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/RPGGameInstance.h"
#include "Misc/LocalTimestampDirectoryVisitor.h"


URPGGameInstance::URPGGameInstance(const FObjectInitializer& ObjectInitializer) {
	//Need
	TimerStruct.MyDays = 0;
	TimerStruct.MyHours = 0;
	TimerStruct.MyMinute = 0.0f;
	TimerStruct.WorldCalendar = FString(TEXT("test"));
	TimerStruct.WorldYear = 354;
	//0:spring 1:summer 2:fall 3:winter
	TimerStruct.WorldMonth = 0;
	TimerStruct.WorldDays = 1;
	TimerStruct.WorldHours = 10;
	TimerStruct.WorldMinute = 0.0f;
	NowDifficultEnum = EDifficultEnum::Easy;
	WhereOpen = EWhereOpen::Start;
	PlayerNumber = 1;
	EnemyTag = FName(TEXT("Barghest"));
	isStatus = false;
	Level = 1;

	//Debug
	/*MainMapPCStautus.SCoins = 3;
	MainMapPCStautus.HaveTito.Add(ETitoList::Kantei);
	MainMapPCStautus.HaveTito.Add(ETitoList::Ansatu);
	MainMapPCStautus.HaveTito.Add(ETitoList::Bouen);
	MainMapPCStautus.TitoPoint = 400;
	MainMapPCStautus.Magic.Add(FString("FireBall"), FMagicStatus());
	MainMapPCStautus.MaxHP = 1000;
	MainMapPCStautus.NowHP = 800;*/
	//MainMapPCStautus.Magic.Add(FString("Recovery"), FMagicStatus());
	/*MainMapPCStautus.CharacterName = FString(TEXT("oooo"));
	MainMapPCStautus.Speed = 10000;
	MainMapPCStautus.MaxHP = 1000;
	MainMapPCStautus.NowHP = 1000;
	MainMapPCStautus.MaxMP = 1000;
	MainMapPCStautus.NowMP = 1000;
	MainMapPCStautus.MaxSP = 1000;
	MainMapPCStautus.NowSP = 1000;
	MainMapPCStautus.NormalAttack = 1000;
	MainMapPCStautus.MagicAttack = 100;
	MainMapPCStautus.Magic.Add(FString("FireBall"), FMagicStatus());
	MainMapPCStautus.Magic.Add(FString("Recovery"), FMagicStatus());
	MainMapPCStautus.Magic.Add(FString("FIreStorm"), FMagicStatus());
	MainMapPCStautus.Skill.Add(FString("Appraisal"), FSkillStatus());
	*/
	SubPlayerStatus.SetNum(1);
	SubPlayerStatus[0].Magic.Add(FString("FireBall"), FMagicStatus());
	SubPlayerStatus[0].Skill.Add(FString("StrongAttack"), FSkillStatus());
	SubPlayerStatus[0].NowHP = 500;
	SubPlayerStatus[0].MaxHP = 1000;
	SubPlayerStatus[0].NowMP = 10;
	SubPlayerStatus[0].MaxMP = 109;
	SubPlayerStatus[0].NowSP = 50;
	SubPlayerStatus[0].MaxSP = 100;
	SubPlayerStatus[0].CharacterName = FString("noname");
	SubPlayerStatus[0].TitoPoint = 400;
	PlayerNumber = 1 + SubPlayerStatus.Num();
}

int32 URPGGameInstance::GetInt32Random(FRandomInt32 RandomList)
{
	return GetRandom<int32, FRandomInt32>(RandomList);
}

float URPGGameInstance::GetFloat32Random(FRandomFloat32 RandomList)
{
	return GetRandom<float, FRandomFloat32>(RandomList);
}

bool URPGGameInstance::MainSaveData(const FString saveName)
{
	AMainMapPC* mainPC = nullptr;
	mainPC = Cast<AMainMapPC>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	this->SaveData->TimerStruct = this->TimerStruct;
	this->SaveData->SaveMainMapPCStautus = this->MainMapPCStautus;
	this->SaveData->SaveMainMapPCStautus.PlayerTransform = mainPC->GetActorTransform();

	FString PathName = FString(TEXT("MainSaveData/"));
	PathName.Append(saveName);
	//save game
	if (UGameplayStatics::SaveGameToSlot(this->SaveData, PathName, 0))
	{
		//Save succeeded.
		return true;
	}
	else
	{
		return false;
	}
}

bool URPGGameInstance::SettingSaveData()
{
	if (this->SettingSave)
	{
		if (UGameplayStatics::SaveGameToSlot(this->SettingSave, "SettingData", 0))
		{
			if (!NowSaveData.IsEmpty())
			{
				//Save succeeded.
				return MainSaveData(NowSaveData);
			}
			else return false;
		}
		else return false;
	}
	else return false;
}

bool URPGGameInstance::LoadData(const FString loadName)
{
	NowSaveData = loadName;
	FString PathName = FString(TEXT("MainSaveData/"));
	PathName.Append(loadName);
	if (USaveData* LoadData = Cast<USaveData>(UGameplayStatics::LoadGameFromSlot(PathName, 0)))
	{
		//LoadData
		this->MainMapPCStautus = LoadData->SaveMainMapPCStautus;
		this->TimerStruct = LoadData->TimerStruct;
		return true;
	}
	else
	{
		return false;
	}
}

bool URPGGameInstance::UseSubPlayerItem(FText PlayerName, FItemStruct ItemStruct)
{
	for (auto& Status : this->SubPlayerStatus)
	{
		if (PlayerName.ToString().Equals(Status.CharacterName))
		{
			return UseItem<FMainMapNPCStautus&>(Status, ItemStruct);
		}
	}
	return false;
}

bool URPGGameInstance::UseMainPlayerItem(AMainMapPC* Status, FItemStruct ItemStruct)
{
	return UseItem<FMainMapPCStautus&>(Status->MainMapPCStautus, ItemStruct);
}

bool URPGGameInstance::AppendSubPlayerItem(FText PlayerName, TArray<FItemStruct> ItemStructs, FMassAndVolume MassAndVolume)
{
	for (auto& status : SubPlayerStatus)
	{
		if (PlayerName.ToString().Equals(status.CharacterName))
		{
			status.MassAndVolume = MassAndVolume;
			return AppendItems<FMainMapNPCStautus&>(status, ItemStructs);
		}
	}
	return false;
}

bool URPGGameInstance::AppendMainPlayerItem(AMainMapPC* Status, TArray<FItemStruct> ItemStructs, FMassAndVolume MassAndVolume)
{
	Status->MainMapPCStautus.MassAndVolume = MassAndVolume;
	return AppendItems<FMainMapPCStautus&>(Status->MainMapPCStautus, ItemStructs);
	return false;
}

bool URPGGameInstance::RemoveItem(FText PlayerName, FString Key, int32 Index)
{
	for (auto& Status : this->SubPlayerStatus)
	{
		if (PlayerName.ToString().Equals(Status.CharacterName))
		{
			FItemArray* Item = Status.Items.Find(Key);
			if (Item != nullptr)
			{
				Item->ItemStruct.RemoveAt(Index);
				if (Item->ItemStruct.Num() <= 0)
					Status.Items.Remove(Key);
				return true;
			}
			else
				return false;
		}
	}
	return false;
}

bool URPGGameInstance::GetShopItems(FString ShopKey, TMap<FString, FItemArray>& GetItems)
{
	TMap<FString, FItemArray> *items = ShopItemMap.Find(ShopKey);
	if (items)
	{
		GetItems = *items;
		return true;
	}
	return false;
}

void URPGGameInstance::AddShopItems(FString Name, FShopItemStruct ShopItemStruct, FItemStruct BaseItem)
{
	int32 Count = ShopItemStruct.ItemCount;
	Count += GetInt32Random(ShopItemStruct.AddRandomItemCount);
	for (int i = 0; i < Count; i++)
	{
		//
		FItemStruct AddItem = BaseItem;//アイテムのコピー
		AddItem.Quality = GetFloat32Random(ShopItemStruct.AddRandomQuality) + ShopItemStruct.BaseQuality;
		AddItem.MaxHP += GetInt32Random(ShopItemStruct.AddRandomMaxHP);
		AddItem.NowHP += GetInt32Random(ShopItemStruct.AddRandomNowHP);
		if (AddItem.NowHP > AddItem.MaxHP)
			AddItem.NowHP = AddItem.MaxHP;
		//
		TMap<FString, FItemArray>* ItemMap = ShopItemMap.Find(Name);
		if (!ItemMap)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("test"));
			TMap<FString, FItemArray> item;
			FItemArray localItems = FItemArray(AddItem);
			item.Add(AddItem.Key, localItems);
			ShopItemMap.Add(Name, item);
		}
		else
		{
			FItemArray* ItemArray = ItemMap->Find(AddItem.Key);
			if (ItemArray)
			{
				ItemArray->ItemStruct.Add(AddItem);
			}
			else
			{
				FItemArray localItems = FItemArray(AddItem);
				ItemMap->Add(AddItem.Key, localItems);
			}
		}
	}
}

bool URPGGameInstance::SetSubPlayerClothse(FText PlayerName, EClothesPart ClothesPart, ERightOrLeft RightOrLeft, EFingerKinds FingerKinds, FClothesStruct ClothseStruct)
{
	for (auto& Status : this->SubPlayerStatus)
	{
		if (PlayerName.ToString().Equals(Status.CharacterName))
		{
			TTuple<TMap<FString, int32>, TMap<FString, float>> tuple = GetBaseStatus<FMainMapNPCStautus>(Status);
			SetClothse<FMainMapNPCStautus&>(Status, ClothesPart, RightOrLeft, FingerKinds, ClothseStruct);
			Status = GetChangeStatus<FMainMapNPCStautus>(Status, tuple.Get<TMap<FString, int32>>(), tuple.Get<TMap<FString, float>>());
		}
	}
	return true;
}

bool URPGGameInstance::SetMainPlayerClothse(AMainMapPC* Status, EClothesPart ClothesPart, ERightOrLeft RightOrLeft, EFingerKinds FingerKinds, FClothesStruct ClothseStruct)
{
	TTuple<TMap<FString, int32>, TMap<FString, float>> tuple = GetBaseStatus<FMainMapPCStautus>(Status->MainMapPCStautus);
	SetClothse<FMainMapPCStautus&>(Status->MainMapPCStautus, ClothesPart, RightOrLeft, FingerKinds, ClothseStruct);
	Status->MainMapPCStautus = GetChangeStatus<FMainMapPCStautus>(Status->MainMapPCStautus, tuple.Get<TMap<FString, int32>>(), tuple.Get<TMap<FString, float>>());
	return true;
}

bool URPGGameInstance::SubPlayerRemovePartClothes(FText PlayerName, EClothesPart ClothesPart, ERightOrLeft RightOrLeft, EFingerKinds FingerKinds)
{
	bool isRemove;
	for (auto& Status : this->SubPlayerStatus)
	{
		if (PlayerName.ToString().Equals(Status.CharacterName))
		{
			TTuple<TMap<FString, int32>, TMap<FString, float>> tuple = GetBaseStatus<FMainMapNPCStautus>(Status);
			isRemove = RemovePartClothes<FMainMapNPCStautus&>(Status, ClothesPart, RightOrLeft, FingerKinds);
			Status = GetChangeStatus<FMainMapNPCStautus>(Status, tuple.Get<TMap<FString, int32>>(), tuple.Get<TMap<FString, float>>());

		}
	}
	return isRemove;
}

bool URPGGameInstance::MainPlayerRemovePartClothes(AMainMapPC* Status, EClothesPart ClothesPart, ERightOrLeft RightOrLeft, EFingerKinds FingerKinds)
{
	bool isRemove = false;
	TTuple<TMap<FString, int32>, TMap<FString, float>> tuple = GetBaseStatus<FMainMapPCStautus>(Status->MainMapPCStautus);
	isRemove = RemovePartClothes<FMainMapPCStautus&>(Status->MainMapPCStautus, ClothesPart, RightOrLeft, FingerKinds);
	Status->MainMapPCStautus = GetChangeStatus<FMainMapPCStautus>(Status->MainMapPCStautus, tuple.Get<TMap<FString, int32>>(), tuple.Get<TMap<FString, float>>());
	return isRemove;
}

bool URPGGameInstance::RemoveClothse(FText PlayerName, FString Key, int32 Index)
{
	for (auto& Status : this->SubPlayerStatus)
	{
		if (PlayerName.ToString().Equals(Status.CharacterName))
		{
			FClothesArray* Clothse = Status.HaveClothes.Find(Key);
			if (Clothse != nullptr)
			{
				Clothse->ClothesStruct.RemoveAt(Index);
				if (Clothse->ClothesStruct.Num() <= 0)
					Status.Items.Remove(Key);
				return true;
			}
			else
				return false;
		}
	}
	return false;
}

FClothesStruct URPGGameInstance::SetRightOrLeft(FText PlayerName, FString Key, int32 Index, ERightOrLeft RightOrLeft, EFingerKinds FingerKinds)
{
	for (auto& Status : this->SubPlayerStatus)
	{
		if (PlayerName.ToString().Equals(Status.CharacterName))
		{
			FOtherClothes OtherClothes = FOtherClothes();
			FClothesArray* ClothesArray = Status.HaveClothes.Find(Key);
			if (ClothesArray)
			{
				if (ClothesArray->ClothesStruct.IsValidIndex(Index))
				{
					for (auto& LocalClothesPart : ClothesArray->ClothesStruct[Index].ClothesParts)
					{
						if (INDEX_NONE == OtherClothes.OtherClothesPart.Find(LocalClothesPart.ClothesPart))
						{

							if (ClothesArray->ClothesStruct[Index].ClothesParts.Num() > 1)
							{
								if (LocalClothesPart.ClothesPart != EClothesPart::Finger)
								{
									LocalClothesPart.RightOrLeft = ERightOrLeft::Right;
									ClothesArray->ClothesStruct[Index].ClothesParts.Add(FClothesParts(LocalClothesPart.ClothesPart, ERightOrLeft::Left));
								}
							}
							else
							{
								if (LocalClothesPart.ClothesPart == EClothesPart::Finger)
								{
									LocalClothesPart.FingerKinds = FingerKinds;
									LocalClothesPart.RightOrLeft = RightOrLeft;
								}
								else
								{
									LocalClothesPart.RightOrLeft = RightOrLeft;
								}
							}
						}
					}
				}
			}
			return ClothesArray->ClothesStruct[Index];
		}
	}
	return FClothesStruct();
}

TArray<FClothesParts> URPGGameInstance::GetFClothesParts(ERightOrLeft RightOrLeft, EFingerKinds FingerKinds, TArray<FClothesParts> ClothesParts)
{
	FOtherClothes OtherClothes = FOtherClothes();
	for (auto LocalClothesPart : ClothesParts)
	{
		if (!OtherClothes.OtherClothesPart.Find(LocalClothesPart.ClothesPart))
		{
			if (LocalClothesPart.ClothesPart == EClothesPart::Finger)
			{
				LocalClothesPart.FingerKinds = FingerKinds;
				LocalClothesPart.RightOrLeft = RightOrLeft;
			}
			else
			{
				LocalClothesPart.RightOrLeft = RightOrLeft;
			}
		}
	}
	return ClothesParts;
}

void URPGGameInstance::GetMainPlayerAddAndMultip(FMainMapPCStautus Status, TMap<FString, int32>& AdderStatus, TMap<FString, float>& MultipStatus)
{
	TTuple<TMap<FString, int32>, TMap<FString, float>> tuple = GetAddAndMultip<FMainMapPCStautus>(Status);
	AdderStatus = tuple.Get<TMap<FString, int32>>();
	MultipStatus = tuple.Get<TMap<FString, float>>();
}

void URPGGameInstance::GetSubPlayerAddAndMultip(FMainMapNPCStautus Status, TMap<FString, int32>& AdderStatus, TMap<FString, float>& MultipStatus)
{
	TTuple<TMap<FString, int32>, TMap<FString, float>> tuple = GetAddAndMultip<FMainMapNPCStautus>(Status);
	AdderStatus = tuple.Get<TMap<FString, int32>>();
	MultipStatus = tuple.Get<TMap<FString, float>>();
}

bool URPGGameInstance::SleepRecovery(AMainMapPC* Status, int32 hours, int32 Min)
{
	SleepRecovery<FMainMapPCStautus&>(Status->MainMapPCStautus, hours, Min);
	for (auto& status : this->SubPlayerStatus)
	{
		return SleepRecovery<FMainMapNPCStautus&>(status, hours, Min);
	}
	return true;
}

bool URPGGameInstance::MainPlayerCalcuMassAndVolume(AMainMapPC* Status)
{
	CalcuMassAndVolume<FMainMapPCStautus&>(Status->MainMapPCStautus);
	Status->MainMapPCStautus.MassAndVolume.NowMass += Status->MainMapPCStautus.BCoins * 2;
	Status->MainMapPCStautus.MassAndVolume.NowMass += Status->MainMapPCStautus.SCoins * 5;
	Status->MainMapPCStautus.MassAndVolume.NowMass += Status->MainMapPCStautus.GCoins * 7;
	Status->MainMapPCStautus.MassAndVolume.NowMass += Status->MainMapPCStautus.PCoins * 10;
	Status->MainMapPCStautus.MassAndVolume.NowVolume += Status->MainMapPCStautus.BCoins * 2;
	Status->MainMapPCStautus.MassAndVolume.NowVolume += Status->MainMapPCStautus.SCoins * 2;
	Status->MainMapPCStautus.MassAndVolume.NowVolume += Status->MainMapPCStautus.GCoins * 2;
	Status->MainMapPCStautus.MassAndVolume.NowVolume += Status->MainMapPCStautus.PCoins * 2;
	return true;
}

bool URPGGameInstance::SubPlayerCalcuMassAndVolume()
{
	for (auto& Status : SubPlayerStatus)
	{
		CalcuMassAndVolume<FMainMapNPCStautus&>(Status);
	}
	return true;
}

//フラグを立てる
//Names[0]:名前空間
//Names[1]:イベント名前
//Names[2]:入れるフラグ
void URPGGameInstance::UpdataFlag(TArray<FString> Names)
{
	if (Names.Num() < 3)
		return;
	EEventProgress Progress;
	if (Names[2] == FString("Yet"))
		Progress = EEventProgress::Yet;
	else if (Names[2] == FString("Conti"))
		Progress = EEventProgress::Continue;
	else if (Names[2] == FString("Comp"))
		Progress = EEventProgress::Completion;

	FEventsStruct* ref1 = this->EventList.Find(FName(Names[0]));
	if (ref1 == nullptr)
		return;
	FEventState* ref2 = ref1->EventMaps.Find(FName(Names[1]));
	if (ref2 == nullptr)
		return;
	ref2->EventProgress = Progress;
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("test"));
}

//フラグが等しいか確認
//Names[0]:名前空間
//Names[1]:イベント名前
//Names[2]:比較するフラグ

bool URPGGameInstance::CheckFlag(TArray<FString> Names)
{
	if (Names.Num() < 3)
		return false;
	EEventProgress Progress;
	if (Names[2] == FString("Yet"))
		Progress = EEventProgress::Yet;
	else if (Names[2] == FString("Conti"))
		Progress = EEventProgress::Continue;
	else if (Names[2] == FString("Comp"))
		Progress = EEventProgress::Completion;

	FEventsStruct ref1 = this->EventList.FindRef(FName(Names[0]));
	FEventState ref2 = ref1.EventMaps.FindRef(FName(Names[1]));
	if (ref2.EventProgress == Progress)
		return true;
	else
		return false;
}

URPGGameInstance* URPGGameInstance::GetGameInstance()
{
	URPGGameInstance* instance = nullptr;
	if (GEngine) {
		FWorldContext* context = GEngine->GetWorldContextFromGameViewport(GEngine->GameViewport);
		instance = Cast<URPGGameInstance>(context->OwningGameInstance);
	}
	return instance;
}

void URPGGameInstance::Init()
{
	Super::Init();
	NowSaveData = TEXT("");
	//setting dataがあるか確認する。ない場合は作成する。
	if (USettingSave* LoadGame = Cast<USettingSave>(UGameplayStatics::LoadGameFromSlot("SettingData", 0))) {
		SettingSave = LoadGame;
	}
	else
	{
		if (USettingSave* SaveSettingGame = Cast<USettingSave>(UGameplayStatics::CreateSaveGameObject(USettingSave::StaticClass()))) {
			if (UGameplayStatics::SaveGameToSlot(SaveSettingGame, "SettingData", 0))
			{
				//Save succeeded.
				SettingSave = SaveSettingGame;
			}
		}
	}
	//create main save object
	SaveData = Cast<USaveData>(UGameplayStatics::CreateSaveGameObject(USaveData::StaticClass()));
}

//do not know
TArray<FString> URPGGameInstance::GetAllFilesInDirectory(const FString FullPath)
{
	bool fullPath = false;
	FString directory = FullPath;
	directory.Append(TEXT("SaveGames/MainSaveData"));
	FString onlyFilesStartingWith = TEXT("");
	FString onlyFilesWithExtension = TEXT("sav");

	// Get all files in directory
	TArray<FString> directoriesToSkip;
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	FLocalTimestampDirectoryVisitor Visitor(PlatformFile, directoriesToSkip, directoriesToSkip, false);
	PlatformFile.IterateDirectory(*directory, Visitor);
	TArray<FString> files;

	for (TMap<FString, FDateTime>::TIterator TimestampIt(Visitor.FileTimes); TimestampIt; ++TimestampIt)
	{
		const FString filePath = TimestampIt.Key();
		const FString fileName = FPaths::GetCleanFilename(filePath);
		bool shouldAddFile = true;

		// Check if filename starts with required characters
		if (!onlyFilesStartingWith.IsEmpty())
		{
			const FString left = fileName.Left(onlyFilesStartingWith.Len());

			if (!(fileName.Left(onlyFilesStartingWith.Len()).Equals(onlyFilesStartingWith)))
				shouldAddFile = false;
		}

		// Check if file extension is required characters
		if (!onlyFilesWithExtension.IsEmpty())
		{
			if (!(FPaths::GetExtension(fileName, false).Equals(onlyFilesWithExtension, ESearchCase::IgnoreCase)))
				shouldAddFile = false;
		}

		// Add full path to results
		if (shouldAddFile)
		{
			files.Add(fullPath ? filePath : fileName);
		}
	}

	return files;
}
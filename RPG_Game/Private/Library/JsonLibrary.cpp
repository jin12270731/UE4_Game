// Fill out your copyright notice in the Description page of Project Settings.

#include "Library/JsonLibrary.h"
#include "JsonUtilities/Public/JsonUtilities.h"
#include "JsonObjectConverter.h"
#include "../Public/RPGGameInstance.h"
#include "Runtime/Json/Public/Serialization/JsonReader.h"

//static const FString RootName("InventoryObject");
static const FString WritePath(FPaths::ProjectSavedDir() / "JsonData");
static const FString FileName("GameInstJsonData.json");
static const FString FilePathFull(WritePath / FileName);

bool UJsonLibrary::WriteGameinstanceToJsonFile(const URPGGameInstance* GameIns)
{
	JsonObjectPtr JsonRootObject = MakeShareable(new FJsonObject);

	JsonObjectPtr MainCharacterJsonObj = FJsonObjectConverter::UStructToJsonObject(GameIns->MainMapPCStautus);
	JsonObjectPtr TimerJsonObj = FJsonObjectConverter::UStructToJsonObject(GameIns->TimerStruct);
	if (MainCharacterJsonObj.IsValid() && TimerJsonObj.IsValid())
	{

		//�Q�[���C���X�^���X�̃f�[�^��1��JSON�ɓ����
		JsonRootObject->SetObjectField("MainCharacter", MainCharacterJsonObj);
		JsonRootObject->SetObjectField("Timer", TimerJsonObj);
		//UENUM��Enum��FStrung�ɕϊ����Ă���Z�b�g����
		UEnum* const Enum = FindObject<UEnum>(ANY_PACKAGE, TEXT("EDifficultEnum"));
		if (Enum)
			JsonRootObject->SetStringField("NowDifficultEnum", Enum->GetNameStringByIndex(static_cast<int32>(GameIns->NowDifficultEnum)));

		// FString��Json���������ނ��߂�Writer���쐬
		FString OutPutString;
		TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutPutString);
		// Json�I�u�W�F�N�g��FString�ɏ�������
		FJsonSerializer::Serialize(JsonRootObject.ToSharedRef(), Writer);
		if (FFileHelper::SaveStringToFile(OutPutString, *FilePathFull))
			return true;
		else
			return false;
	}
	else
		return false;
}


bool UJsonLibrary::GetJsonFileData(FString& GetString, TArray<FString> SarchStrings)
{
	FString RawData;

	if (FFileHelper::LoadFileToString(RawData, *FilePathFull))
	{
		// FJsonObject(Json�f�[�^�̓��ꕨ)���쐬
		JsonObjectPtr JsonRootObject = MakeShareable(new FJsonObject());
		// FString����Json��ǂݍ��ނ��߂�Reader���쐬
		TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(RawData);
		// Json�����񂩂�Json�I�u�W�F�N�g�ɓǂݍ���
		if (FJsonSerializer::Deserialize(JsonReader, JsonRootObject))
		{
			if (SarchStrings.Num() <= 0)
				return false;
			const JsonObjectPtr* LocalPtr;
			JsonObjectPtr RootPtr = JsonRootObject;
			for (int i = 0; i < SarchStrings.Num(); i++)
			{
				if (!RootPtr->TryGetObjectField(SarchStrings[i], LocalPtr))
					break;
				else
					RootPtr = *LocalPtr;
			}
			if (RootPtr->TryGetStringField(SarchStrings[SarchStrings.Num() - 1], GetString))
				return true;
			else
			{
				//�z��̏ꍇ
				TArray <FString> GetStrings;
				if (RootPtr->TryGetStringArrayField(SarchStrings[SarchStrings.Num() - 2], GetStrings))
				{
					int32 FindIndex = GetStrings.Find(SarchStrings[SarchStrings.Num() - 1]);
					if (INDEX_NONE != FindIndex)
					{
						GetString = GetStrings[FindIndex];
					}
					else
					{
						GetString = FString("");
					}
					return true;
				}
				else//
				{
					const TArray < TSharedPtr <FJsonValue > >* outArray;
					if (RootPtr->TryGetArrayField(SarchStrings[SarchStrings.Num() - 2], outArray))
					{
						for (auto array : *outArray)
						{
							auto serverObj = array->AsObject();
							if (serverObj.IsValid())
							{
								if (serverObj->TryGetStringField(SarchStrings[SarchStrings.Num() - 1], GetString))
								{
									//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("test"));
									return true;
								}
							}
						}

					}
				}
			}
		}
	}
	return false;
}
//

bool UJsonLibrary::WriteJsonFile(FString WriteString, TArray<FString> WriteStrings, bool isCoin)
{
	FString RawData;

	if (FFileHelper::LoadFileToString(RawData, *FilePathFull))
	{
		// FJsonObject(Json�f�[�^�̓��ꕨ)���쐬
		JsonObjectPtr JsonRootObject = MakeShareable(new FJsonObject());

		// FString����Json��ǂݍ��ނ��߂�Reader���쐬
		TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(RawData);
		// Json�����񂩂�Json�I�u�W�F�N�g�ɓǂݍ���
		if (FJsonSerializer::Deserialize(JsonReader, JsonRootObject))
		{
			if (WriteStrings.Num() <= 0)
				return false;
			const JsonObjectPtr* LocalPtr;
			JsonObjectPtr RootPtr = JsonRootObject;
			if (isCoin)//�d�݂��������ނƂ��͓��݂̑����ɂȂ��Ă��邽�ߗ��ւ����Ă�����
			{
				const TArray<FString> coinName = { "bCoins", "sCoins", "gCoins", "pCoins" };
				TArray<int32> coins;
				int32 bronze = FCString::Atoi(*WriteString);
				int32 sirver = bronze / 10;
				bronze -= (sirver * 10);
				int32 gold = sirver / 10;
				sirver -= gold * 10;
				int32 platinum = gold / 10;
				gold -= platinum * 10;
				coins.Add(bronze);
				coins.Add(sirver);
				coins.Add(gold);
				coins.Add(platinum);
				for (int i = 0; i < coinName.Num(); i++)
				{
					WriteStrings[WriteStrings.Num() - 1] = coinName[i];
					for (int j = 0; j < WriteStrings.Num(); j++)
					{
						if (!RootPtr->TryGetObjectField(WriteStrings[j], LocalPtr))
							break;
						else
							RootPtr = *LocalPtr;
					}
					RootPtr->SetNumberField(WriteStrings[WriteStrings.Num() - 1], coins[i]);
				}
			}
			else//�d�݈ȊO
			{
				for (int i = 0; i < WriteStrings.Num(); i++)
				{
					if (!RootPtr->TryGetObjectField(WriteStrings[i], LocalPtr))
						break;
					else
						RootPtr = *LocalPtr;
				}
				RootPtr->SetStringField(WriteStrings[WriteStrings.Num() - 1], WriteString);
			}

			// FString��Json���������ނ��߂�Writer���쐬
			FString OutPutString;
			TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutPutString);
			// Json�I�u�W�F�N�g��FString�ɏ�������
			FJsonSerializer::Serialize(JsonRootObject.ToSharedRef(), Writer);
			if (FFileHelper::SaveStringToFile(OutPutString, *FilePathFull))
			{
				URPGGameInstance* gameinstance = URPGGameInstance::GetGameInstance();
				if (gameinstance)
				{
					JsonFileToWriteGameinstance(gameinstance);
					return true;
				}
			}
		}
	}
	return false;
}

bool UJsonLibrary::JsonFileToWriteGameinstance(URPGGameInstance* GameIns)
{
	FString RawData;

	bool bLoadedFile = FFileHelper::LoadFileToString(RawData, *FilePathFull);

	if (bLoadedFile)
	{

		// FJsonObject(Json�f�[�^�̓��ꕨ)���쐬
		JsonObjectPtr JsonRootObject = MakeShareable(new FJsonObject());

		// FString����Json��ǂݍ��ނ��߂�Reader���쐬
		TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(RawData);

		// Json�����񂩂�Json�I�u�W�F�N�g�ɓǂݍ���
		if (FJsonSerializer::Deserialize(JsonReader, JsonRootObject))
		{
			//Json�t�@�C������f�[�^���擾���āAJson�I�u�W�F�N�g�Ƃ��đ������B
			JsonObjectPtr JOMainCharacter = JsonRootObject->GetObjectField("MainCharacter");
			JsonObjectPtr JOTimer = JsonRootObject->GetObjectField("Timer");

			//Json�t�@�C������f�[�^���擾���āAFString�Ƃ��đ������B
			FString JSNowDifficultEnum = JsonRootObject->GetStringField("NowDifficultEnum");

			//Json�I�u�W�F�N�g�̍\���̂��Q�[���C���X�^���X�̍\���̂ɑ������B
			bool flag1 = FJsonObjectConverter::JsonObjectToUStruct<FMainMapPCStautus>(JOMainCharacter.ToSharedRef(), &(GameIns->MainMapPCStautus), 0, 0);
			bool flag2 = FJsonObjectConverter::JsonObjectToUStruct<FTimerStruct>(JOTimer.ToSharedRef(), &(GameIns->TimerStruct), 0, 0);

			//FString����񋓌^�ɕϊ����āA�Q�[���C���X�^���X�ɑ������B
			UEnum* const Enum1 = FindObject<UEnum>(ANY_PACKAGE, *FString("EDifficultEnum"));
			if (Enum1)
				GameIns->NowDifficultEnum = static_cast<EDifficultEnum>(Enum1->GetValueByName(FName(JSNowDifficultEnum)));

			if (GEngine && flag1 && flag2 && Enum1)
			{
				GEngine->GetWorldContexts();
				AMainMapPC* MainMapPC = Cast<AMainMapPC>(UGameplayStatics::GetPlayerPawn(GEngine->GetWorldContextFromGameViewport(GEngine->GameViewport)->World(), 0));
				if (MainMapPC)
				{
					MainMapPC->SetStatus();
				}
				return true;
			}
			else
				return false;
		}
	}
	return false;
}
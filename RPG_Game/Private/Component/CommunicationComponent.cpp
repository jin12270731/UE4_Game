// Fill out your copyright notice in the Description page of Project Settings.



#include "Component/CommunicationComponent.h"

// Sets default values for this component's properties
//UCommunicationComponent::UCommunicationComponent()
//{
//	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
//	// off to improve performance if you don't need them.
//	PrimaryComponentTick.bCanEverTick = false;
//
//	// ...
//}


FString UCommunicationComponent::GetKey(FString CountString, const FString EventName)
{
	if (MessageCounts.Num() < 3)
		return FString();
	//make Count_EventName_count_
	CountString.Append(FString("_"));
	CountString.Append(EventName);
	CountString.Append(FString("_"));
	CountString.Append(FString::FromInt(MessageCounts[0]));

	if (MessageCounts[1] != -1)
	{
		CountString.Append(FString("_"));
		CountString.Append(FString::FromInt(MessageCounts[1]));
		CountString.Append(FString("_"));
		CountString.Append(FString::FromInt(MessageCounts[2]));
	}
	return CountString;
}


void UCommunicationComponent::JumpMessage(FString ID)
{
	FString r1, r2, l1, l2;
	TArray<int32> count;
	if (ID.Split(FString("_"), &l1, &r1))
	{

		if (r1.Split(FString("_"), &l2, &r2))
		{
			count.Add(FCString::Atoi(*l1));
			count.Add(FCString::Atoi(*l2));
			count.Add(FCString::Atoi(*r2) - 1);
			BranchFlag = true;
		}
		else
		{
			count.Add(FCString::Atoi(*l1));
			count.Add(FCString::Atoi(*r1));
			count.Add(-1);
			BranchFlag = true;
		}
	}
	else
	{
		count.Add(FCString::Atoi(*ID) - 1);
		count.Add(-1);
		count.Add(-1);
		BranchFlag = false;
	}
	if (count.Num() == 3)
		MessageCounts = count;
	else
	{
		TArray<int32> count2;
		count2.Add(-1);
		count2.Add(-1);
		count2.Add(-1);
		MessageCounts = count2;
		BranchFlag = false;
	}
}

void UCommunicationComponent::AddMessageCounts()
{
	if (MessageCounts.Num() >= 3)
	{
		if (!BranchFlag)
			MessageCounts[0]++;
		else
			MessageCounts[2]++;

		/*if (MessageCounts[1] != -1) {
			MessageCounts[2]++;
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("test"));
		}*/
	}
}




void UCommunicationComponent::GetMessage(FString BaseString, FString& Name, FString& Text, TArray<FString>& Texts, bool& Once)
{
	FString Left_1;
	FString Right_1, Right_2;
	TArray<int32> counts;
	BaseString.Split(FString("\r\n"), &Left_1, &Right_1);
	//set up
	Once = false;
	Name = Left_1;
	//if option?
	FString s;
	if (!Right_1.Split(FString("%"), &s, &Right_2))
	{
		Text = Right_1;
		return;
	}
	FString option, optionString;
	Right_2.Split(FString("\r\n"), &option, &optionString);
	//option process
	if (option.Equals(FString("Goto")))
	{
		FString r, l;
		optionString.Split(FString("\r\n"), &l, &r);
		JumpMessage(l);
		Text = r;
	}
	else if (option.Equals(FString("FlagUp")))
	{
		FString r1, l1, r2, l2, r3, l3;
		TArray<FString> strings;
		optionString.Split(FString("\r\n"), &l1, &r1);
		l1.Split(FString("_"), &l2, &r2);
		r2.Split(FString("_"), &l3, &r3);
		strings.Add(l2);
		strings.Add(l3);
		strings.Add(r3);
		URPGGameInstance* gameinstance = URPGGameInstance::GetGameInstance();
		if (gameinstance)
		{
			gameinstance->UpdataFlag(strings);
			Text = r1;
		}
	}
	else if (option.Equals(FString("End")))
	{
		Text = Right_1;
		EndFlag = true;
	}
	else if (option.Equals(FString("Select")))
	{
		FString l;
		TArray<FString> texts;
		while (optionString.Split(FString("\r\n"), &l, &optionString))
		{
			texts.Add(l);
		}
		texts.Add(optionString);
		Text = Right_1;
		Texts = texts;
		SelectFlag = true;
	}
	else if (option.Equals(FString("CheckFlag")))
	{
		FString r1, l1, r2, l2, r3, l3, TrueEvent, FalseEvent;
		TArray<FString> strings;
		optionString.Split(FString("\r\n"), &l1, &TrueEvent);
		l1.Split(FString("_"), &l2, &r2);
		r2.Split(FString("_"), &l3, &r3);
		strings.Add(l2);
		strings.Add(l3);
		strings.Add(r3);
		TrueEvent.Split(FString("\r\n"), &TrueEvent, &FalseEvent);
		TrueEvent.Split(FString("\r\n"), &TrueEvent, &FalseEvent);
		URPGGameInstance* gameinstance = URPGGameInstance::GetGameInstance();
		if (gameinstance)
		{
			if (gameinstance->CheckFlag(strings)) {
				JumpMessage(TrueEvent);
			}
			else {
				JumpMessage(FalseEvent);
			}
		}
		Once = true;
	}
	else if (option.Equals(FString("CheckStatus")))
	{
		FString r1, l1, r2, l2, TrueEvent, FalseEvent;
		TArray<FString> JsonStrings;
		TArray<FString> JsonCompare;
		optionString.Split(FString("\r\n"), &l1, &r1);
		r1.Split(FString("\r\n"), &l2, &r2);

		//�擾����X�e�[�^�X�����擾����
		FString LocalStr;
		while (l1.Split(FString("_"), &LocalStr, &l1))
		{
			JsonStrings.Add(LocalStr);
		}
		JsonStrings.Add(l1);

		//�X�e�[�^�X�Ɣ�r����^����щ��Z�q�A�ϐ����擾����
		while (l2.Split(FString("_"), &LocalStr, &l2))
		{
			JsonCompare.Add(LocalStr);
		}
		JsonCompare.Add(l2);

		//true����false���ɔ�ԏꏊ���擾����
		r2.Split(FString("\r\n"), &TrueEvent, &FalseEvent);

		//PlayerPawn���擾����
		AMainMapPC* MainMapPC = Cast<AMainMapPC>(UGameplayStatics::GetPlayerPawn(this, 0));
		//�Q�[���C���X�^���X���擾����B
		URPGGameInstance* gameinstance = URPGGameInstance::GetGameInstance();
		if (gameinstance)
		{
			//MainMapPlayerPawn�̍\���̂��Q�[���C���X�^���X�̍\���̂ɑ������B
			if (MainMapPC)
				gameinstance->MainMapPCStautus = MainMapPC->MainMapPCStautus;

			//Json�t�@�C���Ɍ��݂�Gameinstance�̃f�[�^����������
			UJsonLibrary::WriteGameinstanceToJsonFile(gameinstance);
		}

		//true�C�x���g��false�C�x���g���𔻒f����
		FString GetString;
		if (UJsonLibrary::GetJsonFileData(GetString, JsonStrings))//�w�肵��Json�f�[�^�ɓ����Ă���f�[�^���擾����
		{

			if (JsonCompare.Num() >= 3)
			{
				int32 BronzeCoins = -1;
				if (JsonStrings[1].Equals(FString("bCoins")) || JsonStrings[1].Equals(FString("sCoins")) || JsonStrings[1].Equals(FString("gCoins")) || JsonStrings[1].Equals(FString("pCoins")))
				{
					//�d�݂��r����Ƃ��͓��݂���ɂ���
					BronzeCoins = 0;
					FString String;
					TArray<FString> str;
					//���L���Ă���d�݂𓺉݂ɂ���
					str.Add(JsonStrings[0]);
					str.Add(FString("bCoins"));
					if (UJsonLibrary::GetJsonFileData(String, str))
						BronzeCoins += FCString::Atoi(*String);
					str.Reserve(1);
					str.Add(FString("sCoins"));
					if (UJsonLibrary::GetJsonFileData(String, str))
						BronzeCoins += FCString::Atoi(*String) * 10;
					str.Reserve(1);
					str.Add(FString("gCoins"));
					if (UJsonLibrary::GetJsonFileData(String, str))
						BronzeCoins += FCString::Atoi(*String) * 100;
					str.Reserve(1);
					str.Add(FString("pCoins"));
					if (UJsonLibrary::GetJsonFileData(String, str))
						BronzeCoins += FCString::Atoi(*String) * 1000;
					//��r����d�݂𓺉݂ɂ���
					if (JsonStrings[1].Equals(FString("sCoins")))
						JsonCompare[2].Append(FString("0"));
					else if (JsonStrings[1].Equals(FString("gCoins")))
						JsonCompare[2].Append(FString("00"));
					else if (JsonStrings[1].Equals(FString("pCoins")))
						JsonCompare[2].Append(FString("000"));
				}
				bool Result = false;
				if (JsonCompare[0].Equals("int"))
				{
					//�d�݂��r����ꍇ��BrpnzeCoins��������B�d�݂ł͂Ȃ��Ƃ���Json����擾�����l��������B
					int32 Value = (BronzeCoins == -1) ? FCString::Atoi(*GetString) : BronzeCoins;
					int32 Constant = FCString::Atoi(*JsonCompare[2]);
					Result = GetResultCompare<int32>(JsonCompare[1], Value, Constant);
				}
				else if (JsonCompare[0].Equals("float"))
				{
					float Value = FCString::Atof(*GetString);
					float Constant = FCString::Atof(*JsonCompare[2]);
					Result = GetResultCompare<float>(JsonCompare[1], Value, Constant);
				}
				else if (JsonCompare[0].Equals("string"))
				{
					Result = GetResultCompareString(JsonCompare[1], GetString, JsonCompare[2]);
				}
				if (Result)
					JumpMessage(TrueEvent);
				else
					JumpMessage(FalseEvent);
			}
		}
		Once = true;

	}
	else if (option.Equals(FString("ChangeStatus")))
	{
		FString r1, l1, Event, l2;
		optionString.Split(FString("\r\n"), &l1, &r1);
		r1.Split(FString("\r\n"), &l2, &Event);
		TArray<FString> JsonStrings;
		TArray<FString> Calculations;

		//���Z�����������Ȃ�Json�f�[�^���擾����B
		FString LocalStr;
		while (l1.Split(FString("_"), &LocalStr, &l1))
		{
			JsonStrings.Add(LocalStr);
		}
		JsonStrings.Add(l1);

		//�X�e�[�^�X�ɉ��Z��������^�A���Z���e�A�l���擾����B
		while (l2.Split(FString("_"), &LocalStr, &l2))
		{
			Calculations.Add(LocalStr);
		}
		Calculations.Add(l2);

		//PlayerPawn���擾����
		AMainMapPC* MainMapPC = Cast<AMainMapPC>(UGameplayStatics::GetPlayerPawn(this, 0));
		//�Q�[���C���X�^���X���擾����B
		URPGGameInstance* gameinstance = URPGGameInstance::GetGameInstance();
		if (gameinstance)
		{
			//MainMapPlayerPawn�̍\���̂��Q�[���C���X�^���X�̍\���̂ɑ������B
			if (MainMapPC)
				gameinstance->MainMapPCStautus = MainMapPC->MainMapPCStautus;

			//Json�t�@�C���Ɍ��݂�Gameinstance�̃f�[�^����������
			UJsonLibrary::WriteGameinstanceToJsonFile(gameinstance);
		}

		//�w�肵���f�[�^�Ɏw�肵�����Z�������Ȃ��B
		FString GetString, ResultString;
		if (UJsonLibrary::GetJsonFileData(GetString, JsonStrings))
		{
			int32 BronzeCoins = -1;
			if (JsonStrings[1].Equals(FString("bCoins")) || JsonStrings[1].Equals(FString("sCoins")) || JsonStrings[1].Equals(FString("gCoins")) || JsonStrings[1].Equals(FString("pCoins")))
			{
				//�d�݂��r����Ƃ��͓��݂���ɂ���
				BronzeCoins = 0;
				FString String;
				TArray<FString> str;
				//���L���Ă���d�݂𓺉݂ɂ���
				str.Add(JsonStrings[0]);
				str.Add(FString("bCoins"));
				if (UJsonLibrary::GetJsonFileData(String, str))
					BronzeCoins += FCString::Atoi(*String);
				str.Reserve(1);
				str.Add(FString("sCoins"));
				if (UJsonLibrary::GetJsonFileData(String, str))
					BronzeCoins += FCString::Atoi(*String) * 10;
				str.Reserve(1);
				str.Add(FString("gCoins"));
				if (UJsonLibrary::GetJsonFileData(String, str))
					BronzeCoins += FCString::Atoi(*String) * 100;
				str.Reserve(1);
				str.Add(FString("pCoins"));
				if (UJsonLibrary::GetJsonFileData(String, str))
					BronzeCoins += FCString::Atoi(*String) * 1000;
				//��r����d�݂𓺉݂ɂ���
				if (JsonStrings[1].Equals(FString("sCoins")))
					Calculations[2].Append(FString("0"));
				else if (JsonStrings[1].Equals(FString("gCoins")))
					Calculations[2].Append(FString("00"));
				else if (JsonStrings[1].Equals(FString("pCoins")))
					Calculations[2].Append(FString("000"));
			}
			if (Calculations[0].Equals("int"))
			{
				//�d�݂��r����ꍇ��BrpnzeCoins��������B�d�݂ł͂Ȃ��Ƃ���Json����擾�����l��������B
				int32 Value = (BronzeCoins == -1) ? FCString::Atoi(*GetString) : BronzeCoins;
				int32 Constant = FCString::Atoi(*Calculations[2]);
				ResultString = FString::FromInt(GetResultCalculations<int32>(Calculations[1], Value, Constant));
				//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, ResultString);
			}
			else if (Calculations[0].Equals("float"))
			{
				float Value = FCString::Atof(*GetString);
				float Constant = FCString::Atof(*Calculations[2]);
				ResultString = FString::SanitizeFloat(GetResultCalculations<float>(Calculations[1], Value, Constant));
			}
			else if (Calculations[0].Equals("string"))
			{
				ResultString = GetResultCalculationsString(Calculations[1], GetString, Calculations[2]);
			}
			if (ResultString.Len() > 0)
				(BronzeCoins == -1) ? UJsonLibrary::WriteJsonFile(ResultString, JsonStrings) : UJsonLibrary::WriteJsonFile(ResultString, JsonStrings, true);
		}
		//�C�x���g�ɃW�����v����B
		JumpMessage(Event);
		Once = true;
	}
	else if (option.Equals(FString("OpenUI")))
	{
		FString LocalStr;
		TArray<FString> texts;
		while (optionString.Split(FString("_"), &LocalStr, &optionString))
		{
			texts.Add(LocalStr);
		}
		texts.Add(optionString);
		Texts = texts;
		OpenUIFlag = true;
	}
}


// Called when the game starts
void UCommunicationComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

bool UCommunicationComponent::GetResultCompareString(FString Operator, FString Value, FString Constant)
{
	if (Operator.Equals("=="))
	{
		if (Value.Equals(Constant))
			return true;
	}
	else if (Operator.Equals("!="))
	{
		if (!Value.Equals(Constant))
			return true;
	}
	return false;
}

FString UCommunicationComponent::GetResultCalculationsString(FString Operator, FString Value, FString Constant)
{
	FString Result;
	if (Operator.Equals("="))
		Result = Constant;
	return Result;
}

// Called every frame
void UCommunicationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


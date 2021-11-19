// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Library/JsonLibrary.h"
#include "../RPGGameInstance.h"
#include "CommunicationComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class RPG_GAME_API UCommunicationComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	//Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool SelectFlag;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool BranchFlag;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool MessageFlag;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool EndFlag;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool OpenUIFlag;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<int32> MessageCounts;

	//Constra
	UCommunicationComponent() : SelectFlag(false), BranchFlag(false), MessageFlag(false), EndFlag(false), OpenUIFlag(false) {
		PrimaryComponentTick.bCanEverTick = false; 
		MessageCounts.Init(-1, 3);
	};

	//Functions
	UFUNCTION(BlueprintCallable)
		FString GetKey(FString CountString, const FString EventName);
	UFUNCTION(BlueprintCallable)
		void GetMessage(FString BaseString, FString &Name, FString &Text, TArray<FString>& Texts, bool& Once);
	UFUNCTION(BlueprintCallable)
		void JumpMessage(FString ID);
	UFUNCTION(BlueprintCallable)
		void AddMessageCounts();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	template<typename T>
		bool GetResultCompare(FString Operator, T Value, T Constant);
		bool GetResultCompareString(FString Operator, FString Value, FString Constant);
	template<typename T>
		T GetResultCalculations(FString Operator, T Value, T Constant);
		FString GetResultCalculationsString(FString Operator, FString Value, FString Constant);


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};


//Compareがtrueのときは値が数値の時
//Compareがfalseのときは値が文字列
//戻り値がTrueのときはTrueイベント、FalseのときはFalseイベントが実行される
template<typename T>
inline bool UCommunicationComponent::GetResultCompare(FString Operator, T Value, T Constant)
{
	if (Operator.Equals(">="))
	{
		if (Value >= Constant)
			return true;
	}
	else if (Operator.Equals("<="))
	{
		if (Value <= Constant)
			return true;
	}
	else if (Operator.Equals("=="))
	{
		if (Value == Constant)
			return true;
	}
	else if (Operator.Equals("!="))
	{
		if (Value != Constant)
			return true;
	}
	else if (Operator.Equals("<"))
	{
		if (Value < Constant)
			return true;
	}
	else if (Operator.Equals(">"))
	{
		if (Value > Constant)
			return true;
	}
	return false;
}

//
//
//
template<typename T>
inline T UCommunicationComponent::GetResultCalculations(FString Operator, T Value, T Constant)
{
	T Result;
	if (Operator.Equals("-"))
		Result = Value - Constant;
	else if (Operator.Equals("+"))
		Result = Value + Constant;
	else if (Operator.Equals("*"))
		Result = Value * Constant;
	else if (Operator.Equals("/"))
		Result = Value / Constant;
	else if (Operator.Equals("="))
		Result = Constant;

	return Result;
	/*if (flag == 0)
		return FString::FromInt((int32)Result);
	else if (flag == 1)
		return FString::SanitizeFloat((float)Result);
	else
		return FString((FString)Result);*/
}

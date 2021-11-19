// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../../Public/Character/MainMap/CharacterBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "MainMapPC.generated.h"


USTRUCT(BlueprintType)
struct FMainMapPCStautus : public FCharacterBaseStatus {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FTransform PlayerTransform;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int32 TitoPoint;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int32 PCoins;//”’‹à‰Ý
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int32 GCoins;//‹à‰Ý
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int32 SCoins;//‹â‰Ý
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int32 BCoins;//“º‰Ý
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int32 TearOffSpeed;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		TArray<ETitoList> HaveTito;
};

/**
 * 
 */
UCLASS()
class AMainMapPC : public ACharacterBase
{
	GENERATED_BODY()
public:
	AMainMapPC();
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UCameraComponent* CameraComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USpringArmComponent* SpringArmComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MaxSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FMainMapPCStautus MainMapPCStautus;
	UFUNCTION()
		void MoveForward(float Value);
	UFUNCTION()
		void MoveRight(float Value);
	UFUNCTION()
		void LookRight(float Value);
	UFUNCTION()
		void LookUp(float Value);
	UFUNCTION()
		void DamegeStamina();
	UFUNCTION(BlueprintCallable)
		void SetStatus();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	bool RemoveItem(FString Key, int32 Index) override;
	bool RemoveClothes(FString Key, int32 Index) override;
	FClothesStruct SetRightOrLeft(FString Key, int32 Index, ERightOrLeft RightOrLeft, EFingerKinds FingerKinds) override;
};

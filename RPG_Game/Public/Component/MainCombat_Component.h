// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "./Character/Combat/CombatCharacterBase.h"
#include "./Character/Combat/CombatPlayer.h"
#include "MainCombat_Component.generated.h"


UCLASS(Blueprintable)
class UMainCombat_Component : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMainCombat_Component();
	UPROPERTY(EditAnywhere)
		int32 PlayerDistance;
	UPROPERTY(EditAnywhere)
		int32 EnemyDistance;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	void CheckHP(ACombatCharacterBase* Character);
	void CheckMP(ACombatCharacterBase* Character);
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable)
		FTransform GetSpawnTransform(int32 Index, FVector PlayerSenter, FRotator Rotator);
	UFUNCTION(BlueprintCallable)
		void ChangeStatusNormalAttack(ACombatCharacterBase* PlayingCharacter);
	UFUNCTION(BlueprintCallable)
		void ChangeStatusSkill(ACombatCharacterBase* PlayingCharacter, FSkillStatus SkillStatus);
	UFUNCTION(BlueprintCallable)
		void ChangeStatusMagic(ACombatCharacterBase* PlayingCharacter, FMagicStatus MagicStatus);
	UFUNCTION(BlueprintCallable)
		void ChangeStatusItem(ACombatCharacterBase* PlayingCharacter);

	//Levelアップ関数
	UFUNCTION(BlueprintCallable)
		void PlayerLevelUp(ACombatCharacterBase* Player, float TotalExp, FPlayerUpCoefficient PlayerUp, FDifficultyStatusUp DiffcultyStatusUp, FNeedExperience Need, int32& OutLevel, float& Amari);
	UFUNCTION(BlueprintCallable, BlueprintPure)
		float GetNeedExperience(ACombatCharacterBase* Player, FNeedExperience Need);
	void LevelUp(ACombatCharacterBase* Player, FPlayerUpCoefficient PlayerUp, FDifficultyStatusUp DiffcultyStatusUp);
	//trueで負け、falseではまだ負けていない
	UFUNCTION(BlueprintCallable, BlueprintPure)
		bool CheckGameOver(TArray<ACombatCharacterBase*> Players);
	//trueで勝ち、falseではまだ勝ちではない
	UFUNCTION(BlueprintCallable, BlueprintPure)
		bool CheckWinner(TArray<ACombatCharacterBase*> Enemys);
};

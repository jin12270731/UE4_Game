// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "../RPGGameInstance.h"
#include "../Character/MainMap/CharacterBase.h"
#include "../Character/Combat/CombatCharacterBase.h"
#include "../Character/Combat/CombatPlayer.h"
#include "../Character/Combat/CombatEnemy.h"
#include "CombatManeger.generated.h"

UCLASS()
class ACombatManeger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACombatManeger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditDefaultsOnly)
		URPGGameInstance* RPGGameInstance;
	UPROPERTY(EditDefaultsOnly)
		FTransform EnemyCenterTransform;
	UPROPERTY(EditDefaultsOnly)
		FTransform PlayerCenterTransform;
	UPROPERTY(EditDefaultsOnly)
		TArray<ACombatPlayer*> Players;
	UPROPERTY(EditDefaultsOnly)
		TArray<ACombatEnemy*> Enemy;
	UPROPERTY(EditDefaultsOnly)
		TArray<ACombatCharacterBase*> CharacterTurn;
	UPROPERTY(EditDefaultsOnly)
		UDataTable* EnemyDataTable;
	UPROPERTY(EditDefaultsOnly)
		USceneComponent* SceneComponent;
	UPROPERTY(EditAnywhere)
		int32 PlayerDistance;
	UPROPERTY(EditAnywhere)
		int32 EnemyDistance;
	UFUNCTION(BlueprintCallable)
		FTransform GetSpawnTransform(int32 Index, FVector PlayerSenter, FRotator Rotator);

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "SavePoint.generated.h"

UCLASS()
class ASavePoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASavePoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY()
		UStaticMeshComponent* MyMeshCom;
	UPROPERTY()
		FVector initialLocation;
	float speed = 1;
	float range = 100;
	UPROPERTY(BlueprintReadWrite)
		UTextRenderComponent* MyTextCom;
	UPROPERTY()
		USceneComponent* MySceneCom;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

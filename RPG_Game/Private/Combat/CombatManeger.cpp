// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Public/Combat/CombatManeger.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"

// Sets default values
ACombatManeger::ACombatManeger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	EnemyCenterTransform.SetLocation(FVector(500.0f,0.0f, 190.0f));
	EnemyCenterTransform.SetRotation(FQuat::FQuat(0.0f,0.0f,0.0f,0.0f));
	EnemyCenterTransform.SetScale3D(FVector::FVector(1.0f, 1.0f, 1.0f));
	PlayerCenterTransform.SetLocation(FVector(-500.0f, 0.0f, 190.0f));
	PlayerCenterTransform.SetRotation(FQuat::FQuat(0.0f, 0.0f, 0.0f, 0.0f));
	PlayerCenterTransform.SetScale3D(FVector::FVector(1.0f, 1.0f, 1.0f));
	PlayerDistance = 200;
	EnemyDistance = 200;
	////Find class
	//ConstructorHelpers::FObjectFinder<UClass> SpawnPlayerClass(TEXT("/Game/RPG/Blueprints/Characters/Combat_Player/BP_CombatPlayer.BP_CombatPlayer_C"));
	//ConstructorHelpers::FObjectFinder<UClass> SpawnBarghestClass(TEXT("/Game/RPG/Blueprints/Characters/Enemy/Barghest/Combat/BP_CombatBarghest.BP_CombatBarghest_C"));
	//ConstructorHelpers::FObjectFinder<UClass> SpawnCentaurClass(TEXT("/Game/RPG/Blueprints/Characters/Enemy/Centaur/Combat/BP_CombatCentaur.BP_CombatCentaur_C"));
	//ConstructorHelpers::FObjectFinder<UClass> SpawnGriffonClass(TEXT("/Game/RPG/Blueprints/Characters/Enemy/Griffon/Combat/BP_CombatGriffon.BP_CombatGriffon_C"));
	//ConstructorHelpers::FObjectFinder<UClass> SpawnMountaonDragonClass(TEXT("/Game/RPG/Blueprints/Characters/Enemy/MountaonDragon/Combat/BP_CombatMountaonDragon.BP_CombatMountaonDragon_C"));
	////Set Object
	//CombatPlayeObject = SpawnPlayerClass.Object;
	//CombatEnemyObject.Add(TEXT("Barghest"), SpawnBarghestClass.Object);
	//CombatEnemyObject.Add(TEXT("Centaur"), SpawnCentaurClass.Object);
	//CombatEnemyObject.Add(TEXT("Griffon"), SpawnGriffonClass.Object);
	//CombatEnemyObject.Add(TEXT("MountaonDragon"), SpawnMountaonDragonClass.Object);
	//Create Camera Component and Scene Component
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SceneComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ACombatManeger::BeginPlay()
{
	Super::BeginPlay();
	RPGGameInstance = Cast<URPGGameInstance>(GetGameInstance());
	
}

// Called every frame
void ACombatManeger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FTransform ACombatManeger::GetSpawnTransform(int32 Index, FVector PlayerSenter, FRotator Rotator)
{
	if (Index == -1)
	{
		return FTransform(Rotator, PlayerSenter, FVector(1.0f));
	}
	else if (Index % 2 == 0)//ãÙêî
	{
		FVector spawnVector = PlayerSenter;
		spawnVector.Y += PlayerDistance * (Index / 2 + 1);
		return FTransform(Rotator, spawnVector, FVector(1.0f));
	}
	else
	{
		FVector spawnVector = PlayerSenter;
		spawnVector.Y += -PlayerDistance * (Index / 2 + 1);
		return FTransform(Rotator, spawnVector, FVector(1.0f));
	}
}


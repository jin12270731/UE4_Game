// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Public/Save/SavePoint.h"

// Sets default values
ASavePoint::ASavePoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Componentを作成
	MySceneCom = CreateDefaultSubobject<USceneComponent>("SceneCom");
	MyMeshCom = CreateDefaultSubobject<UStaticMeshComponent>("saveMesh");
	MyTextCom = CreateDefaultSubobject<UTextRenderComponent>("Name");
	//Componentをアタッチ
	RootComponent = MySceneCom;
	MyMeshCom->SetupAttachment(RootComponent);
	MyTextCom->SetupAttachment(RootComponent);
	//Static Meshを読み込む
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(TEXT("/Game/StarterContent/Shapes/Shape_Sphere"));

	if (SphereMesh.Succeeded()) {
		//読み込みに成功したらStatic Mesh ComponentにStatic Meshをセットする
		MyMeshCom->SetStaticMesh(SphereMesh.Object);
		//Root Componentからの相対位置をセット．これだとRoot Componentと同じ位置になる
		MyMeshCom->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	}
	//
	MyTextCom->SetRelativeLocation(FVector(0.0f, 0.0, 100.0f));
	MyTextCom->SetText(TEXT("SAVE POINT"));
	MyTextCom->SetTextRenderColor(FColor::Black);
	MyTextCom->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
}

// Called when the game starts or when spawned
void ASavePoint::BeginPlay()
{
	Super::BeginPlay();
	initialLocation = GetActorLocation();
}

// Called every frame
void ASavePoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//現在の座標を取得
	FVector nowLocation = GetActorLocation();
	//初期値より小さいか，設定範囲外か
	if (nowLocation.Z > initialLocation.Z + range || nowLocation.Z < initialLocation.Z)
		speed *= -1.0f;//＋と－を入れ替える
	//座標の更新
	nowLocation.Z += speed;
	//新たな座標をセットする
	SetActorLocation(nowLocation);
}

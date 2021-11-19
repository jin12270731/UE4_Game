// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Public/Save/SavePoint.h"

// Sets default values
ASavePoint::ASavePoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Component���쐬
	MySceneCom = CreateDefaultSubobject<USceneComponent>("SceneCom");
	MyMeshCom = CreateDefaultSubobject<UStaticMeshComponent>("saveMesh");
	MyTextCom = CreateDefaultSubobject<UTextRenderComponent>("Name");
	//Component���A�^�b�`
	RootComponent = MySceneCom;
	MyMeshCom->SetupAttachment(RootComponent);
	MyTextCom->SetupAttachment(RootComponent);
	//Static Mesh��ǂݍ���
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(TEXT("/Game/StarterContent/Shapes/Shape_Sphere"));

	if (SphereMesh.Succeeded()) {
		//�ǂݍ��݂ɐ���������Static Mesh Component��Static Mesh���Z�b�g����
		MyMeshCom->SetStaticMesh(SphereMesh.Object);
		//Root Component����̑��Έʒu���Z�b�g�D���ꂾ��Root Component�Ɠ����ʒu�ɂȂ�
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
	//���݂̍��W���擾
	FVector nowLocation = GetActorLocation();
	//�����l��菬�������C�ݒ�͈͊O��
	if (nowLocation.Z > initialLocation.Z + range || nowLocation.Z < initialLocation.Z)
		speed *= -1.0f;//�{�Ɓ|�����ւ���
	//���W�̍X�V
	nowLocation.Z += speed;
	//�V���ȍ��W���Z�b�g����
	SetActorLocation(nowLocation);
}

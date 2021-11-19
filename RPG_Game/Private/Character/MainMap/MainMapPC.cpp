// Fill out your copyright notice in the Description page of Project Settings.

#include "../../../Public/RPGGameInstance.h"
#include "../../../Public/Character/MainMap/MainMapPC.h"

AMainMapPC::AMainMapPC() {
	PrimaryActorTick.bCanEverTick = true;
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	CameraComponent->SetupAttachment(SpringArmComponent);
	SpringArmComponent->SetupAttachment(GetMesh());
	//SpringArmComponent->SetupAttachment(RootComponent);
	
}

void AMainMapPC::MoveForward(float Value)
{
}

void AMainMapPC::MoveRight(float Value)
{
	
	FRotator rotator = GetMesh()->GetRelativeRotation();
	FRotator newRotator = FRotator(rotator.Pitch, rotator.Yaw + Value, rotator.Roll);
	GetMesh()->SetRelativeRotation(newRotator);
}

void AMainMapPC::LookRight(float Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::SanitizeFloat(Value));
}

void AMainMapPC::LookUp(float Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using FPSCharacter."));
}

void AMainMapPC::DamegeStamina()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("800."));
}

void AMainMapPC::SetStatus()
{
	URPGGameInstance* gameinstance = URPGGameInstance::GetGameInstance();
	if (gameinstance)
	{
		this->MainMapPCStautus = gameinstance->MainMapPCStautus;
	}
}

void AMainMapPC::BeginPlay()
{
	Super::BeginPlay();
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Begin."));
	//UE_LOG(LogTest, Log, TEXT("Call Lambda SetTimer"));
	MaxSpeed = 250.0f;
}

void AMainMapPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMainMapPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	/*PlayerInputComponent->BindAxis("moveForward", this, &AMainMapPC::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainMapPC::MoveRight);
	PlayerInputComponent->BindAxis("LookRight", this, &AMainMapPC::LookRight);
	PlayerInputComponent->BindAxis("LookUp", this, &AMainMapPC::LookUp);*/
}

bool AMainMapPC::RemoveItem(FString Key, int32 Index)
{
	FItemArray *Item = this->MainMapPCStautus.Items.Find(Key);
	if (Item != nullptr)
	{
		Item->ItemStruct.RemoveAt(Index);
		if (Item->ItemStruct.Num() <= 0)
			this->MainMapPCStautus.Items.Remove(Key);
		return true;
	}
	return false;
}

bool AMainMapPC::RemoveClothes(FString Key, int32 Index)
{
	FClothesArray* Clothes = this->MainMapPCStautus.HaveClothes.Find(Key);
	if (Clothes != nullptr)
	{
		if(Clothes->ClothesStruct.IsValidIndex(Index))
			Clothes->ClothesStruct.RemoveAt(Index);
		if (Clothes->ClothesStruct.Num() <= 0)
			this->MainMapPCStautus.HaveClothes.Remove(Key);
		return true;
	}
	return false;
}

//���L���Ă��鑕���𑕔�����Ƃ��͂ǂ��ɑ������邩��ݒ肷��
//Key			:�ǂ̏��L������
//Index			:Key�̑����̉��Ԗڂ�
//RightOrLeft	:���݁A�E�����A����ȊO��I�����Ă��邩
//FingerKinds	:���݁A�ǂ��̎w��I�����Ă��邩
FClothesStruct AMainMapPC::SetRightOrLeft(FString Key, int32 Index, ERightOrLeft RightOrLeft, EFingerKinds FingerKinds)
{
	FOtherClothes OtherClothes = FOtherClothes();
	FClothesArray *ClothesArray = MainMapPCStautus.HaveClothes.Find(Key);
	if (ClothesArray)
	{
		if (ClothesArray->ClothesStruct.IsValidIndex(Index))
		{
			bool isRight = false;//�E�ɑ���������
			for (auto& LocalClothesPart : ClothesArray->ClothesStruct[Index].ClothesParts)
			{
				if (INDEX_NONE == OtherClothes.OtherClothesPart.Find(LocalClothesPart.ClothesPart))
				{
					if (ClothesArray->ClothesStruct[Index].ClothesParts.Num() > 1)
					{
						if(LocalClothesPart.ClothesPart != EClothesPart::Finger && !isRight)
						{
							LocalClothesPart.RightOrLeft = ERightOrLeft::Right;
							isRight = true;
						}
						else
						{
							LocalClothesPart.RightOrLeft = ERightOrLeft::Left;
						}
					}
					else
					{
						if (LocalClothesPart.ClothesPart == EClothesPart::Finger)
						{
							LocalClothesPart.FingerKinds = FingerKinds;
							LocalClothesPart.RightOrLeft = RightOrLeft;
						}
						else
						{
							LocalClothesPart.RightOrLeft = RightOrLeft;
						}
					}
				}
			}
		}
	}
	return ClothesArray->ClothesStruct[Index];
}


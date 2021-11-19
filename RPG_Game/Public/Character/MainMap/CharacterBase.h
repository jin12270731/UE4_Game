// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Engine/DataTable.h"
#include "CharacterBase.generated.h"


UENUM(BlueprintType)
enum class ETitoList : uint8
{
	Kantei,
	Sutaminazouka,
	Sutaminakaifuku,
	Idousokudo,
	Seityouzouka,
	Keikentizouka,
	Teni,
	Mapping,
	Inmitu,
	Ansatu,
	Sinimodori,
	Itembox,
	Sikaikyouka,
	Bouen
};


UENUM(BlueprintType)
enum class EItemEffect : uint8 
{
	Self,
	Friend,
	Target,
	Not
};

UENUM(BlueprintType)
enum class ETargetStatus : uint8
{
	NowHP,
	MaxHP,
	NowMP,
	MaxMP,
	NowSP,
	MaxSP,
	NA,
	MA,
	ND,
	MD,
	Speed,
	C,
	CC,
	Exp,
	Not
};



UENUM(BlueprintType)
enum class EWhereUse : uint8
{
	Combat,
	Main,
	Both,
	Not
};

UENUM(BlueprintType)
enum class ESpecialSkillType : uint8
{
	Nothing,
	Appraisal
};

UENUM(BlueprintType)
enum class EGenderEnum : uint8 {
	Man,
	Woman
};

UENUM(BlueprintType)
enum class EAttributeType : uint8 {
	Fire,
	Water,
	Wind,
	Thunder,
	Darkness,
	Light,
	Nothing
};

UENUM(BlueprintType)
enum class EGrowRate : uint8 {
	Child,
	Parent,
	Adult,
	Old
};

UENUM(BlueprintType)
enum class EUseCombatOnlyOrBoth : uint8 {
	CombatOnly,
	Both
};

UENUM(BlueprintType)
enum class ETargetType : uint8 {
	Enemy,
	Self,
	Friend,
	Both
};

UENUM(BlueprintType)
enum class EGrowthTypeEnum : uint8 {
	Balance,
	Attack,
	Magic,
	Defense
};

UENUM(BlueprintType)
enum class EAbiltys : uint8
{
	Tito,
	Skill,
	Magic
};

UENUM(BlueprintType)
enum class EAdderOrMultip : uint8
{
	Adder,
	Multip,
	Not
};

UENUM(BlueprintType)
enum class EClothesPart : uint8
{
	Head,
	Face,
	Ear,
	Neck,
	Shoulder,
	Arm,
	Wrist,
	Hand,
	Finger,
	Chest,
	Stomach,
	Waist,
	Thighs,
	Calf,
	Ankle,
	Legs,
	Back
};

UENUM(BlueprintType)
enum class ERightOrLeft : uint8
{
	Other,
	Right,
	Left
	
};

UENUM(BlueprintType)
enum class EFingerKinds : uint8
{
	other,
	Thumb,			//親指
	Indexfinger,	//人差し指
	Middlefinger,	//中指
	RingFinnger,	//薬指
	LittleFinger	//小指
};

UENUM(BlueprintType)
enum class EItemKinds : uint8
{
	All,
	Use,
	Material
};

//左右や指ではないやつら
USTRUCT(BlueprintType)
struct FOtherClothes
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
		TArray<EClothesPart> OtherClothesPart;
	FOtherClothes()
	{
		this->OtherClothesPart.Add(EClothesPart::Head);
		this->OtherClothesPart.Add(EClothesPart::Face);
		this->OtherClothesPart.Add(EClothesPart::Neck);
		this->OtherClothesPart.Add(EClothesPart::Chest);
		this->OtherClothesPart.Add(EClothesPart::Stomach);
		this->OtherClothesPart.Add(EClothesPart::Waist);
		this->OtherClothesPart.Add(EClothesPart::Back);
	};
};

USTRUCT(BlueprintType)
struct FClothesParts
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		EClothesPart ClothesPart;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		ERightOrLeft RightOrLeft;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		EFingerKinds FingerKinds;
	FClothesParts() : ClothesPart(EClothesPart::Face), RightOrLeft(ERightOrLeft::Other), FingerKinds(EFingerKinds::other) {}
	FClothesParts(EClothesPart ClothesPart, ERightOrLeft RightOrLeft) : ClothesPart(ClothesPart), RightOrLeft(RightOrLeft), FingerKinds(EFingerKinds::other) {}
};

//増減についての構造体
USTRUCT(BlueprintType)
struct FFluctuationStatusStruct
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		EAdderOrMultip AdderOrMultip;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		ETargetStatus TargetStatus;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		float Value;
	FFluctuationStatusStruct() : AdderOrMultip(EAdderOrMultip::Adder), TargetStatus(ETargetStatus::MaxHP), Value(-1.000000) {}
};

USTRUCT(BlueprintType)
struct FItemBase : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FString Key;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FString Name;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 ID;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 MaxHP;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 NowHP;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float Quality;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 Mass;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 Volume;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 BaseValue;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		EItemKinds ItemKinds;
	FItemBase() : Key(""), Name(""), ID(-1), MaxHP(-1), NowHP(-1), Quality(-1.000000), Mass(-1), Volume(-1), ItemKinds(EItemKinds::Use) {}
};

USTRUCT(BlueprintType)
struct FItemStruct : public FItemBase
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		EItemEffect ItemEffect;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		TArray<FFluctuationStatusStruct> FluctuationStatusStructs;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		EWhereUse WhereUse;
	FItemStruct() : ItemEffect(EItemEffect::Self), WhereUse(EWhereUse::Both){}
};


USTRUCT(BlueprintType)
struct FMassAndVolume
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 MaxMass;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 NowMass;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 MaxVolume;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 NowVolume;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 ClothesMaxMass;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 ClothesNowMass;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 ClothesMaxVolume;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 ClothesNowVolume;
	FMassAndVolume() : MaxMass(1), NowMass(0), MaxVolume(1), NowVolume(0), ClothesMaxMass(1), ClothesNowMass(0), ClothesMaxVolume(1), ClothesNowVolume(0) {}
};

USTRUCT(BlueprintType)
struct FClothesStruct : public FItemBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		TArray<FFluctuationStatusStruct> FluctuationStatusStructs;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		TArray<FClothesParts> ClothesParts;
	FClothesStruct() {};
	FClothesStruct(FString name, TArray<FClothesParts> clothesParts, TArray<FFluctuationStatusStruct> FluctuationStatusStructs)
	{
		this->Name = name;
		//this->Key =;
		//this->Name;
		//this->ID;
		//this->MaxHP;
		//this->NowHP;
		//this->Quality;
		//this->Mass;
		//this->Volume;
		this->ClothesParts = clothesParts;
		this->FluctuationStatusStructs = FluctuationStatusStructs;

	};
	FClothesStruct(FString name, TArray<FClothesParts> clothesParts)
	{ 
		this->Name = name; 
		this->ClothesParts = clothesParts;
	}
};

USTRUCT(BlueprintType)
struct FItemArray
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TArray<FItemStruct> ItemStruct;
	FItemArray() {}
	FItemArray(FItemStruct AddItem)
	{
		ItemStruct.Add(AddItem);
	}
};

USTRUCT(BlueprintType)
struct FClothesArray
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TArray<FClothesStruct> ClothesStruct;

};

USTRUCT(BlueprintType)
struct FSkillStatus : public FTableRowBase {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString SkillName;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int32 SortInteger;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int32 CostSP;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		float BaseAttack;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		ESpecialSkillType SpecialSkillType;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		EAttributeType SkillAttribute;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		ETargetType Target;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		EUseCombatOnlyOrBoth CombatOnlyOrBoth;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int32 NeedPoint;
	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
		FString Passward;
};


USTRUCT(BlueprintType)
struct FMagicStatus : public FTableRowBase {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FString MagicName;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int32 SortInteger;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int32 CostMP;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		float BaseAttack;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		EAttributeType MagicAttribute;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		ETargetType Target;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int32 NeedPoint;
	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
		FString Passward;
};

USTRUCT(BlueprintType)
struct FCharacterBaseStatus
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FString CharacterName;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 Level;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 NowHP;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 MaxHP;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 NowSP;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 MaxSP;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 NowMP;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 MaxMP;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 NormalAttack;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 MagicAttack;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 NormalDefense;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 MagicDefense;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 Speed;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float Critical;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float CriticalCoefficient;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float TotalExperience;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float RemainderExperience;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool DieFlag;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		EGenderEnum Gender;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		EGrowRate GrowRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		EGrowthTypeEnum GrowthType;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FMassAndVolume MassAndVolume;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		TMap<FString, FMagicStatus> Magic;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		TMap<FString, FSkillStatus> Skill;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		TMap<FString, FItemArray> Items;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		TMap<FString, FClothesArray> HaveClothes;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		TMap<FName, FClothesStruct> Clothes;
	FCharacterBaseStatus();
};

UCLASS()
class ACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION(BlueprintCallable)
		virtual bool RemoveItem(FString Key, int32 Index);
	UFUNCTION(BlueprintCallable)
		virtual bool RemoveClothes(FString Key, int32 Index);
	UFUNCTION(BlueprintCallable)
		virtual FClothesStruct SetRightOrLeft(FString Key, int32 Index, ERightOrLeft RightOrLeft, EFingerKinds FingerKinds);

};

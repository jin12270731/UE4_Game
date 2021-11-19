// Fill out your copyright notice in the Description page of Project Settings.


#include "../../../Public/Character/Combat/CombatCharacterBase.h"
//void ACombatCharacterBase::SetAnimationAndRate(UAnimationAsset* NewAnimToPlay, TArray<USceneComponent*> ChildlenComponent, float Rate)
//{
//	for (auto& component :ChildlenComponent) 
//	{
//		USkeletalMeshComponent* skeltalMesh = Cast<USkeletalMeshComponent>(component);
//		if (skeltalMesh != nullptr)
//		{
//			skeltalMesh->SetAnimation(NewAnimToPlay);
//			skeltalMesh->SetPlayRate(Rate);
//			skeltalMesh->Play(false);
//		}
//	}
//	this->GetMesh()->SetAnimation(NewAnimToPlay);
//	this->GetMesh()->SetPlayRate(Rate);
//	this->GetMesh()->Play(false);
//}
//
//void ACombatCharacterBase::SetIdleAnimation(UAnimationAsset* IdleAnim, TArray<USceneComponent*> ChildlenComponent)
//{
//	for (auto& component : ChildlenComponent)
//	{
//		USkeletalMeshComponent* skeltalMesh = Cast<USkeletalMeshComponent>(component);
//		if (skeltalMesh != nullptr)
//		{
//			skeltalMesh->SetAnimation(IdleAnim);
//			skeltalMesh->SetPlayRate(1.0f);
//			skeltalMesh->Play(true);
//		}
//	}
//	this->GetMesh()->SetAnimation(IdleAnim);
//	this->GetMesh()->SetPlayRate(1.0f);
//	this->GetMesh()->Play(true);
//}


void ACombatCharacterBase::SendAnimation(UAnimMontage* DamegeAnim, float Rate)
{
	PlayAnimMontage(DamegeAnim,Rate);
}

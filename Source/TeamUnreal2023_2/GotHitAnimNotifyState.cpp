// Fill out your copyright notice in the Description page of Project Settings.
//�Ⱦ��� Ŭ���� -> ������ ��

#include "GotHitAnimNotifyState.h"
#include "NPC.h"

void UGotHitAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		if (ANPC* const character = Cast<ANPC>(MeshComp->GetOwner()))
		{
			originalBehavior = character->GetBehavior();
			character->SetBehavior(EMonsterBehavior::GOTHIT);
		}
	}
}

void UGotHitAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		if (ANPC* const character = Cast<ANPC>(MeshComp->GetOwner()))
		{
			character->SetBehavior(originalBehavior);
		}
	}
}
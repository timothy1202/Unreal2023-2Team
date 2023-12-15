// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillAnimNotifyState.h"
#include "NPC.h"

void USkillAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		if (ANPC* const character = Cast<ANPC>(MeshComp->GetOwner()))
		{
			// ������ - ��ų�� �����ߴٴ� ���� ��Ÿ�� ���� �� �˸�
			character->SetIsSkillOn(true);
		}
	}
}

void USkillAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		if (ANPC* const character = Cast<ANPC>(MeshComp->GetOwner()))
		{
			// ������ - ��ų�� �����ٴ� ���� ��Ÿ�� ���� �� �˸�
			character->SetIsSkillOn(false);

			// ������ -> ��ų ������ Ʈ����
			character->SetTriggerSkill();
		}
	}
}
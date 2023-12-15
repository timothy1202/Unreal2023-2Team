// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillAnimNotifyState.h"
#include "NPC.h"

void USkillAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		if (ANPC* const character = Cast<ANPC>(MeshComp->GetOwner()))
		{
			// 음영준 - 스킬을 시작했다는 것을 몽타주 시작 시 알림
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
			// 음영준 - 스킬이 끝났다는 것을 몽타주 끝날 시 알림
			character->SetIsSkillOn(false);

			// 음영준 -> 스킬 실행을 트리거
			character->SetTriggerSkill();
		}
	}
}
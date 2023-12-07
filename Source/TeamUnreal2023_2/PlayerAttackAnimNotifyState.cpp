// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAttackAnimNotifyState.h"
#include "TeamUnreal2023_2Character.h"

void UPlayerAttackAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		if (ATeamUnreal2023_2Character* const character = Cast<ATeamUnreal2023_2Character>(MeshComp->GetOwner()))
		{
			// 음영준 - 몽타주에서 시작했다는 것을 알릴 시 플레이어의 Fist콜리전 활성화
			character->AttackCollisionEnable();
		}
	}
}

void UPlayerAttackAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		if (ATeamUnreal2023_2Character* const character = Cast<ATeamUnreal2023_2Character>(MeshComp->GetOwner()))
		{
			// 음영준 - 몽타주에서 끝났다는 것을 알릴 시 플레이어의 Fist콜리전 비활성화
			character->AttackCollisionDisable();
		}
	}
}
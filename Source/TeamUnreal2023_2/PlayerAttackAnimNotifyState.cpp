// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAttackAnimNotifyState.h"
#include "TeamUnreal2023_2Character.h"

void UPlayerAttackAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		if (ATeamUnreal2023_2Character* const character = Cast<ATeamUnreal2023_2Character>(MeshComp->GetOwner()))
		{
			// ������ - ��Ÿ�ֿ��� �����ߴٴ� ���� �˸� �� �÷��̾��� Fist�ݸ��� Ȱ��ȭ
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
			// ������ - ��Ÿ�ֿ��� �����ٴ� ���� �˸� �� �÷��̾��� Fist�ݸ��� ��Ȱ��ȭ
			character->AttackCollisionDisable();
		}
	}
}
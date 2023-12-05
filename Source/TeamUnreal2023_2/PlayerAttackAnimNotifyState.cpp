// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAttackAnimNotifyState.h"
#include "TeamUnreal2023_2Character.h"

void UPlayerAttackAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		if (ATeamUnreal2023_2Character* const character = Cast<ATeamUnreal2023_2Character>(MeshComp->GetOwner()))
		{
			character->AttackStart();
		}
	}
}

void UPlayerAttackAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		if (ATeamUnreal2023_2Character* const character = Cast<ATeamUnreal2023_2Character>(MeshComp->GetOwner()))
		{
			character->AttackEnd();
		}
	}
}
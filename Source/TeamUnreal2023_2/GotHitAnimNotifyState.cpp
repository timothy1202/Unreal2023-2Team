// Fill out your copyright notice in the Description page of Project Settings.


#include "GotHitAnimNotifyState.h"
#include "MonsterBehavior.h"
#include "NPC.h"

void UGotHitAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Called!"));
	if (MeshComp && MeshComp->GetOwner())
	{
		if (ANPC* const character = Cast<ANPC>(MeshComp->GetOwner()))
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("GotHit!"));
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
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Hit Finish!"));
			character->SetBehavior(originalBehavior);
		}
	}
}
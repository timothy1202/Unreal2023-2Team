// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "PlayerAttackAnimNotifyState.generated.h"

/**
 * 음영준 - 플레이어 공격 몽타주(PlayerAttackMontage)가 재생될 때 호출되는 함수들이 포함된 클래스
 */
UCLASS()
class TEAMUNREAL2023_2_API UPlayerAttackAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	// 음영준 - 몽타주 내에서 이 함수가 호출됨 - 1번
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;

	// 음영준 - 몽타주 내에서 이 함수가 호출됨 - 2번
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};

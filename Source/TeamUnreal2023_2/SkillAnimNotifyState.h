// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "SkillAnimNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class TEAMUNREAL2023_2_API USkillAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
	// 음영준 - 몽타주 내에서 이 함수가 호출됨 - 1번
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;

	// 음영준 - 몽타주 내에서 이 함수가 호출됨 - 2번
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};

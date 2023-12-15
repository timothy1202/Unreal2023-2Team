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
	// ������ - ��Ÿ�� ������ �� �Լ��� ȣ��� - 1��
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;

	// ������ - ��Ÿ�� ������ �� �Լ��� ȣ��� - 2��
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};

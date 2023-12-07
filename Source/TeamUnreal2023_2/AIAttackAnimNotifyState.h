// Fill out your copyright notice in the Description page of Project Settings.
// �Ⱦ��� Ŭ���� -> ������ ��

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "MonsterBehavior.h"
#include "AIAttackAnimNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class TEAMUNREAL2023_2_API UAIAttackAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

private:
	EMonsterBehavior originalBehavior;
	
};

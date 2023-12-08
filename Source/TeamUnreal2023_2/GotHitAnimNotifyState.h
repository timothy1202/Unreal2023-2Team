// Fill out your copyright notice in the Description page of Project Settings.
//안쓰는 클래스 -> 지워야 됨

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "MonsterBehavior.h"
#include "GotHitAnimNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class TEAMUNREAL2023_2_API UGotHitAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

private:
	EMonsterBehavior originalBehavior;
};

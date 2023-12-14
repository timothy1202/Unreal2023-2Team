// Fill out your copyright notice in the Description page of Project Settings.
// 음영준 - 안씀 지워야 됨

#pragma once

#include "CoreMinimal.h"
#include "BTTask_SkillBase.h"
#include "BTTask_NoneInvisibleMonster.generated.h"

/**
 *
 */
UCLASS()
class TEAMUNREAL2023_2_API UBTTask_NoneInvisibleMonster : public UBTTask_SkillBase
{
	GENERATED_BODY()

public:
	explicit UBTTask_NoneInvisibleMonster(FObjectInitializer const& ObjectInitializer); // 박광훈 - 객체 초기화
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override; //박광훈 - 몬스터 소환 테스크

private:
	/// <summary>
	/// 박공훈 - NPC 원래 머티리얼
	/// </summary>
	void RestoreOriginalMaterial(UBehaviorTreeComponent& OwnerComp);
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BTTask_MonsterBase.h"
#include "SkillLogic.h"
#include "BTTask_SkillBase.generated.h"

/**
 * 음영준 - 모든 스킬Task들의 Base가 되는 클래스
 */
UCLASS(Abstract)
class TEAMUNREAL2023_2_API UBTTask_SkillBase : public UBTTask_MonsterBase
{
	GENERATED_BODY()

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	// 음영준 - ISkillLogic인터페이스를 상속받아서 재정의함
	virtual void UseSkill(UBehaviorTreeComponent& OwnerComp);
	virtual void CancleSkill(UBehaviorTreeComponent& OwnerComp);

public:
	// 음영준 - 플레이어가 시야를 벗어나면 스킬 사용 취소 -> static함수로 정의
	void CancleSkillOnFailPerception(UBehaviorTreeComponent& OwnerComp);
};

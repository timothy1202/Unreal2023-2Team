// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SkillLogic.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USkillLogic : public UInterface
{
	GENERATED_BODY()
};

/**
 * 음영준 - 모든 스킬에 포함되는 인터페이스 클래스 (BT내에서 스킬을 멈추는 것이 불가능하다고 판단되어 static함수를 두어 스킬 실행을 멈추도록 구현)
 */
class TEAMUNREAL2023_2_API ISkillLogic
{
	GENERATED_BODY()

public:
	// 음영준 - 스킬을 사용하는 함수 -> 각 스킬 클래스에서 재정의해야 됨
	virtual void UseSkill(class UBehaviorTreeComponent& OwnerComp) = 0;

	// 음영준 - 스킬을 취소하는 함수 -> 각 스킬 클래스에서 재정의해야 됨
	virtual void CancleSkill(class UBehaviorTreeComponent& OwnerComp) = 0;

	// 음영준 - 플레이어가 시야를 벗어나면 스킬 사용 취소 -> static함수로 정의
	static void CancleSkillOnFailPerception(UBehaviorTreeComponent& OwnerComp);
};

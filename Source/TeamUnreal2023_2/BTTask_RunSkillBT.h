// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BTTask_MonsterBase.h"
#include "BTTask_RunSkillBT.generated.h"

/**
 * 음영준 - 스킬을 사용하는 서브트리로 전환해주는 클래스
 */
UCLASS()
class TEAMUNREAL2023_2_API UBTTask_RunSkillBT : public UBTTask_MonsterBase
{
	GENERATED_BODY()
	
public:
	explicit UBTTask_RunSkillBT(FObjectInitializer const& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BTTask_MonsterBase.h"
#include "BTTask_AttackPlayer.generated.h"

/**
 * 음영준 - AI가 플레이어를 공격시키게 하는 노드
 */
UCLASS()
class TEAMUNREAL2023_2_API UBTTask_AttackPlayer : public UBTTask_MonsterBase
{
	GENERATED_BODY()

public:
	explicit UBTTask_AttackPlayer(FObjectInitializer const& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};

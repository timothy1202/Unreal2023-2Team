// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BTTask_MonsterBase.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_TeleportingMonster.generated.h"

/**
 * 
 */
UCLASS()
class TEAMUNREAL2023_2_API UBTTask_TeleportingMonster : public UBTTask_MonsterBase
{
	GENERATED_BODY()

public:
	UBTTask_TeleportingMonster();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};

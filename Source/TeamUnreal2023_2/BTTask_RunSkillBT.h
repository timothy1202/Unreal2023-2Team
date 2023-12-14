// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_RunSkillBT.generated.h"

/**
 * ������ - ��ų�� ����ϴ� ����Ʈ���� ��ȯ���ִ� Ŭ����
 */
UCLASS()
class TEAMUNREAL2023_2_API UBTTask_RunSkillBT : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	explicit UBTTask_RunSkillBT(FObjectInitializer const& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};

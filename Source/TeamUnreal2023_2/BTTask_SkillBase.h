// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BTTask_MonsterBase.h"
#include "SkillLogic.h"
#include "BTTask_SkillBase.generated.h"

/**
 * ������ - ��� ��ųTask���� Base�� �Ǵ� Ŭ����
 */
UCLASS(Abstract)
class TEAMUNREAL2023_2_API UBTTask_SkillBase : public UBTTask_MonsterBase
{
	GENERATED_BODY()

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	// ������ - ISkillLogic�������̽��� ��ӹ޾Ƽ� ��������
	virtual void UseSkill(UBehaviorTreeComponent& OwnerComp);
	virtual void CancleSkill(UBehaviorTreeComponent& OwnerComp);

public:
	// ������ - �÷��̾ �þ߸� ����� ��ų ��� ��� -> static�Լ��� ����
	void CancleSkillOnFailPerception(UBehaviorTreeComponent& OwnerComp);
};

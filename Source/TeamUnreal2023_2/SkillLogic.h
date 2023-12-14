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
 * ������ - ��� ��ų�� ���ԵǴ� �������̽� Ŭ���� (BT������ ��ų�� ���ߴ� ���� �Ұ����ϴٰ� �ǴܵǾ� static�Լ��� �ξ� ��ų ������ ���ߵ��� ����)
 */
class TEAMUNREAL2023_2_API ISkillLogic
{
	GENERATED_BODY()

public:
	// ������ - ��ų�� ����ϴ� �Լ� -> �� ��ų Ŭ�������� �������ؾ� ��
	virtual void UseSkill(class UBehaviorTreeComponent& OwnerComp) = 0;

	// ������ - ��ų�� ����ϴ� �Լ� -> �� ��ų Ŭ�������� �������ؾ� ��
	virtual void CancleSkill(class UBehaviorTreeComponent& OwnerComp) = 0;

	// ������ - �÷��̾ �þ߸� ����� ��ų ��� ��� -> static�Լ��� ����
	static void CancleSkillOnFailPerception(UBehaviorTreeComponent& OwnerComp);
};

// Fill out your copyright notice in the Description page of Project Settings.
// ������ - �Ⱦ� ������ ��

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
	explicit UBTTask_NoneInvisibleMonster(FObjectInitializer const& ObjectInitializer); // �ڱ��� - ��ü �ʱ�ȭ
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override; //�ڱ��� - ���� ��ȯ �׽�ũ

private:
	/// <summary>
	/// �ڰ��� - NPC ���� ��Ƽ����
	/// </summary>
	void RestoreOriginalMaterial(UBehaviorTreeComponent& OwnerComp);
};

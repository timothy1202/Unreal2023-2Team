// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BTTask_MonsterBase.h"
#include "BTTask_SkillBase.h"
#include "BTTask_HackingMonster.generated.h"

/**
 * 
 */
UCLASS()
class TEAMUNREAL2023_2_API UBTTask_HackingMonster : public UBTTask_SkillBase
{
	GENERATED_BODY()

public:
	explicit UBTTask_HackingMonster(FObjectInitializer const& ObjectInitializer); // �ڱ��� - ��ü �ʱ�ȭ
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override; //�ڱ��� - ���� ��ȯ �׽�ũ
	
	virtual void UseSkill(UBehaviorTreeComponent& OwnerComp) override;
	virtual void CancleSkill(UBehaviorTreeComponent& OwnerComp) override;

	UFUNCTION()
	void SetHacking(ANPC* npc, bool isHack);

	void AbleToHack(ANPC* npc);
	void StopHacking(ANPC* npc);
};

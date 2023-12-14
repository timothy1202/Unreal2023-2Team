// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_SkillBase.h"
#include "BTFunction.h"
#include "NPC.h"

EBTNodeResult::Type UBTTask_SkillBase::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (Super::ExecuteTask(OwnerComp, NodeMemory) == EBTNodeResult::InProgress)
	{
		CancleSkill(OwnerComp);
		return EBTNodeResult::InProgress;
	}

	// 음영준 - 스킬 사용
	UseSkill(OwnerComp);

	// 음영준 - AI행동을 Skill로
	if (ANPC* npc = BTFunction::GetControlledNPC(OwnerComp))
	{
		if (npc->GetIsSkillOn() == true)
		{
			BTFunction::GetNPCAndSetBehavior(OwnerComp, EMonsterBehavior::SKILL);
		}
	}

	return EBTNodeResult::Succeeded;
}

void UBTTask_SkillBase::UseSkill(UBehaviorTreeComponent& OwnerComp)
{
	// 음영준 - 각 스킬들에서 재정의
}

void UBTTask_SkillBase::CancleSkill(UBehaviorTreeComponent& OwnerComp)
{
	// 음영준 - 각 스킬들에서 재정의
}

void UBTTask_SkillBase::CancleSkillOnFailPerception(UBehaviorTreeComponent& OwnerComp)
{
	CancleSkill(OwnerComp);
}
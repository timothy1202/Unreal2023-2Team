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

	// ������ - ��ų ���
	UseSkill(OwnerComp);

	// ������ - AI�ൿ�� Skill��
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
	// ������ - �� ��ų�鿡�� ������
}

void UBTTask_SkillBase::CancleSkill(UBehaviorTreeComponent& OwnerComp)
{
	// ������ - �� ��ų�鿡�� ������
}

void UBTTask_SkillBase::CancleSkillOnFailPerception(UBehaviorTreeComponent& OwnerComp)
{
	CancleSkill(OwnerComp);
}
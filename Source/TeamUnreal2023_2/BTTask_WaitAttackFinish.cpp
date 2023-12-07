// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_WaitAttackFinish.h"
#include "MonsterBehavior.h"
#include "BTFunction.h"
#include "AIController.h"
#include "NPC.h"

EBTNodeResult::Type UBTTask_WaitAttackFinish::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (ANPC* controlledPawn = BTFunction::GetControlledNPC(OwnerComp))
	{
		SetNextTickTime(NodeMemory, controlledPawn->GetCurrentMontage()->GetPlayLength());
	}

	return EBTNodeResult::InProgress;
}
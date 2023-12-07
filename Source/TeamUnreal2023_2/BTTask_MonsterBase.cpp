// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MonsterBase.h"
#include "BTFunction.h"
#include "AIController.h"
#include "NPC.h"

EBTNodeResult::Type UBTTask_MonsterBase::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (ANPC* controlledPawn = BTFunction::GetControlledNPC(OwnerComp))
	{
		if (controlledPawn->GetBehavior() == EMonsterBehavior::GOTHIT)
		{
			OwnerComp.GetAIOwner()->StopMovement();
			bNotifyTick = true;
			return EBTNodeResult::InProgress;
		}
	}

	return EBTNodeResult::Succeeded;
}

void UBTTask_MonsterBase::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	if (ANPC* controlledPawn = BTFunction::GetControlledNPC(OwnerComp))
	{
		if (controlledPawn->GetBehavior() != EMonsterBehavior::GOTHIT)
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
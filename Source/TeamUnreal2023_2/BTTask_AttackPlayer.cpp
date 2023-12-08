// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_AttackPlayer.h"
#include "MonsterBehavior.h"
#include "BTFunction.h"
#include "AIController.h"
#include "NPC.h"

UBTTask_AttackPlayer::UBTTask_AttackPlayer(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Attack Player";
}

EBTNodeResult::Type UBTTask_AttackPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (Super::ExecuteTask(OwnerComp, NodeMemory) == EBTNodeResult::InProgress)
		return EBTNodeResult::InProgress;

	if (ANPC* controlledPawn = BTFunction::GetControlledNPC(OwnerComp))
	{
		// ������ - AI�� �������� ����
		OwnerComp.GetAIOwner()->StopMovement();

		// ������ - AttackMontage���� 
		controlledPawn->PlayMontageOnBehavior(GetNewBehavior());

		// ������ - AI�� �ൿ Attack���� ����
		BTFunction::SetMonsterBehavior(*controlledPawn, GetNewBehavior());

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
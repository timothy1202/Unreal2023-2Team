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
		// 음영준 - AI의 움직임을 멈춤
		OwnerComp.GetAIOwner()->StopMovement();

		// 음영준 - AttackMontage실행 
		controlledPawn->PlayMontageOnBehavior(GetNewBehavior());

		// 음영준 - AI의 행동 Attack으로 설정
		BTFunction::SetMonsterBehavior(*controlledPawn, GetNewBehavior());

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
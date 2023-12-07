// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_WaitBehavior.h"
#include "BTFunction.h"
#include "AIController.h"
#include "NPC.h"

EBTNodeResult::Type UBTTask_WaitBehavior::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ANPC* controlledPawn = nullptr;

	if (ANPC* pawn = BTFunction::GetControlledNPC(OwnerComp))
		controlledPawn = pawn;
	else
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

	EMonsterBehavior pawnBehavior = controlledPawn->GetBehavior();

	// 음영준 - AI의 행동이 Chase였냐 Patrol이었냐에 따라서 로직이 달라짐  
	if (pawnBehavior == EMonsterBehavior::CHASE)
	{
		// 음영준 - Chase상태에서 이 노드로 넘어오면 AI의 움직임을 멈추고 '?' UI를 띄움
		OwnerComp.GetAIOwner()->StopMovement();
		BTFunction::SetMonsterBehavior(*controlledPawn, newBehavior);
	}
	else if (pawnBehavior == EMonsterBehavior::PATROL)
	{
		// 음영준 - Patrol상태에서 이 노드로 넘어왔을 때는 정상적으로 Task에 성공했다고 알리고 TickTime설정을 하지 않음
		return EBTNodeResult::Succeeded;
	}

	// 음영준 - BT에서 설정한 WaitTime시간 만큼 다음 실행될 TickTask의 시간을 설정
	const float RemainingWaitTime = FMath::FRandRange(FMath::Max(0.0f, WaitTime - RandomDeviation), (WaitTime + RandomDeviation));
	SetNextTickTime(NodeMemory, RemainingWaitTime);

	// 음영준 - InProgress로 반환하여 TickTask가 실행되기 전까지 다음 노드 실행을 중지시킴
	return EBTNodeResult::InProgress;
}
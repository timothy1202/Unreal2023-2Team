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

	// ������ - AI�� �ൿ�� Chase���� Patrol�̾��Ŀ� ���� ������ �޶���  
	if (pawnBehavior == EMonsterBehavior::CHASE)
	{
		// ������ - Chase���¿��� �� ���� �Ѿ���� AI�� �������� ���߰� '?' UI�� ���
		OwnerComp.GetAIOwner()->StopMovement();
		BTFunction::SetMonsterBehavior(*controlledPawn, newBehavior);
	}
	else if (pawnBehavior == EMonsterBehavior::PATROL)
	{
		// ������ - Patrol���¿��� �� ���� �Ѿ���� ���� ���������� Task�� �����ߴٰ� �˸��� TickTime������ ���� ����
		return EBTNodeResult::Succeeded;
	}

	// ������ - BT���� ������ WaitTime�ð� ��ŭ ���� ����� TickTask�� �ð��� ����
	const float RemainingWaitTime = FMath::FRandRange(FMath::Max(0.0f, WaitTime - RandomDeviation), (WaitTime + RandomDeviation));
	SetNextTickTime(NodeMemory, RemainingWaitTime);

	// ������ - InProgress�� ��ȯ�Ͽ� TickTask�� ����Ǳ� ������ ���� ��� ������ ������Ŵ
	return EBTNodeResult::InProgress;
}
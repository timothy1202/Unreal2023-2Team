// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MonsterBase.h"
#include "BTFunction.h"
#include "AIController.h"
#include "NPC.h"
#include "BTTask_HackingMonster.h"


// ������ - �ڽ� ���κ��� ExecuteTask�� ���������μ� ��Ÿ�ְ� ����������� ���� ���θ� �Ǵ�
EBTNodeResult::Type UBTTask_MonsterBase::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
		if (ANPC* controlledPawn = BTFunction::GetControlledNPC(OwnerComp))
		{
			// ������ - ���� ������̶�� �������� ���߰� EBTNodeResult�� InProgress�� ��ȯ
			if (controlledPawn->IsPlayingMontage())
			{
					// ������ - AI�� ������ ����
					OwnerComp.GetAIOwner()->StopMovement();

					// ������ - TickTask������ ���� bNotifyTick ����
					bNotifyTick = true;

					// ������ - InProgress�� ��ȯ �� BT�ȿ��� ���� ���� �Ѿ�� ���� -> InProgress�� ��ȯ�ϰ� bNotifyTick�� Ȱ��ȭ�ϸ� �� ƽ���� TickTask�� ����
					return EBTNodeResult::InProgress;
			}
		}

	return EBTNodeResult::Succeeded;
}

// ������ - ��Ÿ�ְ� ������̶�� �� TickTask�� �Ѿ�� -> TickTask�� Ȱ��ȭ �� �������� �� ƽ���� �����
void UBTTask_MonsterBase::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	if (ANPC* controlledPawn = BTFunction::GetControlledNPC(OwnerComp))
	{
		// ������ - ���� ��Ÿ�ְ� ������� �ʰ��ִٸ� �½�ũ�� �����ߴٰ� �˸� -> ���� �� �ٽ� ���������� ���� ���� �Ѿ
		if (!controlledPawn->IsPlayingMontage())
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
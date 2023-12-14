// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MonsterBase.h"
#include "BTFunction.h"
#include "AIController.h"
#include "NPC.h"
#include "BTTask_HackingMonster.h"


// 음영준 - 자식 노드로부터 ExecuteTask를 실행함으로서 몽타주가 재생중인지에 대한 여부를 판단
EBTNodeResult::Type UBTTask_MonsterBase::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
		if (ANPC* controlledPawn = BTFunction::GetControlledNPC(OwnerComp))
		{
			// 음영준 - 만약 재생중이라면 움직임을 멈추고 EBTNodeResult를 InProgress로 반환
			if (controlledPawn->IsPlayingMontage())
			{
					// 음영준 - AI의 움직임 멈춤
					OwnerComp.GetAIOwner()->StopMovement();

					// 음영준 - TickTask실행을 위한 bNotifyTick 설정
					bNotifyTick = true;

					// 음영준 - InProgress로 반환 시 BT안에서 다음 노드로 넘어가지 않음 -> InProgress로 반환하고 bNotifyTick을 활성화하면 매 틱마다 TickTask를 실행
					return EBTNodeResult::InProgress;
			}
		}

	return EBTNodeResult::Succeeded;
}

// 음영준 - 몽타주가 재생중이라면 이 TickTask로 넘어옴 -> TickTask는 활성화 된 순간부터 매 틱마다 실행됨
void UBTTask_MonsterBase::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	if (ANPC* controlledPawn = BTFunction::GetControlledNPC(OwnerComp))
	{
		// 음영준 - 만약 몽타주가 재생하지 않고있다면 태스크를 성공했다고 알림 -> 성공 시 다시 정상적으로 다음 노드로 넘어감
		if (!controlledPawn->IsPlayingMontage())
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
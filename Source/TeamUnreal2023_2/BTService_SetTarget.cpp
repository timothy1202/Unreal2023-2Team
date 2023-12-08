// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_SetTarget.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_SetTarget::UBTService_SetTarget()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Set Target");
}

void UBTService_SetTarget::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);
	if (auto* const AIController = OwnerComp.GetAIOwner())
	{
		// 음영준 - BT내에 지정한 Key값으로 타겟을 가져옴 -> Key지정은 NPC의 OnBeginOverlapPlayer, OnEndOverlapPlayer에서 하는중
		AActor* Target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey()));

		// 음영준 - AI컨트롤러의 Focus설정 -> 한 번 Foucs를 설정해두면 자동으로 계속 그 타겟을 바라보게됨
		AIController->SetFocus(Target);
	}
}
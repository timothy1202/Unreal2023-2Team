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
		// ������ - BT���� ������ Key������ Ÿ���� ������ -> Key������ NPC�� OnBeginOverlapPlayer, OnEndOverlapPlayer���� �ϴ���
		AActor* Target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey()));

		// ������ - AI��Ʈ�ѷ��� Focus���� -> �� �� Foucs�� �����صθ� �ڵ����� ��� �� Ÿ���� �ٶ󺸰Ե�
		AIController->SetFocus(Target);
	}
}
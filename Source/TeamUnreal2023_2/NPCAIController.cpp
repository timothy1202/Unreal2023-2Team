// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCAIController.h"
#include "NPC.h"

ANPCAIController::ANPCAIController(FObjectInitializer const& ObjectInitializer)
{

}

void ANPCAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (ANPC* const npc = Cast< ANPC>(InPawn)) //�� ���� npc �̸�
	{
		if (UBehaviorTree* const tree = npc->GetBehaviorTree()) //���� Ʈ���� ������
		{
			UBlackboardComponent* b;
			UseBlackboard(tree->BlackboardAsset, b); //������ ������ Ʈ������ �����ͼ� �����ϸ� b�� �־��ش�
			Blackboard = b;
			RunBehaviorTree(tree);
		}
	}
}
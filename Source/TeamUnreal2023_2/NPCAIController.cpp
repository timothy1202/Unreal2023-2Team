// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCAIController.h"
#include "NPC.h"

ANPCAIController::ANPCAIController(FObjectInitializer const& ObjectInitializer)
{

}

void ANPCAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (ANPC* const npc = Cast< ANPC>(InPawn)) //이 폰이 npc 이면
	{
		if (UBehaviorTree* const tree = npc->GetBehaviorTree()) //폰의 트리를 가져옴
		{
			UBlackboardComponent* b;
			UseBlackboard(tree->BlackboardAsset, b); //블랙보드 에셋을 트리한테 가져와서 존재하면 b에 넣어준다
			Blackboard = b;
			RunBehaviorTree(tree);
		}
	}
}
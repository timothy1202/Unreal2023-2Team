// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindRandomLocation.h"
#include "NPCAIController.h"
#include "BTFunction.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MonsterBehavior.h"
#include "NPC.h"

UBTTask_FindRandomLocation::UBTTask_FindRandomLocation(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Find Random Location In NavMesh";
}

EBTNodeResult::Type UBTTask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (Super::ExecuteTask(OwnerComp, NodeMemory) == EBTNodeResult::InProgress)
		return EBTNodeResult::InProgress;

	// ������ - ���� Focus�� ���¿��� �Ѿ�Դٸ� AI��Ŀ�� ����
	if (OwnerComp.GetAIOwner()->GetFocusActor())
		OwnerComp.GetAIOwner()->ClearFocus(EAIFocusPriority::Gameplay);

	if (BTFunction::GetNPCAndSetBehavior(OwnerComp, GetNewBehavior()) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to set behavior!"));
	}

	//get AI Conroller and its npc
	if (auto* const cont = Cast<ANPCAIController>(OwnerComp.GetAIOwner())) //���� ��Ʈ�ѷ��� �����ͼ� Ʈ���� ������
	{
		if (auto* const npc = cont->GetPawn())
		{
			//obatin npc location to use as an origin
			auto const Origin = npc->GetActorLocation();

			//get the navigation system and generate a radom location
			if (auto* const NavSys = UNavigationSystemV1::GetCurrent(GetWorld()))
			{
				FNavLocation Loc;
				//������ġ�� ã���� if�� ����
				
				if (NavSys->GetRandomPointInNavigableRadius(Origin, SearchRadius, Loc))
				{
					cont->GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), Loc.Location);
				}


				//finish with success
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
	}

	return EBTNodeResult::Failed;
}
